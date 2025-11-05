#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// O(N^2) - time complexity
// O(1) - space complexity
vector<int> twoSumbruteForce(vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); i++)
        for (int j = 0; j < nums.size(); j++)
            if (i != j && nums[i] + nums[j] == target)
                return {i,j};
    return {-1, -1};
}

// O(N log_2 N) - time complexity - because of std::sort
// O(N) - space complexity
vector<int> twoSumVecSort(vector<int>& nums, int target) {
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
vector<int> twoSumMultiMapSort(vector<int>& nums, int target) {
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
vector<int> twoSumHashMap(vector<int>& nums, int target) {
    std::unordered_map<int, int> checked;

    for (int i = 0; i < nums.size(); i++) {
        int needed = target - nums[i];
        if (checked.count(needed))
            return {checked[needed], i};
        checked[nums[i]] = i;
    }

    return {-1, -1};
}

void runSolution() {
    std::cout << "TODO: TESTS: " << std::endl;

    std::cout << "BRUTE FORCE SOLUTION:" << std::endl;

    std::cout << "SORT VECTOR SOLUTION: " << std::endl;

    std::cout << "SORT MULTIMAP SOLUTION: " << std::endl;

    std::cout << "HASHMAP SOLUTION: " << std::endl;
}