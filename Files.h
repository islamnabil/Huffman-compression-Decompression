//
// Created by ahmed on 12/15/17.
//

#ifndef HUFFMAN_COMPRESSION_DECOMPRESSION_FILES_H
#define HUFFMAN_COMPRESSION_DECOMPRESSION_FILES_H


#include <queue>
#include <string>
#include <map>

#define EXTENSION ".huff"
#define ENCODED "\\\\ENCODED\\\\"
#define SPACE '$'
#define NEW_LINE '%'
#define TAB '^'

using namespace std;

typedef struct {
    map<string, int> code;
    map<int, int> freq;
    queue<int> content;
} My_File;

My_File read_file(const string &file_name);

void write_file(const string &file_name, vector<int> &content);

My_File read_encoded_file(const string &file_name);

void write_encoded_file(const string &file_name, const string &content, const string &codes);

void compare_file_size(const string &file_name);

string decode(int hex);

#endif //HUFFMAN_COMPRESSION_DECOMPRESSION_FILES_H
