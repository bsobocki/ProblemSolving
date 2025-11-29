#include <iostream>
#include <utils/utils.hpp>

using namespace std;

// in place - it requires non-const reference,
// so it can be dangerous if we still returns vector as output,
// because in that case user doesn't expect any changes in input.
// However, my tests doesn't allow non-const reference 
// because the funtion passed as an argument of runTests
// needs to have const reference to Test object.
// That is why input parameters for tested functions are also const reference or passed by value.
//
// O(n) time complexity
// O(1) space complexity if we use vector<int>& nums as an argument,
// but in case when we pass nums by value we still makes copy, so O(n)
vector<int> inPlaceSortArrayByParity(vector<int> nums) {
    int left = 0, right = nums.size()-1;

    while(left < right) {
        if(nums[left] % 2 != 0) {
            if (nums[right] % 2 == 0)
                std::swap(nums[left++], nums[right--]);
            else right --;
        }
        else left++;
    }

    return nums;
}

// O(n) time complexity
// O(n) space complexity
vector<int> linearSortArrayByParity(const vector<int>& nums) {
    vector<int> vec;
    vec.resize(nums.size());

    int left = 0, right = nums.size()-1;

    // at start: 0 < left + right < size
    // at each step: we will increase left or decrease right by 1
    //    - so even if we go through whole vec by decreasing right then we achieve right == -1
    //      only after going through the whole array, so we won't try to get value at vec[-1]
    //    - the same with left - we will get left == vec.size() only after going through the whole array
    for(auto num : nums) {
        if(num % 2 == 0) vec[left++] = num;
        else vec[right--] = num;
    }

    return vec;
}

// using std::sort:
// O(n log n) time complexity
// O(n) space complexity
vector<int> sortArrayByParity(const vector<int>& nums) {
    auto vec = nums;

    std::sort(vec.begin(), vec.end(), [](int num1, int num2) {
        return num1%2==0;
    });

    return vec;
}

struct Test {
    vector<int> nums;

    std::string getInfo() const {
        std::stringstream ss;
        ss << nums;
        return ss.str();
    }
};

bool hasCorrectOrder(const vector<int>& result) {
    auto firstOdd = std::find_if(result.begin(), result.end(), [](const int num) {
        return num % 2 != 0;
    });

    auto anyEvenAfterOdd = std::find_if(firstOdd, result.end(), [](const int num){
        return num % 2 == 0;
    });

    return anyEvenAfterOdd == result.end();
}

// simple way - just sort both and check if they are the same
bool haveTheSameElements(const vector<int>& result, const vector<int>& input) {
    auto vec1 = result, vec2 = input;
    std::sort(vec1.begin(), vec1.end());
    std::sort(vec2.begin(), vec2.end());
    return vec1 == vec2;
}

bool isResultValid(const vector<int>& result, const vector<int>& input) {
    return hasCorrectOrder(result) && haveTheSameElements(result, input);
}

void runSolution() {
    const std::vector<Test> tests = {
        // Example 1: Mixed even and odd
        {{3, 1, 2, 4}},
        
        // Example 2: Single element
        {{0}},
        
        // All even numbers
        {{2, 4, 6, 8}},
        
        // All odd numbers
        {{1, 3, 5, 7}},
        
        // Already sorted (evens first)
        {{2, 4, 1, 3}},
        
        // Already sorted (odds first)
        {{1, 3, 2, 4}},
        
        // Alternating pattern
        {{1, 2, 3, 4, 5, 6}},
        
        // Two elements - both even
        {{2, 4}},
        
        // Two elements - both odd
        {{1, 3}},
        
        // Two elements - odd, even
        {{3, 2}},
        
        // Two elements - even, odd
        {{2, 3}},
        
        // Larger array with zeros
        {{0, 1, 0, 3, 12}},
        
        // All same even number
        {{4, 4, 4, 4}},
        
        // All same odd number
        {{5, 5, 5, 5}},
        
        // Mixed with duplicates
        {{3, 1, 2, 4, 2, 3, 1, 4}},
        
        // Large numbers
        {{5000, 4999, 2, 1}},
    };

    runTests(tests, [](const Test& test){
        auto sortedVec = sortArrayByParity(test.nums);
        auto linearSortedVec = linearSortArrayByParity(test.nums);
        auto inPlaceSortedVec = inPlaceSortArrayByParity(test.nums);
        bool result = isResultValid(sortedVec, test.nums) && isResultValid(linearSortedVec, test.nums) && isResultValid(inPlaceSortedVec, test.nums);
        std::cout << getTestResultInfo(test.getInfo(), inPlaceSortedVec, result) << std::endl;
        return result;
    });
}