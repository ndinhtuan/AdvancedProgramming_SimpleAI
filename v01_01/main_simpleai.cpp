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
#include <fstream>
#include "simpleai.h"
 
#include "util.h"

using namespace std;

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
    //save_filter(1, wordLen, candidateWords, "-", '-');
    set<char> selectedChars;
    int incorrectGuess = 0;
    string finalMessage = "";
    string mask(wordLen, MASK_CHAR);
    cout << "So your secret word looks like: " << mask << endl;

    //cout << "Max guess: " << incorrectGuess << " Word-len: " << wordLen << " Word num: " << candidateWords.size() << endl;
    
    int idTestCase = 0;
    while (true) {
        // B2
        idTestCase += 1;
        string file_name_candidate_words = "test_data/find_best_char/candidate_words/" + to_string(idTestCase) + ".txt";
        string file_name_seletected_chars = "test_data/find_best_char/selected_chars/" + to_string(idTestCase) + ".txt";
        string file_name_next_char = "test_data/find_best_char/next_char/" + to_string(idTestCase) + ".txt";

        //ofstream file_candidate_words; file_candidate_words.open(file_name_candidate_words);
        //ofstream file_seletected_chars; file_seletected_chars.open(file_name_seletected_chars);
        //ofstream file_next_char; file_next_char.open(file_name_next_char);

        char nextChar = findBestChar(candidateWords, selectedChars);
        //printVector(candidateWords);
        //printVector(candidateWords, file_candidate_words); 
        //printSet(selectedChars, file_seletected_chars);
        //printChar(nextChar, file_next_char);

        //file_candidate_words.close();
        //file_seletected_chars.close();
        //file_next_char.close();

        if (nextChar == 0) {
            finalMessage =  "There is something wrong. I quit :|";
            break;
        }
        selectedChars.insert(nextChar);
        string responsedMask = getWordMask(nextChar);

        // B3
        cout << "nextChar: " << nextChar << endl;
        cout << "responsedMask: " << responsedMask << endl;
        cout << isCorrectChar(nextChar, responsedMask) << endl;
        if (isCorrectChar(nextChar, responsedMask)) {
            if (isWholeWord(responsedMask)) {
                finalMessage =  "It is easy :)";
                break;
            } else {
                candidateWords = filterWordsByMask(candidateWords, responsedMask, nextChar);
                //save_filter(0, 0, candidateWords, responsedMask, nextChar);
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