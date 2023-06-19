#include "HuffmanArchiver.hpp"
#include "FrequencyCounter.hpp"
#include <iostream>

namespace huffman {
    HuffmanArchiver::HuffmanArchiver(std::string input_path, std::string output_path)
            : input_path_(std::move(input_path)), output_path_(std::move(output_path)), tree_(nullptr) {}

    HuffmanTree *HuffmanArchiver::get_tree() {
        return tree_.get();
    }

    FrequencyCounter *HuffmanArchiver::get_freq_counter() {
        return freq_counter_.get();
    }

    void HuffmanArchiver::encode() {
        freq_counter_ = std::make_unique<FrequencyCounter>(input_path_);
        freq_counter_->calc_dictionary();
        tree_ = std::make_unique<HuffmanTree>(freq_counter_->dictionary());
        std::map<char, std::string> alphabet = tree_->get_alphabet();
        tree_->encode(input_path_, output_path_, alphabet);
        std::cout << get_file_size(input_path_) << "\n" <<
                  tree_->data_size() << "\n" <<
                  tree_->header_size();
    }

    void HuffmanArchiver::decode() {
        tree_ = std::make_unique<HuffmanTree>();
        tree_->recreate_huffman_tree(input_path_);
        tree_->decode(input_path_, output_path_);
        std::cout << get_file_size(input_path_) - tree_->header_size() << "\n" <<
                  get_file_size(output_path_)<< "\n" <<
                  tree_->header_size();
    }

    size_t HuffmanArchiver::get_file_size(const std::string& file_path) {
        std::ifstream file (file_path, std::ios::binary);
        file.seekg(0, std::ios::end);
        size_t file_size = file.tellg();
        return file_size;
    }
}