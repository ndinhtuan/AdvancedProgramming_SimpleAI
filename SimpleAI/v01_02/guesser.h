#ifndef GUARD_guesser
#define GUARD_guesser

#include <string>
#include <vector>
#include <map>
#include <set>

#include "util.h"

const char MASK_CHAR = '-';

std::vector<std::string> filterWordsByLen(int wordLen, const std::vector<std::string>& vocabulary);
char findBestChar(const std::vector<std::string>& candidateWords, const std::set<char>& selectedChars);
std::vector<std::string> filterWordsByMask(const std::vector<std::string>& words, const std::string& mask, char ch);
std::vector<std::string> filterWordsByIncorrectChar(const std::vector<std::string>& words, char ch);

#endif