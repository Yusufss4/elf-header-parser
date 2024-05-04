#pragma once

#include <string>
#include <vector>
#include <array>

class FileLoader {
public:
    void loadFile(const std::string& filename);
    const std::array<uint8_t, 16>& getFileIdentification() const;
    const std::vector<uint8_t>& getFileData() const;

private:
    std::array<uint8_t, 16> identification;
    std::vector<uint8_t> data;
};
