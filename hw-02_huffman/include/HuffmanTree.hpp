#pragma once
#include "HuffmanTreeNode.hpp"
#include <queue>
#include <map>

namespace huffman {
    class HuffmanTree {
    private:
        std::unique_ptr<HuffmanTreeNode> head_;
        std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, comp> pq_;
        size_t header_size_ = 0;
        size_t data_size_ = 0;
    public:
        HuffmanTree();
        explicit HuffmanTree(const std::map<char, double>& dict);
        std::map<char, std::string> get_alphabet();
        void get_codes(HuffmanTreeNode* node, const std::string& code, std::map<char, std::string>& alphabet);
        static int binary_to_decimal(const std::string& in);
        static std::string decimal_to_binary(int in);
        void encode(const std::string& in_file_name, const std::string& out_file_name, std::map<char, std::string>& alphabet);
        void build_tree_from_code(std::string& code, char ch);
        void recreate_huffman_tree(const std::string& in_file_name);
        void decode(const std::string& in_file_name, const std::string& out_file_name);
        size_t data_size() const;
        size_t header_size() const;
    };
}