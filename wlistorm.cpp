/* ********************************* */
/*      name: wlistorm               */
/*    Author: Marco Aurelio 2021     */
/* ********************************* */

#include <iostream>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>

bool endOfwordlist(const std::string&, const std::vector<int>&);
void increment(std::string&, std::vector<int>&);
void printWord(const std::string&, const std::vector<int>&, bool, int, bool, std::string, std::string, FILE*);
void printControl(const std::string&, const std::vector<int>&, bool);
void printWordlistSize(uint64_t, int, std::string);
bool allowWord(const std::vector<int>&, bool);

enum {
    TYPE_CONSOLE,
    TYPE_FILE,
    TYPE_CONSOLE_FILE
};


void help(){

    system("clear");

    std::cout << "\n                       -------------------------------- ";
    std::cout << "\n  --------------------|  wlistorm - wordlist generator |--------------------";
    std::cout << "\n  --------------------|         byMarcoAurelio         |--------------------";
    std::cout << "\n                       -------------------------------- ";
    std::cout << "\n  > HELP\n\n  ";
    std::cout << "  wlistorm <min> <max> <alphabet> <(optional)>  \n";
    std::cout << "  \n";
    std::cout << "   <min>           Minimum lenght of the generate words. \n";
    std::cout << "   <max>           Maximum lenght of the generate words. \n";
    std::cout << "   <alphabet>      Charactere list you will use in the wordlist generation. \n";
    std::cout << "   -m <mask>       The mask you want use in the word. All the charactere \"~\" will \n";
    std::cout << "                   be replaced to alphabet given. \n";
    std::cout << "   -f <filename>   The name or path of file to save the wordlist. If you no set -f,  \n";
    std::cout << "                   the generate words will be show in the screen.\n";
    std::cout << "   -r              Set -f if you want no charactere repetitions in the generated word. \n";

    std::cout << "\n\n   EXAMPLE: \n";
    std::cout << "   wlistorm 8 8 abcd -m mask~~~~ -f wordlist.txt -r \n";
    std::cout << "\n  ---------------------------------------------------------------------------";
    std::cout << "\n\n";
}

