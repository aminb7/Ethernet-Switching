#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

vector<string> split(const string& s, char delimiter);

std::string read_file_to_string(std::string file_path);

#endif
