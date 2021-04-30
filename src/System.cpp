#include "../include/System.h"

using namespace std;

int main(int argc, char const *argv[]) {
	System system;
    system.start(argv[DATA]);
	return ZERO;
}

System::System()
: network_pipe_path("")
, connection_pipe_path("") {
}

void System::start(const char* args) {
    set_props(args);

    char received_message[MAX_LINE] = {0};
    fd_set fds;
    int maxfd, activity;
    while (true) {
        int network_pipe_fd = open(this->network_pipe_path.c_str(), O_RDONLY);
        maxfd = network_pipe_fd;

        FD_ZERO(&fds);
        FD_SET(network_pipe_fd, &fds);
        int connection_pipe_fd;
        if (connection_pipe_path != "") {
            connection_pipe_fd = open(this->connection_pipe_path.c_str(), O_RDONLY);
            maxfd = connection_pipe_fd > network_pipe_fd ? connection_pipe_fd : network_pipe_fd;
            FD_SET(connection_pipe_fd, &fds);
        }

        activity = select(maxfd + 1, &fds, NULL, NULL, NULL);
        if (activity < 0)
            return;

        memset(received_message, 0, sizeof received_message);
        read(network_pipe_fd, received_message, MAX_LINE);

        if (FD_ISSET(network_pipe_fd, &fds))
            handle_network_command(received_message);

        if (connection_pipe_path != "" && FD_ISSET(connection_pipe_fd, &fds))
            handle_network_command(received_message);

        if (connection_pipe_path != "")
            close(connection_pipe_fd);
        close(network_pipe_fd);
    }
}

void System::set_props(string data) {
    this->id = stoi(data);
    this->network_pipe_path = PATH_PREFIX + data;
}

void System::handle_network_command(char* message) {
    vector<string> info = split(message, COMMAND_SEPARATOR);

    if (info[COMMAND] == CONNECT_COMMAND) 
        connect(info[ARG1]);
}

void System::connect(string path) {
    this->connection_pipe_path = path;
}
