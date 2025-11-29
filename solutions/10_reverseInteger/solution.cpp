#include <iostream>
#include <utils/utils.hpp>
#include <random>
#include <climits>

int reverse(int x) {
    int sign = 1;
    // for x == INT_MIN we just skip loop and return 0 at the end
    if (x < 0 && x != INT_MIN){
        sign = -1;
        x *= -1; // for while loop
    }

    int result = 0;
    while (x > 0) {
        // check if next step is possible, if not (result*10 will be bigger than INT_MAX)
        // then we will have an overflow, so return 0 
        if (result && result > INT_MAX/10) return 0; // overflow
        result = result * 10 + x % 10;
        x /= 10;
    }

    return sign * result;
}

struct Test {
    int x;
    int expectedResult;

    std::string getInfo() const {
        return "x: " + std::to_string(x);
    }
};

int reverseUsingLongLong(int x) {
    long long result = 0;
     int sign = 1;
    if (x < 0){
        sign = -1;
        x *= -1;
    }

    while(x > 0) {
        result = result * 10 + x % 10;
        x /= 10;
    }

    if (result > INT_MAX || result < INT_MIN) return 0;

    return (int)result*sign;
}

void runSolution() {
    std::vector<Test> tests = {
        // Basic positive numbers
        {123, 321},
        {120, 21},
        {1, 1},
        {10, 1},
        {100, 1},
        
        // Basic negative numbers
        {-123, -321},
        {-120, -21},
        {-1, -1},
        
        // Zero
        {0, 0},
        
        // Single digit numbers
        {5, 5},
        {9, 9},
        {-7, -7},
        
        // Multi-digit numbers
        {12345, 54321},
        {98765, 56789},
        {-54321, -12345},
        {-2147483641, -1463847412},
        
        // Numbers with trailing zeros
        {1000, 1},
        {10200, 201},
        {-5000, -5},
        {1000000, 1},
        {1200000, 21},
        
        // Overflow cases - positive (should return 0)
        {1534236469, 0},      // reversed: 9646324351 > INT_MAX
        {2147483647, 0},      // INT_MAX, reversed: 7463847412 > INT_MAX
        {1563847412, 0},      // reversed: 2147483651 > INT_MAX
        {2147483641, 1463847412},      // reversed: 1463847412 (this one is valid!)
        {1000000003, 0},      // reversed: 3000000001 > INT_MAX
        
        // Overflow cases - negative (should return 0)
        {-2147483648, 0},     // INT_MIN, reversed: -8463847412 < INT_MIN
        {-1563847412, 0},     // reversed: -2147483651 < INT_MIN
        {-1000000003, 0},     // reversed: -3000000001 < INT_MIN
        
        // Valid boundary cases (close to overflow but within range)
        {1463847412, 2147483641},    // reversed is close to INT_MAX but valid
        {-1463847412, -2147483641},  // reversed is close to INT_MIN but valid
        {1234567899, 0},             // reversed: 9987654321 > INT_MAX
        {-1234567899, 0},            // reversed: -9987654321 < INT_MIN
        
        // Edge cases near boundaries
        {1000000000, 1},             // reversed: 1
        {-1000000000, -1},           // reversed: -1
        {1111111111, 1111111111},    // reversed: 1111111111 (within range)
        {2000000000, 2},             // reversed: 2
        {-2000000000, -2},           // reversed: -2
    };

    runTests(tests, [](const Test& test) {
        int reversed = reverse(test.x);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, reversed) << std::endl;
        return reversed == test.expectedResult;
    });

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(INT_MIN, INT_MAX);

    std::cout << std::endl << "RUNNING RANDOM TESTS..." << std::endl << std::endl;

    bool allTestsPassed = true;
    for (int i=1; i<100; i++) {
        int x = dist(gen);
        int reversed = reverse(x);
        int expectedResult = reverseUsingLongLong(x);
        bool result = expectedResult == reversed;

        if (!result) {
            allTestsPassed = false;
            std::cout << getTestResultInfo("x: " + std::to_string(x), expectedResult, reversed) << std::endl;
        }
    }

    if (allTestsPassed)
        std::cout << greenStr("ALL TESTS PASSED!") << std::endl << std::endl;
}