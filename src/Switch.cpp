#include "../include/Switch.h"

using namespace std;

int main(int argc, char const *argv[]) {
	Switch my_switch;
	my_switch.set_props(argv[DATA]);
	return ZERO;
}

void Switch::set_props(string data) {
	// char data[MAX_LINE];
	// int fd = open(this->path_name, O_RDONLY);
    // read(fd, data, MAX_LINE);
    // close(fd);
    vector<string> info = split(data, PROPS_SEPARATOR);
    this->id = stoi(info[ID]);
    this->path_name = PATH_PREFIX + info[ID];
    this->number_of_ports = stoi(info[NUMBER_OF_PORTS]);
}
