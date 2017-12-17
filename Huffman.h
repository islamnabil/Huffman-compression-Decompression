//
// Created by ahmed on 12/15/17.
//

#ifndef HUFFMAN_COMPRESSION_DECOMPRESSION_HUFFMAN_H
#define HUFFMAN_COMPRESSION_DECOMPRESSION_HUFFMAN_H


#include "Node.h"

#define ENCODED "\\\\ENCODED\\\\"

class Huffman {
public:
    explicit Huffman(map<string, int> loaded_code);

    explicit Huffman(map<int, int> reversed_freq_map);

    string get_codes();

    vector<int> decode(queue<int> encoded_file);

    string encode(queue<int> str);

private:
    Node *root;
    vector<pair<int, int> > freq_arr;
    map<int, string> generated_codes;
    map<string, int> loaded_codes;
    priority_queue<Node *, vector<Node *>, order_by_freq> heap;

    void __build_freq_map(map<int, int> reversed_freq_map);

    void __print(Node *node, const string &code_str = "");

    void __generate();
};


#endif //HUFFMAN_COMPRESSION_DECOMPRESSION_HUFFMAN_H
