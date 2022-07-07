#pragma once

#ifndef FOLDER_H
#define FOLDER_H

#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>

#include "file.h"
#include "folder.h"

namespace fs = std::filesystem;

using namespace std;
using namespace fs;


class Folder: directory_entry {
    fs::path filepath, name; 
    vector<string> relatedExtensions;
    vector<Folder> relatedFolders;
    directory_iterator files;

    public:
    Folder(string fpath);
    Folder(string fpath, vector<string> extensions);
    void addToRelatedExtensions(string extension);
    void addToRelatedFolders(Folder folder);
    bool checkFileExtension(File file);
    void moveFile(File file);
    void sort(File file);
    void sort(directory_entry entry);
    bool findFile(string filename);
    vector<Folder> getRelatedFolders();
    fs::path getName(), getPath();
    directory_iterator getFiles();

    private:
    void moveFile(File file, int increment);
};

#endif