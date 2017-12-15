//
// Created by ahmed on 12/15/17.
//

#ifndef HUFFMAN_COMPRESSION_DECOMPRESSION_HUFFMAN_H
#define HUFFMAN_COMPRESSION_DECOMPRESSION_HUFFMAN_H


#include "Node.h"

class Huffman {
public:
    explicit Huffman(map<char, int> reversed_freq_map);

    void print_codes();

private:
    map<int, char> freq_map;
    map<char, int> generated_codes;
    Node *root;
    priority_queue<Node *, vector<Node *>, order_by_freq> heap;

    void __build_freq_map(map<char, int> reversed_freq_map);

    void __print(Node *node, const string &code_str = "");

    void __generate();
};


#endif //HUFFMAN_COMPRESSION_DECOMPRESSION_HUFFMAN_H
