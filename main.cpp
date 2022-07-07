#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <Windows.h>

#include "file.cpp"
#include "folder.cpp"
#include "filewatcher.h"

using namespace std;

char *username = getenv("USERNAME");
string root = "C:\\Users\\",
    downloads = "\\Downloads",
    videos = "\\Videos",
    music = "\\Music",
    pictures = "\\OneDrive\\Pictures",
    downloadsPath = "",
    videosPath = "",
    musicPath="",
    picturesPath="";

vector<string> AUDIO_EXTENSIONS = {".3gp", ".3gpp", ".3g2", ".3gpp2", ".aac", ".adts", ".loas", ".ass", ".au", ".snd", ".mp3", ".mp2", ".opus", ".aif", ".aifc", ".aiff", ".ra", ".wav", ".reapeaks", ".flac"};
vector<string> VIDEO_EXTENSIONS = {".mp4", ".mpeg", ".m1v", ".mpa", ".mpe", ".mpg", ".mov", ".qt", ".webm", ".avi", ".movie"};
vector<string> IMAGE_EXTENSIONS = {".bmp", ".gif", ".ief", ".jfif", ".jpg", ".jpe", ".jpeg", ".heic", ".heif", ".png", ".svg", ".tiff", ".tif", ".ico", ".ras", ".pnm", ".pbm", ".pgm", ".ppm", ".rgb", "webp", ".xbm", ".xpm", ".xwd"};


void createFilePath(string &pathToBeMade, string folderName) {
    pathToBeMade = pathToBeMade + root;
    pathToBeMade = pathToBeMade + username;
    pathToBeMade = pathToBeMade + folderName;
}

void openFolderLocation(string path) {
    // const char command = &path;
    string command = "explorer ";
    command = command + path;
    char *help;
    help = &command[0];
    system(help);
}

void openFileLocation(string filepath) {
    // const char command = &path;
    string command = "explorer /select, ";
    command = command + filepath;
    char *help;
    help = &command[0];
    system(help);
}

void listFiles(string path) {
    for (auto& dirEntry: directory_iterator(path)) {
        if (!dirEntry.is_regular_file()) {
            cout << "Directory: " << dirEntry.path() << endl;
            continue;
        }
        fs::path file = dirEntry.path();
        cout << "Filename: " << file.filename() << " extension: " << file.extension() << endl;

    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << "running..." << endl;

    createFilePath(downloadsPath, downloads);
    createFilePath(videosPath, videos);
    createFilePath(musicPath, music);
    createFilePath(picturesPath, pictures);

    Folder videosFolder(videosPath, VIDEO_EXTENSIONS);
    Folder musicFolder(musicPath, AUDIO_EXTENSIONS);
    Folder picturesFolder(picturesPath, IMAGE_EXTENSIONS);
    Folder downloadsFolder(downloadsPath);

    downloadsFolder.addToRelatedFolders(videosFolder);
    downloadsFolder.addToRelatedFolders(musicFolder);
    downloadsFolder.addToRelatedFolders(picturesFolder);

    for (auto& entry: downloadsFolder.getFiles()) {
        downloadsFolder.sort(entry);
    }

    // Create a FileWatcher instance that will check the current folder for changes every 5 seconds
    FileWatcher fw{downloadsPath, chrono::milliseconds(10), downloadsFolder};

    // Start monitoring a folder for changes and (in case of changes)
    // run a user provided lambda function
    fw.start([] (string path_to_watch, FileStatus status, Folder downloadsFolder) -> void {
        // Process only regular files, all other file types are ignored
        if(!is_regular_file(path(path_to_watch)) && status != FileStatus::erased) {
            return;
        }

        File file(path_to_watch);

        switch(status) {
            case FileStatus::created:    
                downloadsFolder.sort(file);
                cout << "File created: " << file.getName() << endl;
                break;
            case FileStatus::modified:
                downloadsFolder.sort(file);
                cout << "File modified: " << file.getName() << endl;
                break;
            case FileStatus::erased:
                cout << "File erased: " << file.getName() << endl;
                break;
            default:
                cout << "Error! Unknown file status." << endl;
        }
    });

    return 0;
}