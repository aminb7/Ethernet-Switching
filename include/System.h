#ifndef SYSTEM_H
#define SYSTEM_H

#include <sys/stat.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <string>
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
    System() {}
    ~System();
    void set_props(std::string data);
    void handle_command();
    int get_id() {return id;}

private:
    int id;
    std::string path_name;
    std::string connection;
};

System::~System()
{
}

#endif
