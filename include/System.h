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

#include "Utils.h"

#define PATH_PREFIX "system"
#define ZERO 0
#define MAX_LINE 2048
#define DATA 1
#define COMMAND_SEPARATOR '@'
#define CONNECT_COMMAND "Connect"
#define COMMAND 0
#define ARG1 1

class System {
public:
    System();
    ~System();
    void start(const char* args);
    void set_props(std::string data);
    void handle_network_command(char* message);
    void connect(std::string path);
    int get_id() {return id;}

private:
    int id;
    std::string network_pipe_path;
    std::string connection_pipe_path;
};

System::~System()
{
}

#endif
