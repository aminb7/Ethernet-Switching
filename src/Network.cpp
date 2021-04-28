#include "../include/Network.h"

int main(int argc, char const *argv[]) {
	string command;
	while(true) {
		getline(cin, command);
		if (command == QUIT_COMMAND) {
			break;
		}

		Network network;
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
}

int Network::add_switch(int number_of_ports, int switch_number) {
	unlink(PATH_NAME);
	mkfifo(PATH_NAME, READ_WRITE);
	
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
		char *args[] = {(Message)SWITCH_DIR, (Message)"1", NULL};
		execv(args[ZERO], args);
	}

    string switch_message = make_switch_message(number_of_ports, switch_number);

	int fds = open(PATH_NAME, O_WRONLY);
    write(fds, (Message) switch_message.c_str(), 
    	strlen((Message) switch_message.c_str()) + ONE);
    close(fds);
}

int Network::add_system(int system_number) {
	unlink(PATH_NAME);
	mkfifo(PATH_NAME, READ_WRITE);
	
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
		char *args[] = {(Message)SYSTEM_DIR, (Message)"1", NULL};
		execv(args[ZERO], args);
	}

    string system_message = to_string(system_number);

	int fds = open(PATH_NAME, O_WRONLY);
    write(fds, (Message) system_message.c_str(), 
    	strlen((Message) system_message.c_str()) + ONE);
    close(fds);
}

string Network::make_switch_message(int number_of_ports, int switch_number) {
    string message = to_string(switch_number);
    message += PROPS_SEPARATOR;
    message += to_string(number_of_ports);
    return message;
}