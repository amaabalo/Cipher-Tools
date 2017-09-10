/* cipher_tools.hpp */

#include <unordered_map>
#include <vector>
#include <utility>


const float englishCharacterFrequencies[26] ={0.080, 0.015, 0.030, 0.040, 0.130, 0.020, 0.015, 0.060, 0.065, 0.005, 0.005, 0.035, 0.030, 0.070, 0.080,//
											  0.020, 0.002, 0.065, 0.060, 0.090, 0.030, 0.010, 0.015, 0.005, 0.020, 0.002};

int frequencyAnalysis(float *frequency_map, char *file_name);
void computeCorrelations(float *frequency_map, std::vector<std::pair<char, float>> &correlation_map);
bool getOption(std::string &option);
void displayPartialDecryption(char *file_name, int num_letters, int shift);
void tryShift(std::vector<std::pair<char, float>> &correlation_map, char *file_name, int num_letters);
bool isALetter(char c);
void replaceLetters(int argc, char *argv[]);
void shift(char *file_name, int shift);
