// EndiannessConverter.h
#pragma once

#include <vector>

namespace elf_header {

class EndiannessConverter {
public:
    virtual ~EndiannessConverter() {}
    virtual uint32_t convertToLittleEndian(uint32_t value) = 0;
    // Add more conversion methods as needed
};

class LittleEndianConverter : public EndiannessConverter {
public:
    uint32_t convertToLittleEndian(uint32_t value) override {
        // Implementation for little-endian conversion
    }
};

class BigEndianConverter : public EndiannessConverter {
public:
    uint32_t convertToLittleEndian(uint32_t value) override {
        // Implementation for big-endian conversion
    }
};

}  // namespace elf_header