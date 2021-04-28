#ifndef SYSTEM_H
#define SYSTEM_H

#include <sys/stat.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <iostream>

#define PATH_PREFIX "system"
#define ZERO 0
#define MAX_LINE 2048
#define DATA 1

using namespace std;

class System {
public:
    System() {}
    ~System();
    void set_props(string data);
    int get_id() {return id;}
private:
    int id;
    string path_name;
};

System::~System()
{
}

#endif