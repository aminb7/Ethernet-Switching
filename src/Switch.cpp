#include "../include/Switch.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
	Switch my_switch;
    my_switch.start(argv[DATA]);
	return ZERO;
}

void Switch::start(const char* args) {
    set_props(args);

    while(true) {
		handle_command();
	}
}

void Switch::set_props(string data) {
    vector<string> info = split(data, PROPS_SEPARATOR);
    this->id = stoi(info[ID]);
    this->network_pipe_path = PATH_PREFIX + info[ID];
    this->number_of_ports = stoi(info[NUMBER_OF_PORTS]);
}

void Switch::handle_command() {
	char data[MAX_LINE];
	int fd = open(this->network_pipe_path.c_str(), O_RDONLY);
    read(fd, data, MAX_LINE);
    close(fd);
    vector<string> info = split(data, COMMAND_SEPARATOR);

    if (info[COMMAND] == CONNECT_COMMAND) 
        connect(info[ARG1]);
}

void Switch::connect(string path) {
	vector<string> parts = split(path, PATH_SEPARATOR);
	this->connection_pipe_paths.insert({stoi(parts[PORT_NUMBER]), path});
}
