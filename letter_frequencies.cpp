#include <stdlib.h>
#include "cipher_tools.hpp"
#include <iostream>

int main(int argc, char* argv[])
{   
    // user must enter name of encrypted file
    if (argc != 2)
    {   
        std::cout << "Usage: ./letter_frequencies <FILENAME>\n";
        exit(0);
    }    
    char *file_name = argv[1];
    float frequency_map[26];
    int num_letters = frequencyAnalysis(frequency_map, file_name);
    
    if (!num_letters)
    {
        std::cout << "Encrypted file is empty.\n";
        exit(0);
    }
}
