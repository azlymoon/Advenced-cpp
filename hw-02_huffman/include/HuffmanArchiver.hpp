#pragma once
#include <memory>
#include <fstream>
#include "HuffmanTree.hpp"
#include "FrequencyCounter.hpp"

namespace huffman {
    class HuffmanArchiver {
    private:
        std::string input_path_;
        std::string output_path_;
        std::unique_ptr<HuffmanTree> tree_;
        std::unique_ptr<FrequencyCounter> freq_counter_;

    public:
        HuffmanArchiver(std::string input_path, std::string output_path);
        static size_t get_file_size (const std::string& file_path);
        void encode();
        void decode();
        HuffmanTree* get_tree();
        FrequencyCounter* get_freq_counter();
    };
}