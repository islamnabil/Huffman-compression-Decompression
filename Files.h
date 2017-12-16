//
// Created by ahmed on 12/15/17.
//

#ifndef HUFFMAN_COMPRESSION_DECOMPRESSION_FILES_H
#define HUFFMAN_COMPRESSION_DECOMPRESSION_FILES_H


#include <queue>
#include <string>
#include <map>

#define ENCODED "\\\\ENCODED\\\\"

using namespace std;

typedef struct {
    map<char, string> code;
    map<char, int> freq;
    queue<char> content;
} My_File;

My_File read_file(const string &file_name);

void write_file(const string &file_name, const string &content);

My_File read_encoded_file(const string &file_name);

void write_encoded_file(const string &file_name, const string &content, const string &codes);

#endif //HUFFMAN_COMPRESSION_DECOMPRESSION_FILES_H
