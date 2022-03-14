/*
 + B0: Nạp danh sách từ vựng (vocabulary)
 + B1: Nhận vào số lần đoán tối đa N và độ dài từ phải đoán K. 
    Lọc danh sách từ vựng để chỉ chọn xem xét các từ có độ dài K.
    Danh sách các kí tự đã chọn ban đầu là rỗng.
 + B2: 
    Trong các từ đang xét, tìm kí tự xuất hiện nhiều nhất và không nằm trong các 
    kí tự đã chọn. Chọn kí tự này.
    Nhận vào kết quả trả đoán.
 + B3: 
    Nếu kết quả đoán đúng kí tự:
        Nếu đoán hết cả tử, sang B4 (thắng).
        Nếu chưa hết, lọc để giữ chỉ giữ lại xem xét từ vựng 
            với các từ có cả kí tự vừa đoán được tại vị trí được biêt; 
            Rồi quay lại B2. 
    Nếu đoán sai kí tự:
        Nếu hết số lần đoán, sang B4 (thua)
        Nếu chưa hết, tiếp tục đoán bằng cách quay lại B2
 + B4: Kết thúc
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "util.h"

using namespace std;

int readMaxGuess();
int readWordLen();
vector<string> filterWordsByLen(int wordLen, const vector<string>& vocabulary);
char findBestChar(const vector<string>& candidateWords, const set<char>& selectedChars);
string getWordMask(char nextChar);
bool isCorrectChar(char ch, const string& mask);
bool isWholeWord(const string& mask);
vector<string> filterWordsByMask(const vector<string>& words, const string& mask, char ch);

const char MASK_CHAR = '-';
int main()
{
    // B0
    //string wordFilePath = "data/hangman_wordlist.txt";
    string wordFilePath = "data/hangman_dictionary.txt";
    vector<string> vocabulary = readWordListFromFile(wordFilePath);
    /*
    vector<string> vocabulary;
    vocabulary.push_back("hello");
    vocabulary.push_back("good");
    vocabulary.push_back("bad");
    vocabulary.push_back("world");
    vocabulary.push_back("nice");
    */
    
    // B1
    int maxGuess = readMaxGuess();
    int wordLen = readWordLen();

    vector<string> candidateWords = filterWordsByLen(wordLen, vocabulary);
    set<char> selectedChars;
    int incorrectGuess = 0;
    string finalMessage = "";
    string mask(wordLen, MASK_CHAR);
    cout << "So your secret word looks like: " << mask << endl;

    //cout << "Max guess: " << incorrectGuess << " Word-len: " << wordLen << " Word num: " << candidateWords.size() << endl;

    while (true) {
        // B2
        char nextChar = findBestChar(candidateWords, selectedChars);
        if (nextChar == 0) {
            finalMessage =  "There is something wrong. I quit :|";
            break;
        }
        selectedChars.insert(nextChar);
        string responsedMask = getWordMask(nextChar);

        // B3
        if (isCorrectChar(nextChar, responsedMask)) {
            if (isWholeWord(responsedMask)) {
                finalMessage =  "It is easy :)";
                break;
            } else {
                candidateWords = filterWordsByMask(candidateWords, responsedMask, nextChar);
                //cout << "Size of candidates: " << candidateWords.size() << endl;
                //cout << candidateWords[0] << " " << candidateWords[candidateWords.size()-1] << endl;
            }
        } else {
            incorrectGuess += 1;        
            cout << "Incorrect guess count: " << incorrectGuess << endl;
        
            if (maxGuess <= incorrectGuess) {
                finalMessage = "Maybe, you should give me more times to guess :(";
                break;
            } else {
                // continue;
            }
        }
    }

    // B4
    cout << finalMessage << endl;
    return 0;
}

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
