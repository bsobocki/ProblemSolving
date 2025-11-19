#include <iostream>
#include <utils/utils.hpp>
#include <unordered_set>

using namespace std;

// time complexity O(n^2) - but actually constraints makes it fast
// because we will find the next original no more than log_2 1000, so max 9 times
// so by taking it into account it is O(n)
// space complexity O(1)
int findFinalValue(const vector<int>& nums, int original) {
    while(std::find(nums.begin(), nums.end(), original) != nums.end())
        original *= 2;
    return original;
}

// time complexity O(n) amortized - but much slower because constraints make the solution above linear
// and here we have to build unordered set and makes lookup O(1) amortized, but it can be O(n)
// space complexity O(n)
int findFinalValueHashMap(const vector<int>& nums, int original) {
    std::unordered_set<int> numsMap(nums.begin(), nums.end());
    while(numsMap.count(original))
        original *= 2;
    return original;
}

struct Test {
    vector<int> nums;
    int original;
    int expectedValue;

    std::string getInfo() const {
        stringstream ss;
        ss << "nums: " << nums << " | original: " << original ;
        return ss.str();
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        // Example 1: Standard chain (3 -> 6 -> 12 -> 24)
        { {5, 3, 6, 1, 12}, 3, 24 },

        // Example 2: Original not found immediately
        { {2, 7, 9}, 4, 4 },

        // Case 3: Unordered array (2 -> 4 -> 8 -> 16)
        { {8, 2, 4}, 2, 16 },

        // Case 4: Single element found
        { {10}, 10, 20 },

        // Case 5: Single element not found
        { {10}, 5, 5 },

        // Case 6: Duplicates in array (should treat finding one instance as valid)
        // 1 -> 2 (found) -> 4 (not found)
        { {1, 1, 2}, 1, 4 },
        
        // Case 7: Longer chain
        // 1 -> 2 -> 4 -> 8 -> 16 -> 32
        { {16, 8, 4, 2, 1}, 1, 32 },

        // Case 8: Result grows larger than max input constraint (1000)
        // 500 -> 1000 -> 2000
        { {500, 1000}, 500, 2000 }
    };

    runTests(tests, [](const Test& test){
        int result = findFinalValueHashMap(test.nums, test.original);
        int resultHashMap = findFinalValueHashMap(test.nums, test.original);
        bool passed = result == test.expectedValue && resultHashMap == result;
        std::cout << getTestResultInfo(test.getInfo(), test.expectedValue, passed) << std::endl;
        return passed;
    });
}