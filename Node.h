//
// Created by ahmed on 12/15/17.
//

#ifndef HUFFMAN_COMPRESSION_DECOMPRESSION_NODE_H
#define HUFFMAN_COMPRESSION_DECOMPRESSION_NODE_H


#include <bits/stdc++.h>

#define INTERNAL '~'

using namespace std;

class Node {
public:
    char data;
    int freq;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(char data, int freq) {
        this->data = data;
        this->freq = freq;
    }
};

struct order_by_freq {
    bool operator()(Node *l, Node *r) {
        return (l->freq > r->freq);
    }
};


#endif //HUFFMAN_COMPRESSION_DECOMPRESSION_NODE_H
