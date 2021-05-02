#include "../include/Network.h"

using namespace std;

int main(int argc, char const *argv[]) {
	string command;
	Network network;
	while(true) {
		cout << "> ";
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
		send(stoi(command_parts[ARG1]), stoi(command_parts[ARG2]), command_parts[ARG3]);
}

int Network::add_switch(int number_of_ports, int switch_number) {
    string network_pipe_path = SWITCH_PREFIX + to_string(switch_number);
	unlink(network_pipe_path.c_str());
	mkfifo(network_pipe_path.c_str(), READ_WRITE);
	
	Pid p;

	p = fork();

	if (p < ZERO) {
		cout << FORK_FAILED_MESSAGE << NEW_LINE; 
		return ONE;
	}
	else if (p > ZERO) {
		this->switches.insert({switch_number, p});
		return ZERO;
	}
	else {
        string switch_message = make_switch_message(number_of_ports, switch_number);
		char *args[] = {(Message)SWITCH_DIR, (Message)switch_message.c_str(), NULL};
		execv(args[ZERO], args);
		return ZERO;
	}
}

int Network::add_system(int system_number) {
	string path_name_path = SYSTEM_PREFIX + to_string(system_number);
	unlink(path_name_path.c_str());
	mkfifo(path_name_path.c_str(), READ_WRITE);
	
	Pid p;

	p = fork();

	if (p < ZERO) {
		cout << FORK_FAILED_MESSAGE << NEW_LINE; 
		return ONE;
	}
	else if (p > ZERO) {
		this->systems.insert({system_number, p});
		return ZERO;
	}
	else {
        string system_message = to_string(system_number);
		char *args[] = {(Message)SYSTEM_DIR, (Message)system_message.c_str(), NULL};
		execv(args[ZERO], args);
		return ZERO;
	}
}

int Network::connect(int system_number, int switch_number, int port_number) {
	string path = make_connect_pipe_path(system_number, switch_number, port_number);
	string switch_connection_pipe_path = SWITCH_PREFIX + string(PATH_SEPARATOR) + path;
	string system_connection_pipe_path = SYSTEM_PREFIX + string(PATH_SEPARATOR) + path;

    unlink(switch_connection_pipe_path.c_str());
	mkfifo(switch_connection_pipe_path.c_str(), READ_WRITE);
	unlink(system_connection_pipe_path.c_str());
	mkfifo(system_connection_pipe_path.c_str(), READ_WRITE);
    string switch_pipe_path = SWITCH_PREFIX + to_string(switch_number);
	string system_pipe_path = SYSTEM_PREFIX + to_string(system_number);

    string message = make_connect_message(switch_connection_pipe_path, system_connection_pipe_path);

	int fds_switch = open(switch_pipe_path.c_str(), O_WRONLY);
    write(fds_switch, (Message) message.c_str(), strlen((Message) message.c_str()) + ONE);
    close(fds_switch);

	int fds_system = open(system_pipe_path.c_str(), O_WRONLY);
    write(fds_system, (Message) message.c_str(), strlen((Message) message.c_str()) + ONE);
    close(fds_system);
	return ZERO;
}

string Network::make_switch_message(int number_of_ports, int switch_number) {
    string message = to_string(switch_number);
    message += PROPS_SEPARATOR;
    message += to_string(number_of_ports);
    return message;
}

string Network::make_connect_pipe_path(int system_number, int switch_number, int port_number) {
	string path = to_string(system_number) + PATH_SEPARATOR;
	path += to_string(switch_number) + PATH_SEPARATOR;
	path += to_string(port_number);
    return path;
}

string Network::make_connect_message(string switch_connection_pipe_path, string system_connection_pipe_path) {
    string message = CONNECT_COMMAND;
    message += COMMAND_SEPARATOR;
	message += system_connection_pipe_path;
	message += COMMAND_SEPARATOR;
	message += switch_connection_pipe_path;
    return message;
}

int Network::send(int sender_number, int reveiver_number, string file_path) {
	string content = read_file_to_string(file_path);
	vector<string> partitions = partition_content(content, MAX_FILE_PARTITION_SIZE);

	string system_pipe_path = SYSTEM_PREFIX + to_string(sender_number);
	int fds_system = open(system_pipe_path.c_str(), O_WRONLY);
	for (string partition : partitions) {
		string message = string(SEND_COMMAND)
				+ string(COMMAND_SEPARATOR)
				+ EthernetFrame::encode(EthernetFrame(sender_number, reveiver_number, partition));
		write(fds_system, (Message) message.c_str(), message.size() + ONE);
	}

	close(fds_system);
	return ZERO;
}

vector<string> Network::partition_content(string content, int partition_size) {
	int number_of_partitions = content.size() / partition_size + 1;
	vector<string> partitions;
	for (int i = 0; i < number_of_partitions - 1; i++) {
		partitions.push_back(content.substr(i * partition_size, (i + 1) * partition_size));
	}
	partitions.push_back(content.substr((number_of_partitions - 1) * partition_size));
	return partitions;
}
