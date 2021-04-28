#ifndef SYSTEM_H
#define SYSTEM_H

#include <sys/stat.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <iostream>

#define PATH_NAME "system"
#define ZERO 0
#define MAX_LINE 2048

using namespace std;

class System {
public:
    System() {}
    ~System();
    void get_id_from_network();
    int get_id() {return id;}
private:
    int id;
};

System::~System()
{
}

#endif