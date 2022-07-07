#include "file.h"

using namespace std;

File::File(string fpath){
    filepath = fpath;
    name = filepath.filename();
    extension = filepath.extension();
};

File::File(fs::path fpath){
    filepath = fpath;
    name = filepath.filename();
    extension = filepath.extension();
};

fs::path File::getName() {
    return name;
};

fs::path File::getPath() {
    return filepath;
}

fs::path File::getFileExtension() {
    return extension;
}