#include "Huffman.h"
#include "Files.h"

void test_encoding();

void test_decoding();

int main(int argc, char **argv) {
    string file_name;
    if (argc == 2) {
        cout << "Compressing..\n";
        file_name = argv[1];
        My_File my_file = read_file(file_name);
        Huffman huffman(my_file.freq);
        string compressed = huffman.encode(my_file.content);
        write_encoded_file(file_name, compressed, huffman.get_codes());
    } else if (argc == 3) {
        string flag = argv[1];
        if (flag != "-x") {
            cout << "invalid params only -x is valid\n";
            exit(1);
        }
        cout << "Extracting..\n";
        file_name = argv[2];
        My_File my_file = read_encoded_file(file_name);
        Huffman huffman(my_file.code);
        vector<int> original_file = huffman.decode(my_file.content);
        write_file("src.txt.decoded.", original_file);
    } else {
        cout << "invalid params\nCompress file -> ./huff [file name]\nExtract file  -> ./huff -x [file name]\n\n";
        exit(1);
    }

//    test_encoding();
//
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
    My_File my_file = read_encoded_file(string("src.txt") + string(EXTENSION));

    Huffman huffman(my_file.code);

    vector<int> original_file = huffman.decode(my_file.content);

    write_file("src.txt.decoded.", original_file);
}
