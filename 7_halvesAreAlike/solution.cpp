#include <iostream>
#include <unordered_map>
#include <vector>
#include <utils/utils.hpp>

using namespace std;

// O(n) - time complexity
// O(1) - space complexity
bool halvesAreAlike(string s) {
    const std::vector<char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    size_t halfSize = s.size()/2;

    auto isVowel = [&vowels](const char& c) {
        return std::find(vowels.begin(), vowels.end(), c) != vowels.end();
    };

    int countPart1 = std::count_if(s.begin(), s.begin()+halfSize, isVowel);
    int countPart2 = std::count_if(s.begin()+halfSize, s.end(), isVowel);

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

    runTests(tests, [](const Test& test) {
        bool result = halvesAreAlike(test.s);
        cout << getTestResultInfo(test.s, test.expectedResult, result) << endl;
        return test.expectedResult == result;
    });
}
