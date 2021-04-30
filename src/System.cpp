#include "../include/System.h"

using namespace std;

int main(int argc, char const *argv[]) {
	System system;
	system.set_props(argv[DATA]);
    cout << system.get_id();

    while(true) {
		system.handle_command();
	}

	return ZERO;
}

void System::set_props(string data) {
    this->id = stoi(data);
    this->path_name = PATH_PREFIX + data;
}

void System::handle_command() {
	char data[MAX_LINE];
    cout << "waiting for command." << endl;
	int fd = open(this->path_name.c_str(), O_RDONLY);
    read(fd, data, MAX_LINE);
    close(fd);

    vector<string> info = split(data, COMMAND_SEPARATOR);
    
    if (info[COMMAND] == CONNECT_COMMAND) 
        this->connection = info[ARG1];
}
