//
// Created by ahmed on 12/15/17.
//

#ifndef HUFFMAN_COMPRESSION_DECOMPRESSION_HUFFMAN_H
#define HUFFMAN_COMPRESSION_DECOMPRESSION_HUFFMAN_H


#include "Node.h"

#define ENCODED "\\\\ENCODED\\\\"

class Huffman {
public:
    explicit Huffman(map<char, string> code);

    explicit Huffman(map<char, int> reversed_freq_map);

    string get_codes();

    string decode(queue<char> str);

    string encode(queue<char> str);

private:
    Node *root;
    vector<pair<int, char> > freq_arr;
    map<char, string> generated_codes;
    priority_queue<Node *, vector<Node *>, order_by_freq> heap;

    void __build_freq_map(map<char, int> reversed_freq_map);

    void __print(Node *node, const string &code_str = "");

    void __generate();
};


#endif //HUFFMAN_COMPRESSION_DECOMPRESSION_HUFFMAN_H
