#include <iostream>
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "main.h"
#include <string>

using std::string;

struct TestStruct
{
    std::string testName;
    bool result;
    bool expected;
    std::string errorMsg;
};

bool verifyGenerateRandomNumber(const int min, const int max) {
    int myAnswer = generateRandomNumber(min, max);
    return (myAnswer >= min && myAnswer <= max);
}

bool verifyIsCharInWord(const char ch, const string& word){
    return isCharInWord(ch, word);
}


bool verifyFilterWordsByLen(int wordLen, const vector<string>& vocabulary, vector<string> answer){
    myAnswer = filterWordsByLen(wordLen, vocabulary);
    return myAnswer == answer;
}
bool verifyFindBestChar(const vector<string>& candidateWords, const set<char>& selectedChars, char answer){
    char myAnswer = findBestChar(candidateWords, selectedChars);
    return myAnswer == answer;
}
bool GetWordMask(char nextChar, string answer){
    myAnswer = getWordMask(nextChar);
    return myAnswer == answer;
}
bool verifyIsCorrectChar(char ch, const string& mask, bool answer){
    myAnswer = isCorrectChar(ch,mask);
    return myAnswer == answer;

}
bool verifyIsWholeWord(const string& mask, bool answer){
    myAnswer = isWholeWord(mask);
    return myAnswer == answer;
}

bool verifyFilterWordsByMask(const vector<string>& words, const string& mask, char ch, vector<string> answer){
    myAnswer = filterWordsByMask(words,mask,ch);
}


void runTestLoop(TestStruct testCases[], int testSize){
    for (int i = 0; i< testSize; i++){
        std::cout << testCases[i].testName + ": ";
        if (testCases[i].result == testCases[i].expected)
        {
            std::cout << "PASSED!";
        }
        else
        {
            std::cout << "FAILED!\n";
            std::cout << testCases[i].errorMsg;
            exit(1);
        }
    }
}

class Test : public CPPUNIT_NS::TestCase
{
    CPPUNIT_TEST_SUITE(Test);
    CPPUNIT_TEST(testGenerateRandomNumber);
    CPPUNIT_TEST(testIsCharInWord);
    CPPUNIT_TEST(testChooseWordFromList);
    CPPUNIT_TEST(testProcessData);
    CPPUNIT_TEST(testUpdateSecretWord);
    CPPUNIT_TEST(testUpdateEnteredChars);
    CPPUNIT_TEST(testUpdateIncorrectGuess);
    CPPUNIT_TEST(testGenerateHiddenCharacters);
    CPPUNIT_TEST(successTestExit);
    CPPUNIT_TEST_SUITE_END();

    public:
      void setUp(void) {}
      void tearDown(void) {}

    protected:
      void testGenerateRandomNumber(void) {
        const int testSize = 5;
        std::string sharedName = "\n[checkGenerateRandomNumber test] ";
        TestStruct checkGenerateRandomNumber[testSize]  = 
        {
            {
                sharedName + "test normal 1", 
                verifyGenerateRandomNumber(0, 10), 
                true,
                "Should return an integer number between 0 and 10\n"
            },
            {
                sharedName + "test normal 2", 
                verifyGenerateRandomNumber(15, 50), 
                true,
                "Should return an integer number between 15 and 50\n"
            },
            {
                sharedName + "test normal 3", 
                verifyGenerateRandomNumber(1, 100), 
                true,
                "Should return an integer number between 1 and 100\n"
            },
            {
                sharedName + "test normal 4", 
                verifyGenerateRandomNumber(1003, 2022), 
                true,
                "Should return an integer number between 1003 and 2022\n"
            },
            {
                sharedName + "test normal 5", 
                verifyGenerateRandomNumber(10, 10), 
                true,
                "Should return an integer number between 10 and 10\n"
            },
        };
        runTestLoop(checkGenerateRandomNumber, testSize);
      }

      void testIsCharInWord(void) {
        const int testSize = 5;
        std::string sharedName = "\n[checkIsCharInWord test] ";
        TestStruct checkIsCharInWord[testSize]  = 
        {
            {
                sharedName + "test normal 1", 
                verifyIsCharInWord('a', "dad"), 
                true,
                "Character 'a' exists in word dad. Should return true\n"
            },
            {
                sharedName + "test normal 2", 
                verifyIsCharInWord('a', "mom"), 
                false,
                "Character 'a' doesn't exist in word mom. Should return false\n"
            },
            {
                sharedName + "test normal 3", 
                verifyIsCharInWord('g', "strange"), 
                true,
                "Character 'g' exists in word strange. Should return true\n"
            },
            {
                sharedName + "test normal 4", 
                verifyIsCharInWord('m', "mommy"), 
                true,
                "Character 'm' exists in word mommy. Should return true\n"
            },
            {
                sharedName + "test normal 5", 
                verifyIsCharInWord('b', "animal"), 
                false,
                "Character 'b' doesn't exist in word animal. Should return false\n"
            },
        };
        runTestLoop(checkIsCharInWord, testSize);
      }

      

    void successTestExit(void) {
        std::cout << "all tests passed! \n";
        exit(0);
    }   
};  


CPPUNIT_TEST_SUITE_REGISTRATION(Test);

int main()
{
  CPPUNIT_NS::TestResult controller;

  CPPUNIT_NS::TestResultCollector result;
  controller.addListener(&result);

  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener(&progress);

  CPPUNIT_NS::TestRunner runner;
  runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
  runner.run(controller);

  return result.wasSuccessful() ? 0 : 1;
}
