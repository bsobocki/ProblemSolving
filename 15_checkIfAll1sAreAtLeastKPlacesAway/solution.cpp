#include <iostream>
#include <utils/utils.hpp>

using namespace std;

bool kLengthApart(vector<int> nums, int k) {
    auto it = std::find(nums.begin(), nums.end(), 1);
    while(it != nums.end()) {
        auto next = std::find(it+1, nums.end(), 1);
        if (next != nums.end() && (next - it - 1) < k) return false;
        it = next;
    }
    return true;
}

struct Test {
    vector<int> nums;
    int k;
    bool expectedResult;

    string getInfo() const {
        stringstream ss;
        ss << nums << " | k: " << k;
        return ss.str();
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        // Example cases
        {{1,0,0,0,1,0,0,1}, 2, true},
        {{1,0,0,1,0,1}, 2, false},
        
        // Edge cases - single element
        {{1}, 0, true},
        {{0}, 0, true},
        {{1}, 5, true},
        
        // Edge cases - no 1s
        {{0,0,0,0}, 2, true},
        
        // Edge cases - single 1
        {{1,0,0,0}, 2, true},
        {{0,0,0,1}, 2, true},
        {{0,1,0,0}, 2, true},
        
        // k = 0 cases
        {{1,1,1,1}, 0, true},
        {{1,0,1,0}, 0, true},
        
        // k = 1 cases
        {{1,0,1,0,1}, 1, true},
        {{1,1,0,0}, 1, false},
        {{0,1,1,0}, 1, false},
        
        // Two 1s - boundary cases
        {{1,0,1}, 1, true},
        {{1,0,1}, 2, false},
        {{1,0,0,1}, 2, true},
        {{1,0,0,1}, 3, false},
        
        // Multiple 1s - all valid
        {{1,0,0,0,1,0,0,0,1}, 3, true},
        {{1,0,0,0,0,1,0,0,0,0,1}, 4, true},
        
        // Multiple 1s - one pair too close
        {{1,0,0,1,0,0,0,1}, 3, false},
        {{1,0,0,0,1,0,1}, 2, false},
        
        // Consecutive 1s
        {{1,1}, 1, false},
        {{1,1,0,0}, 2, false},
        {{0,1,1,0}, 1, false},
        
        // Long arrays
        {{1,0,0,0,0,0,0,0,0,1}, 8, true},
        {{1,0,0,0,0,0,0,0,0,1}, 9, false},
        
        // All 0s except ends
        {{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, 10, true},
        
        // Large k value
        {{1,0,0,0,1}, 10, false},
        {{1,0,0,0,0}, 10, true},
        
        // Mixed patterns
        {{0,0,1,0,0,1,0,0,1,0,0}, 2, true},
        {{0,0,1,0,1,0,0,1,0,0}, 2, false},
    };

    runTests(tests, [](const Test& test){
        const bool areKLengthApart = kLengthApart(test.nums, test.k);
        cout << getTestResultInfo(test.getInfo(), test.expectedResult, areKLengthApart) << std::endl;
        return areKLengthApart == test.expectedResult;
    });
}