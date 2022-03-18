#include "simpleai.h"

int readMaxGuess()
{
    int maxGuess;
    cout << endl << "Enter the number of incorrect guesses: ";
    cin >> maxGuess;
    return maxGuess;
}

int readWordLen()
{
    int wordLen;
    cout << endl << "Enter the number characters of your secret word: ";
    cin >> wordLen;
    return wordLen;
    
}

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

bool charNotInSet(char c, const set<char>& s) {
    return s.find(c) == s.end();
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
        for (int j = 0; j < numOfChars; ++j) {
            occurrences[word[j]] += 1;
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

string getWordMask(char nextChar)
{
    string mask;
    cout << "The next char is: " << nextChar << endl;
    cout << "Please give me your answer: ";
    cin >> mask;
    return mask;
}

bool isCorrectChar(char ch, const string& mask)
{
    return isCharInWord(ch, mask);
}

bool isWholeWord(const string& mask)
{
    return !isCharInWord(MASK_CHAR, mask);
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