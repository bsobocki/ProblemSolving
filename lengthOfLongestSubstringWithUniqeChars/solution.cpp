#include <iostream>
#include <unordered_map>

int lengthOfLongestSubstring(string s) {
    int start = 0;
    int maxSize = 0;
    std::unordered_map<char, int> seen;

    for (int i = 0; i < s.size(); i++) {
        auto chr = s[i];
        // check if the letter have been seen
        // and if the last occurrence
        // is the part of the substring we are checking
        if (seen.count(chr) and seen[chr] >= start) {
            if (maxSize < i - start) 
                maxSize = i - start;
            // move start to exclude seen letter
            start = seen[chr] + 1;
        }
        seen[chr] = i;
    }

    // after we reached the end of the string we need to check
    // whether the last checked substring is the longest one
    if (maxSize < s.size() - start)
        maxSize = s.size() - start;

    return maxSize;
}

void runSolution() {
    std::cout << " TODO :) " << std::endl;
}