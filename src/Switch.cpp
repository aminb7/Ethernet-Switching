#include "../include/Switch.h"

int main(int argc, char const *argv[]) {
	Switch my_switch;
	my_switch.set_props(argv[DATA]);

    while(true) {
		my_switch.handle_command();
	}

	return ZERO;
}

void Switch::set_props(string data) {
    vector<string> info = split(data, PROPS_SEPARATOR);
    this->id = stoi(info[ID]);
    this->path_name = PATH_PREFIX + info[ID];
    this->number_of_ports = stoi(info[NUMBER_OF_PORTS]);
}

void Switch::handle_command() {
	char data[MAX_LINE];
	int fd = open(this->path_name.c_str(), O_RDONLY);
    read(fd, data, MAX_LINE);
    close(fd);

    vector<string> info = split(data, COMMAND_SEPARATOR);
    
    if (info[COMMAND] == CONNECT_COMMAND) 
        connect(info[ARG1]);
}

void Switch::connect(string path) {
	vector<string> parts = split(path, PATH_SEPARATOR);
	this->connections.insert({stoi(parts[PORT_NUMBER]), path});
}