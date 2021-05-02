#include "../include/System.h"
#include <errno.h>

using namespace std;

int main(int argc, char const *argv[]) {
	System system;
    system.start(argv[DATA]);
	return ZERO;
}

System::System()
: network_pipe_path("")
, connection_pipe_path("", "") {
}

void System::start(const char* args) {
    set_props(args);

    char received_message[MAX_LINE] = {0};
    fd_set fds;
    int maxfd, activity;
    while (true) {
        int network_pipe_fd = open(this->network_pipe_path.c_str(), O_NONBLOCK);
        maxfd = network_pipe_fd;
        FD_ZERO(&fds);
        FD_SET(network_pipe_fd, &fds);
        int connection_pipe_fd;
        if (connection_pipe_path.first != "") {
            connection_pipe_fd = open(this->connection_pipe_path.first.c_str(), O_NONBLOCK);
            maxfd = connection_pipe_fd > network_pipe_fd ? connection_pipe_fd : network_pipe_fd;
            FD_SET(connection_pipe_fd, &fds);
        }

        activity = select(maxfd + 1, &fds, NULL, NULL, NULL);
        if (activity < 0)
            return;

        memset(received_message, 0, sizeof received_message);

        if (FD_ISSET(network_pipe_fd, &fds)) {
            if (connection_pipe_path.first != "")
                close(connection_pipe_fd);
            read(network_pipe_fd, received_message, MAX_LINE);
            handle_network_command(received_message);
        }

        else if (FD_ISSET(connection_pipe_fd, &fds)) {
            read(connection_pipe_fd, received_message, MAX_LINE);
            if (connection_pipe_path.first != "")
                close(connection_pipe_fd);
            handle_ethernet_message(received_message);
        }

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
        connect(info[ARG1], info[ARG2]);

    if (info[COMMAND] == SEND_COMMAND) 
        network_send(info[ARG1]);

    if (info[COMMAND] == RECEIVE_COMMAND)
        network_receive();
}

void System::connect(string read_path, string write_path) {
    this->connection_pipe_path = make_pair(read_path, write_path);
}

void System::network_send(string ethernet_message) {
    if (connection_pipe_path.second != "") {
        int connection_pipe_fd = open(this->connection_pipe_path.second.c_str(), O_WRONLY);
        write(connection_pipe_fd, ethernet_message.c_str(), ethernet_message.size() + ONE);
        close(connection_pipe_fd);
    }
}

void System::network_receive() {
    if (!message_queue.empty()) {
        EthernetFrame frame = message_queue.front();
        cout << "Source Address: " << frame.getContent() << NEW_LINE;
        cout << "Content: " << frame.getContent() << NEW_LINE;
        message_queue.pop();
    }
    else {
        cout << "No messeage has been received yet!" << NEW_LINE;
    }
    cout << "> ";
}

void System::handle_ethernet_message(char* message) {
    vector<string> info = split(message, ETHERNET_SEPERATOR);
    if (stoi(info[DST_ADDR_IDX]) == id)
        message_queue.push(EthernetFrame::decode(message));
}