int main(int argc, char *argv[])
{
    int min = 0;
    int max = 0;
    bool repeat = true;
    int type =  TYPE_CONSOLE;
    std::string alphabet = "";
    std::vector<int> control = {0};
    std::string mask = "";
    bool hasMask = false;
    std::string filename = "";

    for(int i=0;i<argc;i++){
        printf("- %s", argv[i]);
    }

    if(argc == 1){
        system("clear");
        std::cout << "\n  --------------------|  wlistorm 1.1 - wordlist generator |--------------------                byMarco (;\n\n";
        std::cout << "\n  > Type \"wlistorm -h\" to help.\n\n";
        printf("\n  ------------------------------------------------------------------------------\n\n");
        return 0;

    } else if(argc == 2){
       if(!strcmp(argv[1], "-h")){
            help();
            return 0;
        }
    } else if(argc >= 4){
        min = atoi(argv[1]);
        max = atoi(argv[2]);
        alphabet = argv[3];
    } else if(argc == 5){
        min = atoi(argv[1]);
        max = atoi(argv[2]);
        alphabet = argv[3];
        if(!strcmp(argv[4], "-r")){
            repeat = false;
        }
    }

    system("clear");
    std::cout << "\n  --------------------|  wlistorm 1.1 - wordlist generator |--------------------                byMarcoAur�lio (;\n\n";

    for(int i=1;i<argc;i++){
        if(!strcmp(argv[i], "-r")){
            repeat = false;
        }
        if(!strcmp(argv[i], "-m")){
            hasMask = true;
            mask = argv[i+1];

            if(repeat == false){
                int n = 0;
                for(auto& i : mask){if(i == '~'){n++;};}
                if((size_t)n != alphabet.size()){
                    std::cout << "  > ERROR: Incorret mask. The quantity of \"~\" must be " << alphabet.size() << ", but the inserted quantity was " << n << ".\n\n";
                    std::cout << "  ---------------------------------------------------------------------------\n\n";
                    return -1;
                }
            }
        }
        if(!strcmp(argv[i], "-f")){
            type = TYPE_FILE;
            filename = argv[i+1];
        }
    }

    /// wlistorm 8  8  abcd  -m ana~~~~~   -f  wordlist.txt  -r

    /// - The MAX value must not less than MIN value
    ///
    /// - Considering that dont have repetitions in each generate word:
    ///   1. The value of min and max couldn't be less than alphabet size.
    ///   2. The alphabet can have any size, but the number of different
    ///      characters must be larger or equals to nim ando max.

    if(min > max){
        std::cout << "  > ERROR: MIN value cannot be larger than MAX value.\n\n";
        std::cout << "  ---------------------------------------------------------------------------\n\n";
        return -1;
    }

    if(!repeat){
        std::string temp = alphabet;
        sort(temp.begin(), temp.end());
        auto res = std::unique(temp.begin(), temp.end());
        alphabet = std::string(temp.begin(), res);
        reverse(alphabet.begin(), alphabet.end());

        if(alphabet.size() < (size_t)min && alphabet.size() < (size_t)max){
            std::cout << "  > ERROR: There's not enought different characteres to this operation.\n";
            std::cout << "           \"" << alphabet << "\" " << "has " << alphabet.size() << " different characteres, but the minimum is " << min << ".\n\n";
            std::cout << "  ---------------------------------------------------------------------------\n\n";
            return -2;
        }

    }

    std::stringstream ss;
    ss << "\n  > INFO: | min: "<< min << " | max: " << max << " | alph: " << alphabet << ((mask.size() > 0)? " | mask: " + mask : "") <<  ((filename.size() > 0)? " | file: " + filename : "") << " | repeat char: " << ((repeat == true)? "yes" : "no") << " |     \n\n";
    std::cout << ss.str();
    std::cout << "\n\n  > Calculating size...\n\n";

    /// CALCULAR TAMANHO DA WORDLIST
    uint64_t size = 0;
    for(int i=0;i<((max-min)+1);i++){
        control.clear();
        for(int j=0;j<(min+i);j++){
            control.push_back(0);
        }

        while(!endOfwordlist(alphabet, control)){
            if(allowWord(control, repeat)){size++;}
            increment(alphabet, control);
        }
    }
    printWordlistSize(size, alphabet.size(), ss.str());
    control.clear();

    std::cout << "\n\n  > Continue? [y/n] ";
    char opt;
    std::cin >> opt;
    if(opt != 'y' && opt != 'Y'){
        std::cout << "\n  ---------------------------------------------------------------------------\n\n";
        return 0;
    }

     std::cout << "\n\n  > Please wait...\n\n";

    FILE* file = NULL;
    if(type == TYPE_FILE || type == TYPE_CONSOLE_FILE){
        file = fopen(filename.c_str(), "w");
        fclose(file);
        file = fopen(filename.c_str(), "a");
    }

    /// GRAVAR A WORDLIST
    for(int i=0;i<((max-min)+1);i++){

        control.clear();
        for(int j=0;j<(min+i);j++){
            control.push_back(0);
        }

        while(!endOfwordlist(alphabet, control)){
            printWord(alphabet, control, repeat, type, hasMask, mask, filename, file);
            increment(alphabet, control);
        }
    }

    std::cout << "\n\n  > Finished!\n\n";
    std::cout << "  ---------------------------------------------------------------------------\n\n";
    return 0;
}


bool endOfwordlist(const std::string& alphabet, const std::vector<int>& control){
    int n = alphabet.size();
    if(control[0] == n){
        return true;
    }
    return false;
}

