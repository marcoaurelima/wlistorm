/* ********************************* */
/*      name: wlistorm               */
/*    Author: Marco Aurelio 2021     */
/* ********************************* */

#include "functions.h"

int main(int argc, char *argv[])
{
    int min = 0;
    int max = 0;
    bool repeat = true;
    int type =  TYPE_OUT_TERM;
    std::string alphabet = "";
    std::vector<int> control = {0};
    std::string mask = "";
    bool hasMask = false;
    std::string filename = "";

    if(argc == 1){
        print_logo();
        std::cout << "\n\n  Type \"wlistorm -h\" to help.\n";
        printf("  ---------------------------\n\n");
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

    print_logo();

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
            type = TYPE_OUT_FILE;
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
    if(type == TYPE_OUT_FILE || type == TYPE_OUT_TERM_FILE){
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
