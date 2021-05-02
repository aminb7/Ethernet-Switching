#ifndef SYSTEM_H
#define SYSTEM_H

#include <sys/stat.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <utility>

#include "Utils.h"
#include "EthernetFrame.h"

#define PATH_PREFIX "system"
#define ZERO 0
#define MAX_LINE 2048
#define DATA 1
#define COMMAND_SEPARATOR '@'
#define CONNECT_COMMAND "Connect"
#define SEND_COMMAND "Send"
#define COMMAND 0
#define ARG1 1
#define ARG2 2
#define ONE 1

class System {
public:
    System();
    ~System() = default;

    void start(const char* args);
    void set_props(std::string data);
    void handle_network_command(char* message);
    void connect(std::string read_path, std::string write_path);
    void network_send(std::string ethernet_message);
    void handle_ethernet_message(char* message);
    int get_id() {return id;}

private:
    int id;
    std::string network_pipe_path;
    std::pair<std::string, std::string> connection_pipe_path;
    std::vector<std::string> message_queue;
};

#endif
