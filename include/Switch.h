#ifndef SWITCH_H
#define SWITCH_H

#include <sys/stat.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <map>
#include <utility>

#include "Utils.h"
#include "EthernetFrame.h"

#define PATH_PREFIX "switch"
#define CONNECT_PATH_PREFIX "connect"
#define ZERO 0
#define MAX_LINE 2048
#define PROPS_SEPARATOR '$'
#define COMMAND_SEPARATOR '@'
#define PATH_SEPARATOR '_'
#define CONNECT_COMMAND "Connect"
#define CONNECT_SWITCH_COMMAND "ConnectSwitch"
#define STP_COMMAND "Stp"
#define COMMAND 0
#define PORT_NUMBER 3
#define ARG1 1
#define ARG2 2
#define ID 0
#define NUMBER_OF_PORTS 1
#define DATA 1
#define ONE 1

class Switch {
public:
    Switch();
    ~Switch() = default;
    void start(const char* args);
    void set_props(std::string data);
    void handle_network_command(char* message);
    void connect(std::string read_path, std::string write_path);
    void handle_ports_message(char* message, int port);
    void handle_ethernet_message(char* message, int port);
    void handle_stp_message(char* message, int port);
    int get_id() {return id;}
    std::string get_path() {return network_pipe_path;}

private:
    int id;
    int number_of_ports;
    int root_port;
    int root_id;
    int root_distance;
    std::string network_pipe_path;
    std::map<std::string, int> lookup;
    std::map<int, std::pair<std::string, std::string>> connection_pipe_paths;
};

#endif
