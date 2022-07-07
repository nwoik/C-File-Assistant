#include "folder.h"
#include "file.h"

using namespace std;

Folder::Folder(string fpath) {
    filepath = fpath;
    name = filepath.filename();
    files = directory_iterator(filepath);
};

Folder::Folder(string fpath, vector<string> extensions) {
    filepath = fpath;
    name = filepath.filename();
    vector<string> relatedExtensions = extensions;
    files = directory_iterator(filepath);
}

void Folder::addToRelatedExtensions(string extension) {
    relatedExtensions.push_back(extension);
}

void Folder::addToRelatedFolders(Folder folder) {
    relatedFolders.push_back(folder);
}

bool Folder::checkFileExtension(File file) {
    string ext = file.getPath().u8string();
    for (string e: relatedExtensions) {
        cout << e << " " << ext << endl;
        if (e == ext) {
            return true;
        }
    }
    return false;
}

void Folder::moveFile(File file) {
    int increment = 0;
    
    if (findFile(file.getName().u8string())) {
        increment++;
        moveFile(file, increment);
    }
    else {
        string cmd = "move ";
        cmd += file.getPath().u8string() + " ";
        cmd += getPath().u8string();
        char *help; help = &cmd[0];
        cout << help << endl;
        system(help);
    }
}

void Folder::moveFile(File file, int increment) {
    string incName = file.getPath().stem().u8string();
    string strinc = to_string(increment);
    incName += " (";
    incName += strinc;
    incName += ")";
    incName += file.getFileExtension().u8string();
    if (findFile(incName)) {
        increment++;
        moveFile(file, increment);
    }
    else {
        string cmd = "move ";
        cmd += file.getPath().u8string() + " ";
        cmd += getPath().u8string()+"\\";
        cmd += incName;
        char *help; help = &cmd[0];
        cout << help << endl;
        system(help);
    }
}

bool Folder::findFile(string filename) {
    for (auto& entry: files) {
        if (entry.path().filename().u8string() == filename) {
            return true;
        }
    }
    return false;
}

void Folder::sort(File file) {
    for (auto& relatedFolder:relatedFolders) {
        if (relatedFolder.checkFileExtension(file)) {
            relatedFolder.moveFile(file);
        }
    }
}

void Folder::sort(directory_entry entry) {
    if (entry.is_directory()) {
        return ;
    }

    File file(entry.path());
    sort(file);
}

path Folder::getName() {
    return name;
};

path Folder::getPath() {
    return filepath;
}

directory_iterator Folder::getFiles() {
    return files;
}