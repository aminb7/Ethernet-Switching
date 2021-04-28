#include "../include/System.h"

int main(int argc, char const *argv[]) {
	System system;
	system.get_id_from_network();
    cout << system.get_id();
	return ZERO;
}

void System::get_id_from_network() {
	char data[MAX_LINE];
	int fd = open(PATH_NAME, O_RDONLY);
    read(fd, data, MAX_LINE);
    close(fd);
    this->id = stoi(data);
}