void increment(std::string& alphabet, std::vector<int>& control){
    int n = alphabet.size();
    control[control.size()-1]++;
    bool loop = true;
    while(loop){
        loop = false;
        for(size_t i = control.size()-1;i>=1;i--){
            if(control[i] == n){
                control[i] = 0;
                control[i-1]++;
            }
        }
    }
}

bool hasRepetitions(const std::vector<int>& control){
   for(size_t i=0;i<control.size();i++){
        for(size_t j=0;j<control.size();j++){
            if(j != i){
                if(control[i]==control[j]){ return true; }
            }
        }
    }
    return false;
}

std::string insertMask(std::string word, std::string mask){
    std::string result = "";

    int j = 0;
    for(auto& i : mask){
        if(i != '~'){
            result += i;
        } else {
           result += word[j];
           ++j;
        }
    }
    return result;
}

void printWord(const std::string& alphabet, const std::vector<int>& control, bool repeatitions, int type, bool hasMask, std::string mask, std::string filename, FILE* file){
    static uint64_t count = 0;

    if(repeatitions){
        if(type == TYPE_CONSOLE || type == TYPE_CONSOLE_FILE){
            std::cout << "  [" << ++count << "] ";
        }
        std::string word;
        for(auto& item : control){
            word += alphabet[item];
        }

        if(type == TYPE_CONSOLE || type == TYPE_CONSOLE_FILE){
            if(hasMask){
                std::cout << insertMask(word, mask) << std::endl;
            } else {
                std::cout << word << std::endl;
            }
        }
        if(type == TYPE_FILE || type == TYPE_CONSOLE_FILE){
            if(hasMask){
                fprintf(file, "%s\n", insertMask(word, mask).c_str());
            } else {
                fprintf(file, "%s\n", word.c_str());
            }
        }

    } else {
        if(!hasRepetitions(control)){
            if(type == TYPE_CONSOLE || type == TYPE_CONSOLE_FILE){
                std::cout << "  [" << ++count << "] ";
            }
            std::string word;
            for(auto& item : control){
                word += alphabet[item];
            }

            if(type == TYPE_CONSOLE || type == TYPE_CONSOLE_FILE){
                if(hasMask){
                    std::cout << insertMask(word, mask) << std::endl;
                } else {
                    std::cout << word << std::endl;
                }
            }
            if(type == TYPE_FILE || type == TYPE_CONSOLE_FILE){
                if(hasMask){
                     fprintf(file, "%s\n", insertMask(word, mask).c_str());
                } else {
                    fprintf(file, "%s\n", word.c_str());
                }
            }
        }
    }
}

bool allowWord(const std::vector<int>& control, bool repeatitions){

    if(repeatitions){
        return true;
    } else {
        if(!hasRepetitions(control)){
            return true;
        }
    }
    return false;
}


void printWordlistSize(uint64_t lines, int alphabet_size, std::string info){
    uint64_t size = lines * alphabet_size;

    double kilobyte = ((double)size)/1024;
    double megabyte = ((double)size)/(1024 * 1024);
    double gigabyte = ((double)size)/(1024 * 1024 * 1024);
    double terabyte = 0; //((double)size)/(1024 * 1024 * 1024 * 1024);

    if(kilobyte > 1000){kilobyte = 0; }
    if(megabyte < 1){megabyte = 0; }
    if(gigabyte < 1){gigabyte = 0; }
    if(terabyte < 1){terabyte = 0; }


    system("clear");
    std::cout << "\n  --------------------|  wlistorm 1.1 - wordlist generator |--------------------";
    std::cout << "\n  --------------------|           byMarcoAurelio           |--------------------\n\n";
    std::cout << info;
    std::cout << "  > FILE SIZE:  " << " |  "
    << lines << " Ln  |  "
    << kilobyte << " Kb  |  "
    << megabyte << " Mb  |  "
    << gigabyte << " Gb  |  "
    << terabyte << " Tb  |  "
     "" << std::endl;

}
