#include <iostream>
#include <utils/utils.hpp>
#include <numeric>

using namespace std;

int minOperations(const vector<int>& nums, int k) {
    return std::accumulate(nums.begin(), nums.end(), 0) % k;
}

struct Test {
    vector<int> nums;
    int k;
    int expectedResult;

    std::string getInfo() const {
        stringstream ss;
        ss << nums << " | k: " << k;
        return ss.str();
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        // Example 1
        { {3, 9, 7}, 5, 4 },
        
        // Example 2
        { {4, 1, 3}, 4, 0 },
        
        // Example 3
        { {3, 2}, 6, 5 },

        // Edge case: Single element, remainder exists
        { {10}, 3, 1 }, 
        
        // Edge case: Sum is exactly k
        { {1, 2}, 3, 0 },

        // Edge case: Sum is less than k (needs to reduce to 0)
        { {1, 1}, 5, 2 },

        // Edge case: Larger numbers
        { {100, 200, 300}, 7, 5 } // Sum = 600. 600 % 7 = 5
    };


    runTests(tests, [](const Test& test){
        int result = minOperations(test.nums, test.k);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, result) << std::endl;
        return result == test.expectedResult;
    });
}