#include "Huffman.h"

int main() {
    map<char, int> freq;
    freq['a'] = 5;
    freq['b'] = 9;
    freq['c'] = 12;
    freq['d'] = 13;
    freq['e'] = 16;
    freq['f'] = 45;

    Huffman huffman(freq);
    huffman.print_codes();
    return 0;
}
