#include "../include/Network.h"

using namespace std;

int main(int argc, char const *argv[]) {
	string command;
	Network network;
	while(true) {
		getline(cin, command);
		if (command == QUIT_COMMAND) {
			break;
		}

		network.handle_command(command);
	}
	return ZERO;
}

void Network::handle_command(string command) {
    vector<string> command_parts = split(command, SPACE);

    if (command_parts[COMMAND] == ADD_SWITCH_COMMAND)
        add_switch(stoi(command_parts[ARG1]), stoi(command_parts[ARG2]));

    else if (command_parts[COMMAND] == ADD_SYSTEM_COMMAND)
        add_system(stoi(command_parts[ARG1]));

	else if (command_parts[COMMAND] == CONNECT_COMMAND)
		connect(stoi(command_parts[ARG1]), stoi(command_parts[ARG2]), stoi(command_parts[ARG3]));

	else if (command_parts[COMMAND] == SEND_COMMAND)
		send(stoi(command_parts[ARG1]), stoi(command_parts[ARG2]), command_parts[ARG1]);
}

int Network::add_switch(int number_of_ports, int switch_number) {
    string path_name = SWITCH_PREFIX + to_string(switch_number);
	unlink(path_name.c_str());
	mkfifo(path_name.c_str(), READ_WRITE);
	
	int fd[TWO];	
	Pid p;

	p = fork();

	if (p < ZERO) {
		cout << FORK_FAILED_MESSAGE << NEW_LINE; 
		return ONE;
	}
	else if (p > ZERO) {
		this->switches.insert({switch_number, p});
		close(fd[READ_END]);
	}
	else {
		close(fd[WRITE_END]);
        string switch_message = make_switch_message(number_of_ports, switch_number);
		char *args[] = {(Message)SWITCH_DIR, (Message)switch_message.c_str(), NULL};
		execv(args[ZERO], args);
	}
}

int Network::add_system(int system_number) {
	string path_name = SYSTEM_PREFIX + to_string(system_number);
	unlink(path_name.c_str());
	mkfifo(path_name.c_str(), READ_WRITE);
	
	int fd[TWO];	
	Pid p;

	p = fork();

	if (p < ZERO) {
		cout << FORK_FAILED_MESSAGE << NEW_LINE; 
		return ONE;
	}
	else if (p > ZERO) {
		this->systems.insert({system_number, p});
		close(fd[READ_END]);
	}
	else {
		close(fd[WRITE_END]);
        string system_message = to_string(system_number);
		char *args[] = {(Message)SYSTEM_DIR, (Message)system_message.c_str(), NULL};
		execv(args[ZERO], args);
	}
}

int Network::connect(int system_number, int switch_number, int port_number) {
	string path = make_connect_path(system_number, switch_number, port_number);
    unlink(path.c_str());
	mkfifo(path.c_str(), READ_WRITE);
    string switch_path = SWITCH_PREFIX + to_string(switch_number);
	string system_path = SYSTEM_PREFIX + to_string(system_number);

    string message = make_connect_message(path);

	int fds_switch = open(switch_path.c_str(), O_WRONLY);
    write(fds_switch, (Message) message.c_str(), 
    	strlen((Message) message.c_str()) + ONE);
    close(fds_switch);

	int fds_system = open(system_path.c_str(), O_WRONLY);
    write(fds_system, (Message) message.c_str(), 
    	strlen((Message) message.c_str()) + ONE);
    close(fds_system);
}

string Network::make_switch_message(int number_of_ports, int switch_number) {
    string message = to_string(switch_number);
    message += PROPS_SEPARATOR;
    message += to_string(number_of_ports);
    return message;
}

void Network::send(int sender_number, int reveiver_number, string file_path) {

}
string Network::make_connect_path(int system_number, int switch_number, int port_number) {
	string path = to_string(system_number) + PATH_SEPARATOR;
	path += to_string(switch_number) + PATH_SEPARATOR;
	path += to_string(port_number);
    return path;
}

string Network::make_connect_message(string path) {
    string message = CONNECT_COMMAND;
    message += COMMAND_SEPARATOR;
    message += path;
    return message;
}
