#include <iostream>
#include <utils/utils.hpp>
#include <array>
#include <unordered_set>

using namespace std;

// for better readability than std::pair
struct range {
    int start;
    int end;
};

// --------------------------------------------------------
// PHASE 1: Original Intuitive Solution (Sets)
// --------------------------------------------------------
// 0. result = 0
// 1. create ranges for each letter from the string {firstOccurence, lastOccurence}
// 2. create hashsets uniqueCharsFromRange (or array for each engilsh small letter with count 0 or 1 as an optimization) for unique chars in range
// 3. for each uniques in uniqueCharsFromRange: result += uniques.size();
// 4. return result
int countPalindromicSubsequence(string s) {
    constexpr size_t LETTERS_COUNT = 26;
    auto idx = [](const char c) { return c-'a'; };

    if (s.size() < 3) return 0;

    int result = 0;

    vector<range> ranges(LETTERS_COUNT, {-1, -1});

    // fill ranges for each letter from the string
    // if start hasn't been initialized then initialized it
    // each time overwrite end (we can have {i,i} or {i,j} where j > i)
    for (int i = 0; i < s.size(); i++) {
        char letterIdx = idx(s[i]);
        if (ranges[letterIdx].start == -1)
            ranges[letterIdx].start = i;
        ranges[letterIdx].end = i;
    }

    // we will count unique chars within ranges (without start and end)
    // those uniques between start and end are unique middles of our palindromes
    // e.g. for letter 'b' : { 'a', 'b', 'c' } -> we have 3 unique palindromes: "bab", "bbb", "bcb"
    vector<unordered_set<int>> uniquesFromRange(LETTERS_COUNT, unordered_set<int>());

    // first and last letter cannot be inside any range so we can skip them
    for (int i = 1; i < s.size()-1; i++) {
        for (int j = 0; j < LETTERS_COUNT; j++) {
            if (ranges[j].start < i && i < ranges[j].end) {
                uniquesFromRange[j].insert(s[i]);
            }
        }
    }

    // count all unique palindromes
    for (auto& uniques : uniquesFromRange) {
        result += uniques.size();
    }

    return result;
}

// --------------------------------------------------------
// PHASE 2: Data Structure Optimization (Vector vs Set)
// --------------------------------------------------------
// just one optimization unordered_set -> std::vector<int> with counts
// makes it much faster and lighter!!
int betterOptimizedCountPalindromicSubsequence(string s) {
    constexpr size_t LETTERS_COUNT = 26;
    auto idx = [](const char c) { return c-'a'; };

    if (s.size() < 3) return 0;

    int result = 0;

    vector<range> ranges(LETTERS_COUNT, {-1, -1});

    // fill ranges for each letter from the string
    // if start hasn't been initialized then initialized it
    // each time overwrite end (we can have {i,i} or {i,j} where j > i)
    for (int i = 0; i < s.size(); i++) {
        char letterIdx = idx(s[i]);
        if (ranges[letterIdx].start == -1)
            ranges[letterIdx].start = i;
        ranges[letterIdx].end = i;
    }

    // we will count unique chars within ranges (without start and end)
    // those uniques between start and end are unique middles of our palindromes
    // e.g. for letter 'b' : { 'a', 'b', 'c' } -> we have 3 unique palindromes: "bab", "bbb", "bcb"
    vector<vector<int>> uniquesFromRange(LETTERS_COUNT, vector<int>(LETTERS_COUNT, 0));

    // first and last letter cannot be inside any range so we can skip them
    for (int i = 1; i < s.size()-1; i++) {
        for (int j = 0; j < LETTERS_COUNT; j++) {
            if (ranges[j].start < i && i < ranges[j].end) {
                uniquesFromRange[j][idx(s[i])] = 1;
            }
        }
    }

    // count all unique palindromes
    for (auto& uniques : uniquesFromRange)
        for (auto count : uniques)
            result += count;

    return result;
}

