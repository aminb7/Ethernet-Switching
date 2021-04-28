#include "../include/System.h"

int main(int argc, char const *argv[]) {
	System system;
	system.set_props(argv[DATA]);
    cout << system.get_id();
	return ZERO;
}

void System::set_props(string data) {
    this->id = stoi(data);
    this->path_name = PATH_PREFIX + data;
}