#pragma once

#ifndef FILE_H
#define FILE_H

#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;
using namespace fs;


class File: directory_entry {
    fs::path filepath, name, extension; 
    public:
    File(string fpath);
    File(fs::path fpath);
    fs::path getFileExtension(), getName(), getPath();
};


#endif
