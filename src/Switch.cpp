#include "../include/Switch.h"

int main(int argc, char const *argv[]) {
	Switch my_switch;
	my_switch.get_props_from_network();
    cout << my_switch.get_id();
	return ZERO;
}

void Switch::get_props_from_network() {
	char data[MAX_LINE];
	int fd = open(PATH_NAME, O_RDONLY);
    read(fd, data, MAX_LINE);
    close(fd);
    vector<string> info = split(data, PROPS_SEPARATOR);
    this->id = stoi(info[ID]);
    this->number_of_ports = stoi(info[NUMBER_OF_PORTS]);
}