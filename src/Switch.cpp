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

        vector<int> connection_pipe_fds;
        vector<int> connection_ports;
        map<int, pair<string, string>>::iterator it;
        for (it = connection_pipe_paths.begin(); it != connection_pipe_paths.end(); it++)
        {
            int connection_pipe_fd = open(it->second.first.c_str(), O_NONBLOCK);
            connection_pipe_fds.push_back(connection_pipe_fd);
            connection_ports.push_back(it->first);
            maxfd = connection_pipe_fd > maxfd ? connection_pipe_fd : maxfd;
            FD_SET(connection_pipe_fd, &fds);
        }

        activity = select(maxfd + 1, &fds, NULL, NULL, NULL);
        if (activity < 0)
            return;

        memset(received_message, 0, sizeof received_message);

        if (FD_ISSET(network_pipe_fd, &fds)) {
            read(network_pipe_fd, received_message, MAX_LINE);
            handle_network_command(received_message);
        }
        else {
            int incomming_message_port;
            for (size_t i = 0; i < connection_pipe_fds.size(); i++) {
                if (FD_ISSET(connection_pipe_fds[i], &fds)) {
                    incomming_message_port = connection_ports[i];
                    read(connection_pipe_fds[i], received_message, MAX_LINE);
                    break;
                }
            }

            for (int connection_pipe_fd : connection_pipe_fds)
                close(connection_pipe_fd);

            handle_ethernet_message(received_message, incomming_message_port);
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
        connect(info[ARG2], info[ARG1]);
}

void Switch::connect(string read_path, string write_path) {
	vector<string> parts = split(read_path, PATH_SEPARATOR);
    if (connection_pipe_paths.find(stoi(parts[PORT_NUMBER])) == connection_pipe_paths.end())
	    connection_pipe_paths.insert({stoi(parts[PORT_NUMBER]), make_pair(read_path, write_path)});
}

void Switch::handle_ethernet_message(char* message, int port) {
    vector<string> info = split(message, ETHERNET_SEPERATOR);
    if (lookup.find(info[SRC_ADDR_IDX]) == lookup.end()) 
        lookup.insert({info[SRC_ADDR_IDX], port});

    if (lookup.find(info[DST_ADDR_IDX]) != lookup.end()) {
        int port = lookup[info[DST_ADDR_IDX]];
        int connection_pipe_fd = open(connection_pipe_paths[port].second.c_str(), O_WRONLY);
        write(connection_pipe_fd, message, strlen(message) + ONE);
        close(connection_pipe_fd);
    }
    else {
        map<int, pair<string, string>>::iterator it;
        for (it = connection_pipe_paths.begin(); it != connection_pipe_paths.end(); it++) {
            if (connection_pipe_paths[port].second == it->second.second)
                continue;
            int connection_pipe_fd = open(it->second.second.c_str(), O_WRONLY);
            write(connection_pipe_fd, message, strlen(message) + ONE);
            close(connection_pipe_fd);
        }
    }
}
