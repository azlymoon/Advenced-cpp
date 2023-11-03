#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "HuffmanArchiver.hpp"
#include <string>
#include <fstream>

TEST_CASE("test_frequency_counter") {
    std::string input_path = "test_input.txt";
    huffman::FrequencyCounter freq_counter(input_path);

    freq_counter.calc_dictionary();

    std::map<char, double> expected_dict = {
            {'B', 0.125},
            {'H', 0.125},
            {'e', 0.25},
            {'l', 0.25},
            {'o', 0.125},
            {'y', 0.125}
    };

    REQUIRE(freq_counter.dictionary() == expected_dict);
}

TEST_CASE("test_encode") {
    std::string input_path = "test_input.txt";
    std::string output_path = "test_output.bin";
    huffman::HuffmanArchiver archiver(input_path, output_path);

    archiver.encode();

    std::map<char, std::string> expected_alphabet = {
            {'B', "000"},
            {'H', "10"},
            {'e', "001"},
            {'l', "01"},
            {'o', "111"},
            {'y', "110"}
    };

    REQUIRE(archiver.get_tree()->get_alphabet() == expected_alphabet);
}

TEST_CASE("test_decode") {
    std::string input_path = "test_output.bin";
    std::string output_path = "test_output.txt";
    huffman::HuffmanArchiver archiver(input_path, output_path);

    archiver.decode();

    std::ifstream out_file(output_path);
    std::string out_data;
    out_file >> out_data;

    std::string expected_data = "HelloBye";

    REQUIRE(out_data == expected_data);
}