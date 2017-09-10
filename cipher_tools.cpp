/* cipher_tools.cpp */
#include "cipher_tools.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>

int frequencyAnalysis(float *frequency_map, char *file_name)
{
	for (int i = 0; i < 26; i++)
		frequency_map[i] = 0;
	FILE *encrypted_file = fopen(file_name, "r");
	if (encrypted_file != NULL)
	{
		
		float n = 0; // the number of letters in the file
		char c = std::tolower(fgetc(encrypted_file));
		
		while (c != EOF)
		{
			if (isALetter(c))
			{
				frequency_map[c - 'a']++;
				n++;	
			}
			c = std::tolower(fgetc(encrypted_file));
		}

		fclose(encrypted_file);

		for (int j = 0; j < 26; j++)
		{
			frequency_map[j] /= n;	
			std::cout << (char)(j + 'a') << " : " << frequency_map[j] << std::endl;
		}
		return (int)n;
	}
	else
	{
		std::cout << "File cannot be opened.\n";
		exit(0);
	}
}

// Correlations are sorted in descending order
bool sortBySecond(const std::pair<char, float> &a, const std::pair<char, float> &b)
{
	return (a.second > b.second);
}

void computeCorrelations(float *frequency_map, std::vector<std::pair<char, float>> &correlation_map)
{
	float correlation;
	for (int shift = 0; shift < 26; shift++)
	{
		correlation = 0;
		for (int c = 0; c < 26; c++)
		{
			correlation += frequency_map[c] * englishCharacterFrequencies[((c - shift) + 26) % 26];
		}
		correlation_map.push_back(std::make_pair(shift, correlation)); 
	}

	std::sort(correlation_map.begin(), correlation_map.end(), sortBySecond);
}

bool getOption(std::string &option)
{
	bool stop_loop = false;
	while(true)
	{
		std::cout << "Is this decryption intelligible?\n";
		std::cin >> option;
		if (option == "n")
			break;
		else if (option == "q" || option == "y")
		{
			stop_loop = true;
			break;
		}
		else
			std::cout << "Enter 'y' if the deciphered text is intelligible, 'n' if it is not, or 'q' to stop\n";
	}
	return stop_loop;
}

void tryShift(std::vector<std::pair<char, float>> &correlation_map, char *file_name, int num_letters)
{

	std::string option;
	bool stop_loop = false;
	int i = 0;	
	do
	{
		// display decrypted text using shift
		displayPartialDecryption(file_name, (num_letters < 50) ? num_letters : 50, correlation_map[i].first);				
		// get user options
		std::cout << "Shift: " << (int)correlation_map[i].first << "\n";
		stop_loop = getOption(option);
		if (stop_loop) break;
		i++;
	}while(i < correlation_map.size());

	if (option == "n") 
		std::cout << "All possible shifts have been attempted\n";
	else if (option == "q")
		std::cout << "Exited.\n";
	else
		displayPartialDecryption(file_name, num_letters, correlation_map[i].first);				
		// save deciphered text to file

}

void displayPartialDecryption(char *file_name, int num_letters, int shift)
{

	
	FILE *encrypted_file = fopen(file_name, "r");
	if (encrypted_file == NULL)
	{
		std::cout << "Could not open encrypted file.\n";
		exit(1);
	}
	
	int n = 0;
	while (n < num_letters)
	{
		char c = std::tolower(fgetc(encrypted_file));
		if (isALetter(c))
		{
			c -= 'a';
			c = ((c - shift) + 26) % 26;
			c += 'a';
			n++;
		}
		std::cout << c;
	}
	std::cout << "\n";
}

bool isALetter(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void replaceLetters(int argc, char *argv[])
{
	if ((argc % 2))
	{
		std::cout << "USAGE: ./replaceLetters <FILENAME> <LETTER-TO-REPLACE> <REPLACEMENT>\n";
		exit(0);
	}

	std::string old_file_name(argv[1]);
	old_file_name = old_file_name.substr(0, old_file_name.length() - 4) + "_old.txt";
	rename(argv[1], old_file_name.c_str());
	char *recent_file_name = argv[1];
	FILE *file1 = fopen(old_file_name.c_str(), "r");
	FILE *file2 = fopen(recent_file_name, "w");
	char c = fgetc(file1);
	char replacement;
	while (c != EOF)
	{
		replacement = c;	
		for (int i = 2; i < argc; i += 2)
		{
			if (c == argv[i][0])
			{
				replacement = toupper(argv[i + 1][0]);
				break;
			}
		}

		fputc(replacement, file2);
		c = fgetc(file1);
	}
	fclose(file1);
	fclose(file2);
}

void shift(char *file_name, int shift)
{
	FILE *encrypted_file = fopen(file_name, "r");
	std::string new_file_name(file_name);
	new_file_name = new_file_name.substr(0, new_file_name.length() - 4) + "_shifted.txt";
	FILE *decrypted_file = fopen(new_file_name.c_str(), "w");

	char c = tolower(fgetc(encrypted_file));

	while (c != EOF)
	{
		if (isALetter(c))
		{
			c -= 'a';
			c = ((c + shift) + 26) % 26;
			c += 'a';
 
			fputc(c, decrypted_file);
		}
		else
			fputc(c, decrypted_file);
		c = tolower(fgetc(encrypted_file));
	}
}
