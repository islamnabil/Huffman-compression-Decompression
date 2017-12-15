//
// Created by ahmed on 12/15/17.
//

#include "Huffman.h"

Huffman::Huffman(map<char, int> reversed_freq_map) {
    __build_freq_map(move(reversed_freq_map));
    __generate();
}

void Huffman::print_codes() {
    this->__print(this->root);
}

void Huffman::__build_freq_map(map<char, int> reversed_freq_map) {
    for (pair<char, int> reversed_pair: reversed_freq_map)
        this->freq_map[reversed_pair.second] = reversed_pair.first;
}

void Huffman::__print(Node *node, const string &code_str) {
    if (!node) return;

    if (node->data != INTERNAL) {
        cout << node->data << ": " << code_str << "\n";
        this->generated_codes[node->data] = stoi(code_str, nullptr, 2);
    }

    this->__print(node->left, code_str + "0");
    this->__print(node->right, code_str + "1");
}

void Huffman::__generate() {
    // Create a priority queue & inserts all characters
    for (pair<int, char> cur: this->freq_map)
        this->heap.push(new Node(cur.second, cur.first));

    // Iterate while size of this->heap doesn't become 1
    Node *left, *right, *top;
    while (this->heap.size() != 1) {
        // Extract the two minimum freq items from min this->heap
        left = this->heap.top(), this->heap.pop();
        right = this->heap.top(), this->heap.pop();

        // Create a new internal node with frequency equal to the sum of the two nodes frequencies.
        top = new Node(INTERNAL, left->freq + right->freq);
        top->left = left;
        top->right = right;
        this->heap.push(top);
    }
    // set the min this->heap root
    this->root = this->heap.top();
}
