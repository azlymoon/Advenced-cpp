#include "HuffmanArchiver.hpp"
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
    if (argc != 6)
        return 1;

    std::string mode, in_file_path, out_file_path;

    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "-c") == 0) {
            mode = "encode";
        }
        if (std::strcmp(argv[i], "-u") == 0) {
            mode = "decode";
        }
        if (std::strcmp(argv[i], "-f") == 0 || std::strcmp(argv[i], "--file") == 0) {
            in_file_path = argv[i + 1];
        }
        if (std::strcmp(argv[i], "-o") == 0 || std::strcmp(argv[i], "-output") == 0) {
            out_file_path = argv[i + 1];
        }
    }

    huffman::HuffmanArchiver archiver(in_file_path, out_file_path);
    if (mode == "encode") {
        try {
            archiver.encode();
        } catch (...) {
            return 2;
        }
    }
    else if (mode == "decode") {
        try {
            archiver.decode();
        } catch (...) {
            return 2;
        }
    }

    return 0;
}
