#ifndef SWITCH_H
#define SWITCH_H

#include <sys/stat.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "Utils.h"

#define PATH_PREFIX "switch"
#define CONNECT_PATH_PREFIX "connect"
#define ZERO 0
#define MAX_LINE 2048
#define PROPS_SEPARATOR '$'
#define COMMAND_SEPARATOR '@'
#define PATH_SEPARATOR '_'
#define CONNECT_COMMAND "Connect"
#define COMMAND 0
#define PORT_NUMBER 2
#define ARG1 1
#define ARG2 2
#define ID 0
#define NUMBER_OF_PORTS 1
#define DATA 1

class Switch {
public:
    Switch() {}
    ~Switch();
    void set_props(std::string data);
    void handle_command();
    void connect(std::string path);
    int get_id() {return id;}
    std::string get_path() {return path_name;}

private:
    int id;
    int number_of_ports;
    std::string path_name;
    std::map<std::string, std::string> lookup;
    std::map<int, std::string> connections;
};

Switch::~Switch()
{
}

#endif