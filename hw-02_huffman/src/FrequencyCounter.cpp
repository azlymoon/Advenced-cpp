#include "FrequencyCounter.hpp"

namespace huffman {
    FrequencyCounter::FrequencyCounter(const std::string& input_path) : file_(input_path), size_file_(0){}

    FrequencyCounter::~FrequencyCounter() {
        file_.close();
    }

    std::map<char, double> FrequencyCounter::dictionary() {
        return dictionary_;
    }

    void FrequencyCounter::calc_dictionary() {
        if (file_) {
            char c;
            while (file_.get(c)) {
                dictionary_[c]++;
                size_file_++;
            }
        }

        for (auto & it : dictionary_) {
            dictionary_[it.first] = it.second / size_file_;
        }
    }
}