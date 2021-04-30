#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

vector<string> split(const string& s, char delimiter);

std::string read_file_to_string(std::string file_path) {
    std::ifstream t(file_path);
    std::string str;

    t.seekg(0, std::ios::end);   
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    return str;
}

#endif
