//
// Created by ahmed on 12/15/17.
//

#include "Huffman.h"

Huffman::Huffman(map<char, string> codes) {
    this->generated_codes = move(codes);

    // print loaded codes
    cout << "\n\nLoaded codes:\n";
    for (pair<char, string> code: this->generated_codes)
        cout << code.first << ": " << code.second << endl;
    cout << "\n\n";
}

Huffman::Huffman(map<char, int> reversed_freq_map) {
    __build_freq_map(move(reversed_freq_map));
    __generate();

    cout << "\n\nCodes:\n";
    __print(this->root);
    cout << "\n\n";
}

string Huffman::decode(queue<char> str) {
    char c;
    Node *cur = this->root;
    string decoded_str;
    while (!str.empty()) {
        c = str.front(), str.pop();
        if (c == '0')
            cur = cur->left;
        else
            cur = cur->right;

        if (cur->data != INTERNAL)
            decoded_str.push_back(cur->data);
    }
    return decoded_str;
}

string Huffman::encode(queue<char> str) {
    string encoded_str;
    while (!str.empty()) {
        char c = str.front();
        str.pop();
        encoded_str += this->generated_codes[c];
    }
    return encoded_str;
}

string Huffman::get_codes() {
    string codes;
    codes += ENCODED;
    codes.push_back('\n');
    codes += string(to_string(this->generated_codes.size()) + "\n");
    for (pair<char, string> code: this->generated_codes) {
        codes.push_back(code.first);
        codes += (": " + code.second);
        codes.push_back('\n');
    }
    return codes + "\n";
}

void Huffman::__build_freq_map(map<char, int> reversed_freq_map) {
    for (pair<char, int> reversed_pair: reversed_freq_map)
        this->freq_arr.emplace_back(make_pair(reversed_pair.second, reversed_pair.first));
    sort(freq_arr.begin(), freq_arr.end());
}

void Huffman::__print(Node *node, const string &code_str) {
    if (!node) return;

    if (node->data != INTERNAL) {
        cout << node->data << ": " << code_str << "\n";
        this->generated_codes[node->data] = code_str;
    }

    this->__print(node->left, code_str + "0");
    this->__print(node->right, code_str + "1");
}

void Huffman::__generate() {
    // Create a priority queue & inserts all characters
    for (pair<int, char> cur: this->freq_arr)
        this->heap.push(new Node(cur.second, cur.first));

    if (heap.empty()) {
        cout << "Error: Empty file\n";
        exit(1);
    }

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
