#pragma once

#include "ElfHeader.h"
#include "EndiannessConverter.h"

namespace elf_header {

  class ElfHeaderIdentificationParser {
    // Store parsed information about ELF file header
    ElfHeaderIdentification parseIdentification(const std::array<uint8_t, 16>& fileData);
  }

  // Abstract base class for ElfHeaderParser
  template <typename FileClassArchitecture>
  class ElfHeaderParser {
  public:
    virtual ~ElfHeaderParser() {}
    virtual ElfHeader<FileClassArchitecture> parseHeader(const std::vector<uint8_t>& fileData,
                                                         EndiannessConverter& converter)
        = 0;

  private:
    static LittleEndianConverter defaultConverter;  // Default converter for 32-bit
  };

  // Concrete subclass for 32-bit ELF header parser
  class ElfHeaderParser32 : public ElfHeaderParser<uint32_t> {
  public:
    ElfHeader32 parseHeader(const std::vector<uint8_t>& fileData,
                            EndiannessConverter& converter) override;
  };

  // Concrete subclass for 64-bit ELF header parser
  class ElfHeaderParser64 : public ElfHeaderParser<uint64_t> {
  public:
    ElfHeader64 parseHeader(const std::vector<uint8_t>& fileData,
                            EndiannessConverter& converter) override;
  };

  // Factory class for creating instances of ElfHeaderParser
  class ElfHeaderParserFactory {
  public:
    static std::unique_ptr<ElfHeaderParser> createParser(bool is32Bit) {
      if (is32Bit) {
        return std::make_unique<ElfHeaderParser32>();
      } else {
        return std::make_unique<ElfHeaderParser64>();
      }
    }
  };

  class ElfFileLoader {
    // Load ELF file
    // Read necessary data from ELF file
  };

  class EndianConverter {
    // Convert endianness of data
  };

}  // namespace elf_header
