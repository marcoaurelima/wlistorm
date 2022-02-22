#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>

void print_logo();
void help();
void printWord(const std::string& alphabet,
               const std::vector<int>& control,
               bool repeatitions,
               int type,
               bool hasMask,
               std::string mask,
               std::string filename,
               FILE* file);

bool endOfwordlist (const std::string& alphabet, const std::vector<int>& control);
void increment     (std::string& alphabet, std::vector<int>& control);
bool allowWord     (const std::vector<int>& control, bool repeatitions);
void printWordlistSize(uint64_t lines, int alphabet_size, std::string info);

enum {
    TYPE_OUT_TERM,
    TYPE_OUT_FILE,
    TYPE_OUT_TERM_FILE
};


#endif
