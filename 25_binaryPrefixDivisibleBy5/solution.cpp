#include <iostream>
#include <utils/utils.hpp>

using namespace std;

vector<bool> prefixesDivBy5(vector<int>& nums) {
    vector<bool> result;
    // reserve space to avoid reallocations
    result.reserve(nums.size());

    int curr = 0;
    for (auto& x : nums) {
        // instead of calculating whole big number (too big to calculate)
        // we can just take moduulo 5 each time, because it is only thing that matters
        curr = (curr*2 + x) % 5;
        result.push_back(curr == 0);
    }

    return result;
}

struct Test {
    vector<int> nums;
    vector<bool> expectedResult;

    std::string getInfo() const {
        stringstream ss;
        ss << nums;
        return ss.str();
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        {{1,1,0,0,0,1,0,0,1}, {false,false,false,false,false,false,false,false,false}},
        {{0,1,1}, {true, false, false}},
        {{1,1,1}, {false, false, false}}
    };

    runTests(tests, [](const Test& test){
        auto nums = test.nums;
        vector<bool> result = prefixesDivBy5(nums);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, result) << std::endl;
        return result == test.expectedResult;
    });
}