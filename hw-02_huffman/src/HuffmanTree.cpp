#include "HuffmanTree.hpp"
#include <string>
#include <fstream>

namespace huffman {
    HuffmanTree::HuffmanTree() : head_(nullptr) {}

    HuffmanTree::HuffmanTree(const std::map<char, double>& dict) {
        for (auto & it : dict)
        {
            pq_.push(new HuffmanTreeNode(it.first, it.second));
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
        for (char i : code) {
            if (i == '0') {
                if (current->left() == nullptr)
                    current->set_left(new HuffmanTreeNode);
                current = current->left();
            }
            else if (i == '1') {
                if (current->right() == nullptr)
                    current->set_right(new HuffmanTreeNode);
                current = current->right();
            }
        }
        current->set_ch(ch);
    }

    void HuffmanTree::get_codes(HuffmanTreeNode* node, const std::string& code, std::map<char, std::string>& alphabet) {
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
        std::string code;
        get_codes(head_.get(), code, alphabet);
        return alphabet;
    }

    int HuffmanTree::binary_to_decimal(const std::string& in) {
        int result = 0;
        for (char i : in) {
            result = result * 2 + i - '0';
        }
        return result;
    }

    std::string HuffmanTree::decimal_to_binary(int in) {
        std::string temp;
        std::string result;
        while (in) {
            temp += ('0' + in % 2);
            in /= 2;
        }
        result.append(8 - temp.size(), '0');
        for (int i = temp.size() - 1; i >= 0; i--) {
            result += temp[i];
        }
        return result;
    }

    size_t HuffmanTree::header_size() const{
        return header_size_;
    }

    size_t HuffmanTree::data_size() const {
        return data_size_;
    }

    void HuffmanTree::encode(const std::string& in_file_name, const std::string& out_file_name, std::map<char, std::string>& alphabet) {
        std::ifstream in_file(in_file_name, std::ios::in);
        in_file.exceptions(std::ios::badbit);
        std::ofstream out_file(out_file_name, std::ios::out | std::ios::binary);
        out_file.exceptions(std::ios::badbit);
        std::string in, s;

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
        header_size_ = in.size();
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

        data_size_ = in.size() - header_size_;
        out_file.write(in.c_str(), in.size());
        in_file.close();
        out_file.close();
    }

    void HuffmanTree::recreate_huffman_tree(const std::string& in_file_name) {
        std::ifstream in_file(in_file_name, std::ios::in | std::ios::binary);
        in_file.exceptions(std::ios::badbit);
        unsigned char size;
        in_file.read(reinterpret_cast<char*>(&size), 1);
        head_ = std::make_unique<HuffmanTreeNode>();
        for (int i = 0; i < size; i++) {
            char ch;
            unsigned char code[16];
            in_file.read(&ch, 1);
            in_file.read(reinterpret_cast<char*>(code), 16);
            std::string code_s;
            for (unsigned char k : code) {
                code_s += decimal_to_binary(k);
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

    void HuffmanTree::decode(const std::string& in_file_name, const std::string& out_file_name) {
        std::ifstream in_file(in_file_name, std::ios::in | std::ios::binary);
        in_file.exceptions(std::ios::badbit);
        std::ofstream out_file(out_file_name, std::ios::out);
        out_file.exceptions(std::ios::badbit);
        unsigned char size;
        in_file.read(reinterpret_cast<char*>(&size), 1);
        in_file.seekg(-1, std::ios::end);
        char count0;
        in_file.read(&count0, 1);
        header_size_ = 1 + 17 * size;
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
            for (char j : code) {
                if (j == '0')
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
}