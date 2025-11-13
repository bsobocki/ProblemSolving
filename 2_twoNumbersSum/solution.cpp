#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>
#include <utils/utils.hpp>
#include <functional>

using namespace std;

// O(N^2) - time complexity
// O(1) - space complexity
vector<int> twoSumBruteForce(const vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); i++)
        for (int j = 0; j < nums.size(); j++)
            if (i != j && nums[i] + nums[j] == target)
                return {i,j};
    return {-1, -1};
}

// O(N log_2 N) - time complexity - because of std::sort
// O(N) - space complexity
vector<int> twoSumVecSort(const vector<int>& nums, int target) {
    std::vector<std::pair<int, int>> numsIdxs(nums.size());

    for(int i=0; i<nums.size(); i++) {
        numsIdxs[i] = {nums[i], i};
    }

    std::sort(numsIdxs.begin(), numsIdxs.end(), [](auto& p1, auto& p2) {
        return p1.first < p2.first;
    });

    auto left = numsIdxs.begin();
    auto right = numsIdxs.end();
    right--;

    while(left != right) {
        int result = left->first + right->first;
        if (result == target) 
            return {left->second, right->second};
        else if (result < target)
            left++;
        else 
            right--;
    }

    return {-1, -1};
}

// O(N log_2 N) - time complexity - because of std::sort
// slower than vector
// O(N) - space complexity
vector<int> twoSumMultiMapSort(const vector<int>& nums, int target) {
    std::multimap<int, int> numsIdxs;

    for(int i=0; i<nums.size(); i++)
        numsIdxs.insert({nums[i], i});

    auto left = numsIdxs.begin();
    auto right = numsIdxs.end();
    right--;

    while(left != right) {
        int result = left->first + right->first;
        if (result == target) 
            return {left->second, right->second};
        else if (result < target)
            left++;
        else 
            right--;
    }

    return {-1, -1};
}

// O(N) - time complexity
// more space than vector and multimap
vector<int> twoSumHashMap(const vector<int>& nums, int target) {
    std::unordered_map<int, int> checked;

    for (int i = 0; i < nums.size(); i++) {
        int needed = target - nums[i];
        if (checked.count(needed))
            return {checked[needed], i};
        checked[nums[i]] = i;
    }

    return {-1, -1};
}

struct Test {
    vector<int> nums;
    int target;
    vector<int> expectedResult;
};

void runSolution() {
    const vector<Test> tests = {
        {{2,7,11,15}, 9, {0,1}},
        {{3,2,4}, 6, {1,2}},
        {{3,3}, 6, {0,1}},
        {{1,5,3,7,8,10}, 12, {1,3}},
        {{-1,-2,-3,-4,-5}, -8, {2,4}},
        {{0,4,3,0}, 0, {0,3}},
        {{-3,4,3,90}, 0, {0,2}}
    };

    auto runTest = [&](const std::string& title, std::function<vector<int>(const vector<int>&, int)> twoSumSolution) {
        std::cout << "\n=== " << title << " SOLUTION ===" << std::endl;
        runTests(tests, [&](const Test& test) {
            vector<int> result = twoSumSolution(test.nums, test.target);
            std::sort(result.begin(), result.end());
            auto expected = test.expectedResult;
            std::sort(expected.begin(), expected.end());
            cout << getTestResultInfo(to_string(test.nums) + " target:" + to_string(test.target), expected, result) << endl;
            return expected == result;
        });
    };

    runTest("BRUTE FORCE", twoSumBruteForce);
    runTest("SORT VECTOR", twoSumVecSort);
    runTest("SORT MULTIMAP", twoSumMultiMapSort);
    runTest("HASHMAP", twoSumHashMap);
}
