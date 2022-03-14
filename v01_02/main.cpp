/*
 + B0: Nạp danh sách từ vựng (vocabulary)
 + B1: Nhận vào số lần đoán tối đa N và độ dài từ phải đoán K. 
    Lọc danh sách từ vựng để chỉ chọn xem xét các từ có độ dài K.
    Danh sách các kí tự đã chọn ban đầu là rỗng.
 + B2: 
    Trong các từ đang xét, tìm kí tự xuất hiện nhiều nhất và không nằm trong các 
    kí tự đã chọn. Chọn kí tự này.
    Nhận vào kết quả trả về.
 + B3: 
    Nếu kết quả đoán đúng kí tự:
        Nếu đoán hết cả từ, sang B4 (thắng).
        Nếu chưa hết, lọc để giữ chỉ giữ lại xem xét từ vựng 
            với các từ có cả kí tự vừa đoán được tại vị trí được biêt; 
            Rồi quay lại B2. 
    Nếu đoán sai kí tự:
        Nếu hết số lần đoán, sang B4 (thua)
        Nếu chưa hết, lọc để giữ chỉ giữ lại xem xét từ vựng 
            với các từ không có kí tự vừa đoán được; 
            Rồi quay lại B2. 
 + B4: Kết thúc
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "util.h"
#include "guesser.h"

using namespace std;

int readMaxGuess();
int readWordLen();
string getWordMask(char nextChar);
bool isCorrectChar(char ch, const string& mask);
bool isWholeWord(const string& mask);

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
                candidateWords = filterWordsByIncorrectChar(candidateWords, nextChar);
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

