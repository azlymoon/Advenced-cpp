#include "HuffmanTreeNode.hpp"

namespace huffman {
    HuffmanTreeNode::HuffmanTreeNode() : freq_(0), left_(nullptr), right_(nullptr) {}

    HuffmanTreeNode::HuffmanTreeNode(char ch, size_t freq) :
            ch_(ch),
            freq_(freq),
            left_(nullptr),
            right_(nullptr) {}

    HuffmanTreeNode::HuffmanTreeNode(HuffmanTreeNode *left, HuffmanTreeNode *right) :
            freq_(left->freq_ + right->freq_),
            left_(left),
            right_(right) {}

    HuffmanTreeNode* HuffmanTreeNode::left() {
        return left_.get();
    }

    HuffmanTreeNode *HuffmanTreeNode::right() {
        return right_.get();
    }

    size_t HuffmanTreeNode::freq() const {
        return freq_;
    }

    char HuffmanTreeNode::ch() const {
        return ch_;
    }

    bool HuffmanTreeNode::leaf() {
        return left() == nullptr && right() == nullptr;
    }

    void HuffmanTreeNode::set_left(HuffmanTreeNode* left) {
        left_ = std::unique_ptr<HuffmanTreeNode>(left);
    }

    void HuffmanTreeNode::set_right(HuffmanTreeNode* right) {
        right_ = std::unique_ptr<HuffmanTreeNode>(right);
    }

    void HuffmanTreeNode::set_ch(char ch) {
        ch_ = ch;
    }

    bool comp::operator()(huffman::HuffmanTreeNode *left, huffman::HuffmanTreeNode *right) {
        return left->freq() > right->freq();
    }
}