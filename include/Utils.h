#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

std::vector<std::string> split(const std::string& s, char delimiter);

std::string read_file_to_string(std::string file_path);

#endif
