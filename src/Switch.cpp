#include "../include/Switch.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
	Switch my_switch;
    my_switch.start(argv[DATA]);
	return ZERO;
}

void Switch::start(const char* args) {
    set_props(args);

    char received_message[MAX_LINE] = {0};
    fd_set fds;
    int maxfd, activity;
    while (true) {
        int network_pipe_fd = open(this->network_pipe_path.c_str(), O_NONBLOCK);
        maxfd = network_pipe_fd;

        FD_ZERO(&fds);
        FD_SET(network_pipe_fd, &fds);

        map<int, string>::iterator it;
        vector<int> connection_pipe_fds;
        for (it = connection_pipe_paths.begin(); it != connection_pipe_paths.end(); it++)
        {
            int connection_pipe_fd = open(it->second.c_str(), O_NONBLOCK);
            connection_pipe_fds.push_back(connection_pipe_fd);
            maxfd = connection_pipe_fd > maxfd ? connection_pipe_fd : maxfd;
            FD_SET(connection_pipe_fd, &fds);
        }

        activity = select(maxfd + 1, &fds, NULL, NULL, NULL);
        if (activity < 0)
            return;

        memset(received_message, 0, sizeof received_message);
        read(network_pipe_fd, received_message, MAX_LINE);

        if (FD_ISSET(network_pipe_fd, &fds))
            handle_network_command(received_message);
        else
            handle_ethernet_message(received_message);

        for (int connection_pipe_fd : connection_pipe_fds) {
            close(connection_pipe_fd);
        }

        close(network_pipe_fd);
    }
}

void Switch::set_props(string data) {
    vector<string> info = split(data, PROPS_SEPARATOR);
    this->id = stoi(info[ID]);
    this->network_pipe_path = PATH_PREFIX + info[ID];
    this->number_of_ports = stoi(info[NUMBER_OF_PORTS]);
}

void Switch::handle_network_command(char* message) {
    vector<string> info = split(message, COMMAND_SEPARATOR);

    if (info[COMMAND] == CONNECT_COMMAND) 
        connect(info[ARG1]);
}

void Switch::connect(string path) {
	vector<string> parts = split(path, PATH_SEPARATOR);
	this->connection_pipe_paths.insert({stoi(parts[PORT_NUMBER]), path});
    map<int, string>::iterator it;
    for (it = connection_pipe_paths.begin(); it != connection_pipe_paths.end(); it++)
    {
    }
}

void Switch::handle_ethernet_message(char* message) {
    
}
