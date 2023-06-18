#include "huffman.hpp"
#include <memory>
#include <queue>
#include <vector>

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

    size_t HuffmanTreeNode::freq() {
        return freq_;
    }

    char HuffmanTreeNode::ch() {
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

    FrequencyCounter::FrequencyCounter(std::string input_path) : file_(input_path), size_file_(0){}

    FrequencyCounter::~FrequencyCounter() {
        file_.close();
    }

    std::map<char, double> FrequencyCounter::dictionary() {
        return dictionary_;
    }

    void FrequencyCounter::calc_dictionary() {
        if (file_) {
            char c;
            while (!file_.eof()) {
                c = file_.get();
                dictionary_[c]++;
                size_file_++;
            }
        }

        for (auto it = dictionary_.begin(); it != dictionary_.end(); it++) {
            dictionary_[it->first] = it->second / size_file_;
        }
    }

    HuffmanTree::HuffmanTree() : head_(nullptr) {}

    HuffmanTree::HuffmanTree(std::map<char, double> dict) {
        for (auto it = dict.begin(); it != dict.end(); it++)
        {
            pq_.push(new HuffmanTreeNode(it->first, it->second));
        }

        std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, comp> temp(pq_);
        while (temp.size() != 1) {
            HuffmanTreeNode* left = temp.top(); temp.pop();
            HuffmanTreeNode* right = temp.top(); temp.pop();

            temp.push(new HuffmanTreeNode(left, right));
        }

        head_ = std::unique_ptr<HuffmanTreeNode>(temp.top()); temp.pop();
    }

    void HuffmanTree::build_tree_from_code(std::string& code, char ch) {
        HuffmanTreeNode* current = head_.get();
        for (size_t i = 0; i < code.size(); i++) {
            if (code[i] == '0') {
                if (current->left() == nullptr)
                    current->set_left(new HuffmanTreeNode);
                current = current->left();
            }
            else if (code[i] == '1') {
                if (current->right() == nullptr)
                    current->set_right(new HuffmanTreeNode);
                current = current->right();
            }
        }
        current->set_ch(ch);
    }

    void HuffmanTree::get_codes(HuffmanTreeNode* node, std::string code, std::map<char, std::string>& alphabet) {
        if (node == nullptr)
            return;

        if (node->leaf()) {
            alphabet[node->ch()] = code;
            return;
        }

        if (node->left())
            get_codes(node->left(), code + '0', alphabet);

        if (node->right())
            get_codes(node->right(), code + '1', alphabet);
    }

    std::map<char, std::string> HuffmanTree::get_alphabet() {
        std::map<char, std::string> alphabet;
        std::string code = "";
        get_codes(head_.get(), code, alphabet);
        return alphabet;
    }

    int HuffmanTree::binary_to_decimal(std::string in) {
        int result = 0;
        for (size_t i = 0; i < in.size(); i++)
            result = result * 2 + in[i] - '0';
        return result;
    }

    std::string HuffmanTree::decimal_to_binary(int in) {
        std::string temp = "";
        std::string result = "";
        while (in)
        {
            temp += ('0' + in % 2);
            in /= 2;
        }
        result.append(8 - temp.size(), '0');
        for (int i = temp.size() - 1; i >= 0; i--)
        {
            result += temp[i];
        }
        return result;
    }

    void HuffmanTree::encode(std::string in_file_name, std::string out_file_name, std::map<char, std::string>& alphabet) {
        std::ifstream in_file(in_file_name, std::ios::in);
        std::ofstream out_file(out_file_name, std::ios::out | std::ios::binary);
        std::string in = "", s = "";

        in += (char)pq_.size();
        std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, comp> temp(pq_);
        while (!temp.empty()) {
            HuffmanTreeNode* current = temp.top();
            in += current->ch();
            s.assign(127 - alphabet[current->ch()].size(), '0');
            s += '1';
            s.append(alphabet[current->ch()]);
            in += (char)binary_to_decimal(s.substr(0, 8));
            for (int i = 0; i < 15; i++) {
                s = s.substr(8);
                in += (char)binary_to_decimal(s.substr(0, 8));
            }
            temp.pop();
        }
        s.clear();

        char sym;
        in_file.get(sym);
        while (!in_file.eof()) {
            s += alphabet[sym];
            while (s.size() > 8) {
                in += (char)binary_to_decimal(s.substr(0, 8));
                s = s.substr(8);
            }
            in_file.get(sym);
        }
        int count = 8 - s.size();
        if (s.size() < 8) {
            s.append(count, '0');
        }
        in += (char)binary_to_decimal(s);
        in += (char)count;

        out_file.write(in.c_str(), in.size());
        in_file.close();
        out_file.close();
    }

    void HuffmanTree::recreate_huffman_tree(std::string in_file_name) {
        std::ifstream in_file(in_file_name, std::ios::in | std::ios::binary);
        unsigned char size;
        in_file.read(reinterpret_cast<char*>(&size), 1);
        head_ = std::make_unique<HuffmanTreeNode>();
        for (int i = 0; i < size; i++) {
            char ch;
            unsigned char code[16];
            in_file.read(&ch, 1);
            in_file.read(reinterpret_cast<char*>(code), 16);
            std::string code_s = "";
            for (int k = 0; k < 16; k++) {
                code_s += decimal_to_binary(code[k]);
            }
            int j = 0;
            while (code_s[j] == '0') {
                j++;
            }
            code_s = code_s.substr(j + 1);
            build_tree_from_code(code_s, ch);
        }
        in_file.close();
    }

    void HuffmanTree::decode(std::string in_file_name, std::string out_file_name) {
        std::ifstream in_file(in_file_name, std::ios::in | std::ios::binary);
        std::ofstream out_file(out_file_name, std::ios::out);
        unsigned char size;
        in_file.read(reinterpret_cast<char*>(&size), 1);
        in_file.seekg(-1, std::ios::end);
        char count0;
        in_file.read(&count0, 1);
        in_file.seekg(1 + 17 * size, std::ios::beg);

        std::vector<unsigned char> text;
        unsigned char textseg;
        in_file.read(reinterpret_cast<char*>(&textseg), 1);
        while (!in_file.eof()) {
            text.push_back(textseg);
            in_file.read(reinterpret_cast<char*>(&textseg), 1);
        }
        HuffmanTreeNode* current = head_.get();
        std::string code;
        for (size_t i = 0; i < text.size() - 1; i++) {
            code = decimal_to_binary(text[i]);
            if (i == text.size() - 2)
                code = code.substr(0, 8 - count0);
            for (size_t j = 0; j < code.size(); j++)
            {
                if (code[j] == '0')
                    current = current->left();
                else
                    current = current->right();
                if (current->leaf())
                {
                    out_file.put(current->ch());
                    current = head_.get();
                }
            }
        }
        in_file.close();
        out_file.close();
    }

    HuffmanArchiver::HuffmanArchiver(std::string input_path, std::string output_path)
            : input_path_(input_path), output_path_(output_path), tree_(nullptr) {}

    void HuffmanArchiver::encode() {
        FrequencyCounter freq_counter(input_path_);
        freq_counter.calc_dictionary();
        tree_ = std::make_unique<HuffmanTree>(freq_counter.dictionary());
        std::map<char, std::string> alphabet = tree_->get_alphabet();
        tree_->encode(input_path_, output_path_, alphabet);
    }

    void HuffmanArchiver::decode() {
        tree_ = std::make_unique<HuffmanTree>();
        tree_->recreate_huffman_tree(input_path_);
        tree_->decode(input_path_, output_path_);
    }

}
