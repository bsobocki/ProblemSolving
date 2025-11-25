#include <iostream>
#include <utils/utils.hpp>

using namespace std;

// in this solution we will use vector<bool>
// 1 <= k <= 10^5, so it won't be super big
// in this case unordered_set will be much slower
// because it is quite heavy because of hashing and additional storage 
int smallestRepunitDivByK(int k) {
    std::vector<bool> seen(k, false);
    // we want to start from 1, so in the loop we will do
    // 0 * 10 + 1 = 1 
    int remainder = 0;
    int countLen = 0;
    do {
        // for creating such number 11111...1 each time
        // we need to push back '1' into this number in two steps:
        // 1. add another digit at the end (* 10)
        // 2. insert 1 as the last place (+ 10)
        // Note: we don't need to store the whole number
        // we just check remainder each time so we will save only this
        remainder = (remainder * 10 + 1) % k;
        countLen++;
        // if we already seen this remainder then we are in a loop
        // In that case we can't find wanted number no mather how many iterations we will do
        if (seen[remainder]) return -1;
        seen[remainder] = true;
    } while(remainder != 0);
    return countLen;
}

struct Test {
    int k;
    int expectedResult;

    std::string getInfo() const {
        stringstream ss;
        ss << std::format("k: {}", k);
        return ss.str();
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        {1, 1},
        {2, -1},
        {3, 3},
        {4, -1}, // Divisible by 2
        {5, -1}, // Divisible by 5
        {6, -1}, // Divisible by 2
        {7, 6},  // 111111 is divisible by 7
        {10, -1}, // Ends in 0
        {11, 2},  // 11 is divisible by 11
        {12, -1},
        {13, 6},  // 111111 is divisible by 13
        {17, 16},
        {19, 18},
        {23, 22},
        {37, 3},
        {49, 42},
        {111, 3}, // k itself is a repunit
        {101, 4}, // 1111 / 101 = 11
    };

    runTests(tests, [](const Test& test){
        int result = smallestRepunitDivByK(test.k);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, result) << std::endl;
        return result == test.expectedResult;
    });
}