#include <iostream>
#include <unordered_map>
#include <vector>
#include <utils/utils.hpp>

using namespace std;

bool halvesAreAlike(string s) {
    int countPart1 = 0;
    int countPart2 = 0;
    size_t halfSize = s.size()/2;
    char vowels [] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    auto isVowel = [&vowels](const char& c) {
        for (int i=0; i<10; i++)
            if (c == vowels[i]) return true;
        return false;
    };

    for (int i=0; i<halfSize; i++) {
        if (isVowel(s[i])) countPart1 ++;
        if (isVowel(s[i+halfSize])) countPart2 ++;
    }
    return countPart1 == countPart2;
}

struct Test {
    string s;
    bool expectedResult;
};

void runSolution() {
    const vector<Test> tests = {
        {"book", true},
        {"textbook", false},
        {"MerryChristmas", false},
        {"AbCdEfGh", true},
        {"aA", true},
        {"sY", true}, // Y is not counted as vowel
        {"sO", false},
        {"Aa", true},
        {"tkPAllotte", false},
        {"tkPAllotts", true},
    };

    std::cout << getResultInfoHeader() << endl;
    for (auto& test : tests) {
        bool result = halvesAreAlike(test.s);
        cout << getTestResultInfo(test.s, test.expectedResult, result) << endl;
    }
}
