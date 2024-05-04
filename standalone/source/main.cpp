#include <greeter/greeter.h>
#include <greeter/version.h>

#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

// Program Diagram
// Read command line arguments. If the help option is set, print the help message and exit.
// If the version option is set, print the version number and exit.
// If the file option is set, load the elf file to be processed.
// If the none option is set, print the help message and exit.
// Load the first 16 bytes of the ELF file to check the magic number.
// Check the file type and if it is an ELF file, contiune processing. Else print an error message
// and exit. Check the file's class and if it is 32-bit, continue processing for 32-bit. If it is
// 64-bit, continue processing for 64-bit. Else print an error message and exit. Check the encoding
// of the processor spesific data and if it is little endian, set the processing for little endian.
// If it is big endian, set the processing for big endian. Else print an error message and exit.
// After checking the magic number and the file type, print the ELF file's magic number content.
// Depending the file type, class and encoding, process the rest the ELF file's header information
// and store them in the ELF file header structure. Print the ELF file header information.

auto main(int argc, char** argv) -> int {
  const std::unordered_map<std::string, greeter::LanguageCode> languages{
      {"en", greeter::LanguageCode::EN},
      {"de", greeter::LanguageCode::DE},
      {"es", greeter::LanguageCode::ES},
      {"fr", greeter::LanguageCode::FR},
  };

  cxxopts::Options options(*argv, "A program to welcome the world!");

  std::string language;
  std::string name;

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("n,name", "Name to greet", cxxopts::value(name)->default_value("World"))
    ("l,lang", "Language code to use", cxxopts::value(language)->default_value("en"))
  ;
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  if (result["version"].as<bool>()) {
    std::cout << "Greeter, version " << GREETER_VERSION << std::endl;
    return 0;
  }

  auto langIt = languages.find(language);
  if (langIt == languages.end()) {
    std::cerr << "unknown language code: " << language << std::endl;
    return 1;
  }

  greeter::Greeter greeter(name);
  std::cout << greeter.greet(langIt->second) << std::endl;


  ElfFileLoader loader;
  loader.loadFile();

  ElfHeaderIdentificationParser identificationParser;
  identificationParser.parseIdentification(loader.getFileIdentification());

  ElfHeaderParser headerParser;
  headerParser.parseHeader(loader.getFileData());

  ElfFileHeader fileHeader = headerParser.getFileHeader();
  fileHeader.printHeaderInfo();

  return 0;
}
