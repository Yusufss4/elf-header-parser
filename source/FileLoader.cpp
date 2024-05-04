#include "FileLoader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

void FileLoader::loadFile(const std::string& filename) {
    // Open the file
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    // Read the first 16 bytes for identification
    file.read(reinterpret_cast<char*>(identification.data()), identification.size());

    // Clear existing data and read the entire file into memory
    data.clear();
    file.seekg(0, std::ios::end);
    data.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(data.data()), data.size());
}

const std::array<uint8_t, 16>& FileLoader::getFileIdentification() const {
    return identification;
}

const std::vector<uint8_t>& FileLoader::getFileData() const {
    return data;
}