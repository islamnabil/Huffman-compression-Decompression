//
// Created by ahmed on 12/15/17.
//

#include "Huffman.h"

Huffman::Huffman(map<string, int> loaded_codes) {
    this->loaded_codes = move(loaded_codes);

    // print loaded codes
    cout << "\n\nLoaded codes:\n";
    for (pair<string, char> code: this->loaded_codes)
        cout << code.second << ": " << code.first << endl;

    cout << "\n\n";
}

Huffman::Huffman(map<int, int> reversed_freq_map) {
    __build_freq_map(move(reversed_freq_map));
    __generate();

    cout << "\n\nCodes:\n";
    __print(this->root);
    cout << "\n\n";
}

vector<int> Huffman::decode(queue<int> encoded_file) {
    string encoded_str;
    vector<int> decoded_str;
    while (!encoded_file.empty()) {
        encoded_str.push_back((char) encoded_file.front());
        encoded_file.pop();

        if (this->loaded_codes.find(encoded_str) != this->loaded_codes.end()) {
            decoded_str.push_back(this->loaded_codes[encoded_str]);
            encoded_str.clear();
        }
    }

    return decoded_str;
}

string Huffman::encode(queue<int> str) {
    string encoded_str;
    while (!str.empty()) {
        int c = str.front();
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

void Huffman::__build_freq_map(map<int, int> reversed_freq_map) {
    for (pair<int, int> reversed_pair: reversed_freq_map)
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
