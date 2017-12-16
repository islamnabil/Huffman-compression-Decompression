//
// Created by ahmed on 12/15/17.
//

#include <fstream>
#include <iostream>
#include "Files.h"

My_File read_file(const string &file_name) {
    My_File file = My_File();
    ifstream in(file_name);

    while (true) {
        int c = in.get();
        if (c == EOF) break;
        if (c == ' ' || c == '\t' || c == '\n') continue;
        file.content.push((char) c);
        file.freq[(char) c]++;
    }

    in.close();
    return file;
}

void write_file(const string &file_name, const string &content) {
    ofstream out(file_name.substr(0, file_name.find_last_of('.')), ios::out);
    out << content;
    out.close();
}

My_File read_encoded_file(const string &file_name) {
    ifstream in(file_name, ios::in);
    string check;
    in >> check;
    if (check != ENCODED) {
        cout << "Unrecognized encoding format.\n";
        exit(1);
    }

    int cnt = 0;
    in >> cnt;
    map<char, string> codes;
    while (cnt--) {
        string key, value;
        in >> key >> value;
        codes[key[0]] = value;
    }

    queue<char> content;
    while (true) {
        int c = in.get();
        if (c == EOF) break;
        if (c == '\n' || c == ' ' || c == '\t') continue;
        content.push((char) c);
    }

    My_File my_file;
    my_file.content = content;
    my_file.code = codes;
    return my_file;
}

void write_encoded_file(const string &file_name, const string &content, const string &codes) {
    ofstream out(file_name + ".bin", ios::out);
    out << codes;
    out.close();

    out.open(file_name + ".bin", ios::app | ios::binary);
    string str_to_int;
    for (char c: content) {
        str_to_int.push_back(c);
        if (str_to_int.size() == 31) {
            out << stoi(str_to_int, nullptr, 2);
            str_to_int = "";
        }
    }
    if (!str_to_int.empty())
        out << stoi(str_to_int, nullptr, 2) << endl;
    out.close();
}