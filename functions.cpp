#include "functions.h"

void print_logo(){
  system("clear");
  std::cout << R"(
  __      __.__  .__          __
 /  \    /  \  | |__| _______/  |_  ___________  _____
 \   \/\/   /  | |  |/  ___/\   __\/  _ \_  __ \/     \
  \        /|  |_|  |\___ \  |  | (  <_> )  | \/  Y Y  \
   \__/\  / |____/__/____  > |__|  \____/|__|  |__|_|  /
        \/               \/      wordlist generator  \/)";
}

void help(){

    print_logo();

    std::cout << "\n\n   HOW TO USE:\n";
    std::cout << "   wlistorm <min> <max> <alphabet> <(optional)>  \n\n";
    std::cout << "   <min>           Minimum lenght of the generate words. \n";
    std::cout << "   <max>           Maximum lenght of the generate words. \n";
    std::cout << "   <alphabet>      Charactere list you will use in the wordlist generation. \n";
    std::cout << "   -m <mask>       The mask you want use in the word. All the charactere \"~\" will \n";
    std::cout << "                   be replaced to alphabet given. \n";
    std::cout << "   -f <filename>   The name or path of file to save the wordlist. If you no set -f,  \n";
    std::cout << "                   the generate words will be show in the screen.\n";
    std::cout << "   -r              Set -r if you want no charactere repetitions in the generated word. \n";

    std::cout << "\n   EXAMPLE: \n";
    std::cout << "   wlistorm 8 8 abcd -m mask~~~~ -f wordlist.txt -r \n";
    std::cout << "\n  ---------------------------------------------------------------------------";
    std::cout << "\n\n";
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
        if(type == TYPE_OUT_TERM || type == TYPE_OUT_TERM_FILE){
            std::cout << "  [" << ++count << "] ";
        }
        std::string word;
        for(auto& item : control){
            word += alphabet[item];
        }

        if(type == TYPE_OUT_TERM || type == TYPE_OUT_TERM_FILE){
            if(hasMask){
                std::cout << insertMask(word, mask) << std::endl;
            } else {
                std::cout << word << std::endl;
            }
        }
        if(type == TYPE_OUT_FILE || type == TYPE_OUT_TERM_FILE){
            if(hasMask){
                fprintf(file, "%s\n", insertMask(word, mask).c_str());
            } else {
                fprintf(file, "%s\n", word.c_str());
            }
        }

    } else {
        if(!hasRepetitions(control)){
            if(type == TYPE_OUT_TERM || type == TYPE_OUT_TERM_FILE){
                std::cout << "  [" << ++count << "] ";
            }
            std::string word;
            for(auto& item : control){
                word += alphabet[item];
            }

            if(type == TYPE_OUT_TERM || type == TYPE_OUT_TERM_FILE){
                if(hasMask){
                    std::cout << insertMask(word, mask) << std::endl;
                } else {
                    std::cout << word << std::endl;
                }
            }
            if(type == TYPE_OUT_FILE || type == TYPE_OUT_TERM_FILE){
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


    print_logo();

    std::cout << info;
    std::cout << "  > FILE SIZE:  " << " |  "
    << lines << " Ln  |  "
    << kilobyte << " Kb  |  "
    << megabyte << " Mb  |  "
    << gigabyte << " Gb  |  "
    << terabyte << " Tb  |  "
     "" << std::endl;

}
