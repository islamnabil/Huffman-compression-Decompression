//
// Created by ahmed on 12/15/17.
//

#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <cstring>
#include <iomanip>
#include "Files.h"

My_File read_file(const string &file_name) {
    My_File file = My_File();
    ifstream in(file_name);

    while (true) {
        int c = in.get();
        if (c == EOF) break;
        if (c == '\t' || c == ' ' || c == '\n')continue;

        file.content.push(c);
        file.freq[c]++;
    }

    in.close();
    return file;
}

void write_file(const string &file_name, vector<int> &content) {
    ofstream out(file_name.substr(0, file_name.find_last_of('.')), ios::out);
    for (int i: content) out << (char) i;
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
    map<string, int> codes;
    while (cnt--) {
        string key, value;
        in >> key >> value;
        codes[value] = key[0];
    }

    queue<int> content;
    while (true) {
        int c = in.get();
        if (c == EOF) break;
        if (c == '\n' || c == ' ' || c == '\t') continue;
        string decoded = decode(c);
        for (int bin: decoded)
            content.push(bin);
    }

    My_File my_file;
    my_file.content = content;
    my_file.code = codes;
    return my_file;
}

void write_encoded_file(const string &file_name, const string &content, const string &codes) {
    ofstream out(file_name + EXTENSION, ios::out);
    out << codes;

    string str_to_int;
    for (char c: content) {
        str_to_int.push_back(c);
        if (str_to_int.size() == 4) {
            out << hex << stoi(str_to_int, nullptr, 2);
            str_to_int = "";
        }
    }

    if (!str_to_int.empty())
        out << stoi(str_to_int, nullptr, 2) << endl;

    out.close();

    compare_file_size(file_name);
}

void compare_file_size(const string &file_name) {
    double original = -1, compressed = -1;
    struct stat st{};

    if (stat(file_name.c_str(), &st) == 0)
        original = st.st_size;

    if (stat((file_name + EXTENSION).c_str(), &st) == 0)
        compressed = st.st_size;

    cout << "\n\n" << file_name << " size: " << original / 1024 << " KB\n";
    cout << file_name << EXTENSION << " size: " << compressed / 1024 << " KB\n";
    cout << "Compression Ratio: " << (original - compressed) / original * 100 << " %\n\n";
}

string decode(int hex) {
    if (hex == '0') return "0000";
    else if (hex == '1') return "0001";
    else if (hex == '2') return "0010";
    else if (hex == '3') return "0011";
    else if (hex == '4') return "0100";
    else if (hex == '5') return "0101";
    else if (hex == '6') return "0110";
    else if (hex == '7') return "0111";
    else if (hex == '8') return "1000";
    else if (hex == '9') return "1001";
    else if (hex == 'a') return "1010";
    else if (hex == 'b') return "1011";
    else if (hex == 'c') return "1100";
    else if (hex == 'd') return "1101";
    else if (hex == 'e') return "1110";
    else if (hex == 'f') return "1111";
    else {
        cout << "unknown encoded char:" << hex << "\n";
        exit(1);
    }
}