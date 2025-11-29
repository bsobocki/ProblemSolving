#include <iostream>
#include <utils/utils.hpp>

using namespace std;

int minimumOperations(const vector<int>& nums) {
    return std::count_if(nums.begin(), nums.end(), [](const int& num) {
        return num % 3 != 0;
    });
}

struct Test {
    vector<int> nums;
    int expectedResult;

    std::string getInfo() const {
        stringstream ss;
        ss << nums;
        return ss.str();
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        // Example 1: Mixed scenarios
        // 1->sub, 2->add, 3->ok, 4->sub. Total 3.
        { {1, 2, 3, 4}, 3 },

        // Example 2: All divisible by 3
        // 3->ok, 6->ok, 9->ok. Total 0.
        { {3, 6, 9}, 0 },

        // Scenario: All numbers need operations
        // 1(rem 1), 2(add 1), 4(rem 1), 5(add 1). Total 4.
        { {1, 2, 4, 5}, 4 },

        // Edge Case: Single element, needs operation
        { {1}, 1 },

        // Edge Case: Single element, needs no operation
        { {3}, 0 },

        // Edge Case: Large constraint value (50)
        // 50 % 3 = 2. Needs 1 op.
        { {50}, 1 },

        // Scenario: Empty array (though constraint says 1 <= len)
        // Handling just in case standard library behavior is tested
        { {}, 0 }
    };

    runTests(tests, [](const Test& test){
        int result = minimumOperations(test.nums);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, result) << std::endl;
        return result == test.expectedResult;
    });
}