#include "Huffman.h"
#include "Files.h"

void test_encoding();

void test_decoding();

int main() {
    test_encoding();

//    test_decoding();

    return 0;
}

void test_encoding() {
    My_File file = read_file("src.txt");

    Huffman huffman(file.freq);

    string compressed = huffman.encode(file.content);

    write_encoded_file("src.txt", compressed, huffman.get_codes());
}

void test_decoding() {
    My_File my_file = read_encoded_file("src.txt.bin");

    Huffman huffman(my_file.code);

    string original_file = huffman.decode(my_file.content);

    write_file("src.txt", original_file);
}
