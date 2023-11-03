#pragma once
#include <memory>

namespace huffman {
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
        size_t freq() const;
        char ch() const;
        bool leaf();
        void set_left(HuffmanTreeNode* left);
        void set_right(HuffmanTreeNode* right);
        void set_ch(char ch);
    };

    struct comp{
        bool operator() (HuffmanTreeNode* left, HuffmanTreeNode* right);
    };
}