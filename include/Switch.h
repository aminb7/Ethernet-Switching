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
#define ZERO 0
#define MAX_LINE 2048
#define PROPS_SEPARATOR '$'
#define ID 0
#define NUMBER_OF_PORTS 1
#define DATA 1

using namespace std;

class Switch {
    public:
    Switch() {}
    ~Switch();
    void set_props(string data);
    int get_id() {return id;}
    string get_path() {return path_name;}
private:
    int id;
    int number_of_ports;
    string path_name;
    map<string, string> lookup;
};

Switch::~Switch()
{
}

#endif