#pragma once
#include <map>
#include <fstream>

namespace huffman {
    class FrequencyCounter {
    private:
        std::ifstream file_;
        size_t size_file_;
        std::map<char, double> dictionary_;
    public:
        explicit FrequencyCounter(const std::string& input_path);
        ~FrequencyCounter();
        std::map<char, double> dictionary();
        void calc_dictionary();

    };
}