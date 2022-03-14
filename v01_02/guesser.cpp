#include "guesser.h"

using std::string;           
using std::vector;
using std::set;
using std::map;

char nextCharWhenWordIsNotInDictionary(const set<char>& selectedChars);
map<char, int> countOccurrences(const vector<string>& candidateWords);
char findMostFrequentChar(const map<char, int>& occurrences, const set<char>& selectedChars);
bool wordConformToMask(const string& word, const string& mask, char ch);

vector<string> filterWordsByLen(int wordLen, const vector<string>& vocabulary)
{
    vector<string> candidateWords;
    for (int i=0; i < vocabulary.size(); ++i) {
        if (vocabulary[i].size() == wordLen) {
            candidateWords.push_back(vocabulary[i]);
        }
    }
    return candidateWords;
}

vector<string> filterWordsByMask(const vector<string>& words, const string& mask, char ch)
{
    vector<string> newWords;
    for (vector<string>::const_iterator it = words.begin(); it != words.end(); ++it) {
        if (wordConformToMask(*it, mask, ch)) {
            newWords.push_back(*it);
        }
    }
    return newWords;
}

vector<string> filterWordsByIncorrectChar(const vector<string>& words, char ch)
{
    vector<string> newWords;
    for (vector<string>::const_iterator it = words.begin(); it != words.end(); ++it) {
        if (!isCharInWord(ch, *it)) {
            newWords.push_back(*it);
        }
    }
    return newWords;
}

/***
Tìm kí tự xuất hiện nhiều nhất
- Cài đặt cách 1: nếu xuất hiện nhiều lần trong 1 word thì cũng đếm nhiều lần
- Cách 2 (ko cài ở đây): nếu xuất hiện nhiền lần trong 1 word thì chỉ đểm một lần 
***/
char findBestChar(const vector<string>& candidateWords, const set<char>& selectedChars)
{
    if (candidateWords.size() == 0) {
        return nextCharWhenWordIsNotInDictionary(selectedChars);
    }

    map<char, int> occurrences = countOccurrences(candidateWords);
    char max_char = findMostFrequentChar(occurrences, selectedChars);

    if (max_char == 0) {
        return nextCharWhenWordIsNotInDictionary(selectedChars);
    } else {
        return max_char;
    }
}

char nextCharWhenWordIsNotInDictionary(const set<char>& selectedChars)
{
    for (char c = 'a'; c <= 'z'; ++c) {
        if (charNotInSet(c, selectedChars)) {
            return c;
        }
    }
    return 0;    
}

map<char, int> countOccurrences(const vector<string>& candidateWords)
{
    map<char, int> occurrences;
    int numOfWords = candidateWords.size();
    int numOfChars = candidateWords[0].size(); // Tat ca cac tu cung do dai
    for (int i = 0; i < numOfWords; ++i) {
        string word = candidateWords[i];
        set<char> charsOfWords;
        for (int j = 0; j < numOfChars; ++j) {
            if (charNotInSet(word[j], charsOfWords)) {
                occurrences[word[j]] += 1;
                charsOfWords.insert(word[j]);
            }
        }
    }
    return occurrences;

}

char findMostFrequentChar(const map<char, int>& occurrences, const set<char>& selectedChars)
{
    char max_char = 0;
    int max_occur = 0;
    for (map<char, int>::const_iterator it = occurrences.begin(); it != occurrences.end(); ++it) {
        if (max_occur < it->second && charNotInSet(it->first, selectedChars) ) {
            max_occur = it->second;
            max_char = it->first;
        }
    }
    return max_char;    
}

bool wordConformToMask(const string& word, const string& mask, char ch) 
{
    for (int i = 0; i < mask.size(); ++i) {
        if ( (mask[i] == ch && word[i] != ch) || (word[i] == ch && mask[i] != ch) ) {
            return false;
        }
    }
    return true;
}
