#define SWITCH_DIR "Switch.out"
#define SYSTEM_DIR "System.out"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h> 
#include <dirent.h>
#include <fcntl.h> 

#include "Utils.h"

#define ADD_SWITCH_COMMAND "MySwitch"
#define ADD_SYSTEM_COMMAND "MySystem"
#define CONNECT_COMMAND "Connect"
#define QUIT_COMMAND "Quit"
#define SWITCH_PREFIX "switch"
#define SYSTEM_PREFIX "system"
#define CONNECT_PREFIX "connect"
#define PATH_NAME "system"
#define FORK_FAILED_MESSAGE "Fork Failed!"
#define READ_END 0
#define WRITE_END 1
#define NEW_LINE '\n'
#define SPACE ' '
#define PROPS_SEPARATOR "$"
#define COMMAND_SEPARATOR "@"
#define PATH_SEPARATOR "_"
#define READ_WRITE 0666
#define COMMAND 0
#define ARG1 1
#define ARG2 2
#define ARG3 3
#define ZERO 0
#define ONE 1
#define TWO 2

typedef char* Message;
typedef pid_t Pid;

using namespace std;

class Network
{
public:
    Network() {}
    void handle_command(string command);
    int add_switch(int number_of_ports, int switch_number);
    int add_system(int system_number);
    int connect(int system_number, int switch_number, int port_number);
    string make_switch_message(int number_of_ports, int switch_number);
    string make_connect_path(int system_number, int switch_number, int port_number);
    string make_connect_message(string path);
private:
    std::map<int, Pid> switches;
    std::map<int, Pid> systems;
};
