#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <queue>

namespace huffman {
    class FrequencyCounter {
    private:
        std::ifstream file_;
        size_t size_file_;
        std::map<char, double> dictionary_;
    public:
        explicit FrequencyCounter(std::string input_path);
        ~FrequencyCounter();
        std::map<char, double> dictionary();
        void calc_dictionary();

    };

    class HuffmanTreeNode {
    private:
        char ch_ = 0;
        const size_t freq_;
        std::unique_ptr<HuffmanTreeNode> left_, right_;
    public:
        HuffmanTreeNode();
        HuffmanTreeNode(HuffmanTreeNode* left, HuffmanTreeNode* right);
        HuffmanTreeNode(char ch, size_t freq);
        HuffmanTreeNode* left();
        HuffmanTreeNode*  right();
        size_t freq();
        char ch();
        bool leaf();
        void set_left(HuffmanTreeNode* left);
        void set_right(HuffmanTreeNode* right);
        void set_ch(char ch);
    };

    struct comp{
        bool operator() (HuffmanTreeNode* left, HuffmanTreeNode* right);
    };

    class HuffmanTree {
    private:
        std::unique_ptr<HuffmanTreeNode> head_;
        std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, comp> pq_;
    public:
        HuffmanTree();
        explicit HuffmanTree(std::map<char, double> dict);
        std::map<char, std::string> get_alphabet();
        void get_codes(HuffmanTreeNode* node, std::string code, std::map<char, std::string>& alphabet);
        int binary_to_decimal(std::string in);
        std::string decimal_to_binary(int in);
        void encode(std::string in_file_name, std::string out_file_name, std::map<char, std::string>& alphabet);
        void build_tree_from_code(std::string& code, char ch);
        void recreate_huffman_tree(std::string in_file_name);
        void decode(std::string in_file_name, std::string out_file_name);
    };

    class HuffmanArchiver {
    private:
        std::string input_path_;
        std::string output_path_;
        std::unique_ptr<HuffmanTree> tree_;
    public:
        HuffmanArchiver(std::string input_path, std::string output_path);
        void encode();
        void decode();
    };
}
