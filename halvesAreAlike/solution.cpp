#include <iostream>
#include <unordered_map>

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

void runSolution() {
    std::cout << " TODO :) " << std::endl;
}