// --------------------------------------------------------
// PHASE 3: Algorithmic Optimization (Inverted Loops)
// --------------------------------------------------------
// even better version: optimalization from version above + inverted loops
// because of that i could change vector<vector<int>> to one vector<int>
// to make it even faster we could use bits for counting letters because we only counts 0 or 1
int optimalCountPalindromicSubsequence(string s) {
    constexpr size_t LETTERS_COUNT = 26;
    auto idx = [](const char c) { return c-'a'; };

    if (s.size() < 3) return 0;

    int result = 0;

    vector<range> ranges(LETTERS_COUNT, {-1, -1});

    // fill ranges for each letter from the string
    // if start hasn't been initialized then initialized it
    // each time overwrite end (we can have {i,i} or {i,j} where j > i)
    for (int i = 0; i < s.size(); i++) {
        char letterIdx = idx(s[i]);
        if (ranges[letterIdx].start == -1)
            ranges[letterIdx].start = i;
        ranges[letterIdx].end = i;
    }

    // we will count unique chars within ranges (without start and end)
    // those uniques between start and end are unique middles of our palindromes
    // e.g. for letter 'b' : { 'a', 'b', 'c' } -> we have 3 unique palindromes: "bab", "bbb", "bcb"
    // we can skip letters that we know that they are outside our range - begin with i = start+1 and end with i = end-1
    std::vector<int> uniquesFromRangeCounts(LETTERS_COUNT, 0);
    for (int j = 0; j < LETTERS_COUNT; j++) {
        auto start = ranges[j].start;
        auto end = ranges[j].end;

        // letters between end and start is the distance - 1 
        // because we count steps from start to end but we don't want to count the last step to end
        // if we have those letters then we can proceed with further counting
        if (end - start - 1) {
            for (int i = start + 1; i < end; i++) {
                    uniquesFromRangeCounts[idx(s[i])] = 1;
            }
            // count all unique palindromes
            for (auto& count : uniquesFromRangeCounts) {
                result += count;
                count = 0;
            }
        }
    }

    return result;
}

// --------------------------------------------------------
// PHASE 4: Hardware Optimization (Bitmask)
// --------------------------------------------------------
// the best version: optimalization from version above + bitmap for checking seen letters
// because of that i could change vector<int> to one int
int optimalBitmapCountPalindromicSubsequence(string s) {
    constexpr size_t LETTERS_COUNT = 26;
    auto idx = [](const char c) { return c-'a'; };

    if (s.size() < 3) return 0;

    int result = 0;

    vector<range> ranges(LETTERS_COUNT, {-1, -1});

    // fill ranges for each letter from the string
    // if start hasn't been initialized then initialized it
    // each time overwrite end (we can have {i,i} or {i,j} where j > i)
    for (int i = 0; i < s.size(); i++) {
        char letterIdx = idx(s[i]);
        if (ranges[letterIdx].start == -1)
            ranges[letterIdx].start = i;
        ranges[letterIdx].end = i;
    }

    // we will count unique chars within ranges (without start and end)
    // those uniques between start and end are unique middles of our palindromes
    // e.g. for letter 'b' : { 'a', 'b', 'c' } -> we have 3 unique palindromes: "bab", "bbb", "bcb"
    // we can skip letters that we know that they are outside our range - begin with i = start+1 and end with i = end-1
    // use int as a bitmat for counting uniques characters from range
    int uniquesFromRangeCounts = 0;
    for (int j = 0; j < LETTERS_COUNT; j++) {
        auto start = ranges[j].start;
        auto end = ranges[j].end;

        // letters between end and start is the distance - 1 
        // because we count steps from start to end but we don't want to count the last step to end
        // if we have those letters then we can proceed with further counting
        if (end - start - 1) {
            uniquesFromRangeCounts = 0;
            // add every letter you found into uniquesFromRangeCounts as seen - bit 1
            for (int i = start + 1; i < end; i++) {
                    uniquesFromRangeCounts |= 1 << idx(s[i]);
                    // Optional: break early if we found all 26 chars
                    if (uniquesFromRangeCounts == 0x3FFFFFF) break;
            }
            // count all unique palindromes
            result += std::popcount((unsigned)uniquesFromRangeCounts);
        }
    }

    return result;
}

struct Test {
    string s;
    int expectedResult;

    std::string getInfo() const {
        return s;
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        // Example 1: "aba", "aaa", "aca"
        {"aabca", 3},
        
        // Example 2: No palindromes of length 3
        {"adc", 0},
        
        // Example 3: "bbb", "bcb", "bab", "aba"
        {"bbcbaba", 4},
        
        // Edge Case: Minimum length
        {"aba", 1},
        {"abc", 0},
        
        // All same characters
        {"aaaaa", 1}, // only "aaa"
        
        // Palindrome inside palindrome
        // 'a': inner "bcb" -> "aba", "aca" (2)
        // 'b': inner "c"   -> "bcb" (1)
        // Total: 3
        {"abcba", 3},
        
        // Disjoint palindromes
        // 'x': "y" -> "xyx" (1)
        // 'z': "w" -> "zwz" (1)
        {"xyxzwz", 2},
        
        // Nested ranges
        {"abbccbba", 4},
        
        // Empty middle
        {"abba", 1}
    };

    runTests(tests, [](const Test& test){
        int result = countPalindromicSubsequence(test.s);
        int resultBetterOptimized = betterOptimizedCountPalindromicSubsequence(test.s);
        int resultBetterOptimal = betterOptimizedCountPalindromicSubsequence(test.s);
        int resultBitmap = optimalBitmapCountPalindromicSubsequence(test.s);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, result) << std::endl;
        return  result == test.expectedResult &&
                resultBetterOptimized == test.expectedResult &&
                resultBetterOptimal == test.expectedResult;
    });


}