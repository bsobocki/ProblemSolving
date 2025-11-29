#include <iostream>
#include <utils/utils.hpp>
#include <numeric>
#include <climits>

using namespace std;

// the best idea - check if sum of all nums is divisible by 3
// if not then:
// if sum % 3 == 1 remove minimum value that gives 1 after modulo 3
//    - minimum value x where x % 3 == 1
//    - or two minimum values x,y where (x % 3 == 2 && y % 3 == 2) because then x+y % 3 == 1
// if sum % 3 == 2 remove minimum value that gives 2 after modulo 3
//    - minimum value x where x % 3 == 2
//    - or two minimum values x,y where (x % 3 == 1 && y % 3 == 1) because then x+y % 3 == 2
int maxSumDivThree(vector<int>& nums) {
    if (nums.empty()) return 0;

    int sum = std::accumulate(nums.begin(), nums.end(), 0);

    if (sum % 3 == 0) return sum;

    // from constraints num <= 10000
    // we are checking sum min + prevMin so our max needs to be 20000
    // because it is the maximum value of this sum
    const int inf = 1e9; 
    int min1 = inf;
    int min2 = inf;
    int prevMin1 = inf; 
    int prevMin2 = inf;

    // find minimum values
    for (auto& num : nums) {
        if (num % 3 == 1) {
            // min X where X % 3 == 1 
            if (num < min1) {
                prevMin1 = min1;
                min1 = num;
            }
            // second min X where X % 3 == 1
            else if (num < prevMin1)
                prevMin1 = num;
        }
        else if (num % 3 == 2) {
            // min Y where Y % 3 == 2
            if (num < min2) {
                prevMin2 = min2;
                min2 = num;
            }
            // second min Y where Y % 3 == 2
            else if (num < prevMin2)
                prevMin2 = num;
        }
    }

    if (sum % 3 == 1)
        return sum - std::min(min1, min2 + prevMin2);

    return sum - std::min(min2, min1 + prevMin1);
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
        // some corner cases
        {{10, 10, 10, 11, 11}, 42},
        {{10000, 10000}, 0},
        {{8000, 8000}, 0},
        
        // --- LeetCode Examples ---
        {{366,809,6,792,822,181,210,588,344,618,341,410,121,864,191,749,637,169,123,472,358,908,235,914,322,946,738,754,908,272,267,326,587,267,803,281,586,707,94,627,724,469,568,57,103,984,787,552,14,545,866,494,263,157,479,823,835,100,495,773,729,921,348,871,91,386,183,979,716,806,639,290,612,322,289,910,484,300,195,546,499,213,8,623,490,473,603,721,793,418,551,331,598,670,960,483,154,317,834,352}, 50487},
        // Ex 1: Mix of remainders, result 18
        {{3,6,5,1,8}, 18},
        // Ex 2: Single number not divisible by 3
        {{4}, 0},
        // Ex 3: Multiple remainder 1s and 2s
        {{1,2,3,4,4}, 12},

        // --- Basic Logic ---
        // All divisible by 3
        {{3, 9, 30}, 42},
        // Only 1s and 2s that sum perfectly
        {{1, 2, 1, 2}, 6},

        // --- Logic Traps (Where the algorithm must make a choice) ---
        
        // 1. Sum % 3 == 1
        // Choice: Remove one remainder-1 (Val: 100) vs Remove two remainder-2s (Val: 2+2=4)
        // Correct: Remove 2+2. Result: 106 - 4 = 102.
        {{100, 2, 2, 2}, 102}, 
        
        // 2. Sum % 3 == 2
        // Choice: Remove one remainder-2 (Val: 50) vs Remove remainder-1 (Val: 1 + inf)
        // Correct: Remove 50. Result: 101 - 50 = 51.
        {{1, 50, 50}, 51},

        // 3. Sum % 3 == 2
        // Choice: Remove one remainder-2 (Val: 200) vs Remove two remainder-1s (Val: 1+1=2)
        // Correct: Remove 1+1. Result: 203 - 2 = 201.
        // Note: 200%3=2, 1%3=1. Sum=203 (rem 2).
        {{200, 1, 1, 1}, 201}, 

        // 4. Sum % 3 == 1
        // Choice: Remove one remainder-1 (Val: 100) vs Remove two remainder-1s (Val: 2 + inf)
        // Correct: Remove 100. Result: 202 - 100 = 102.
        {{100, 100, 2}, 102},

        // --- Corner Cases / Impossible Scenarios ---
        // Only one Remainder-1 (Sum%3=1, need to remove rem-1 or two rem-2s. We have rem-1).
        {{1}, 0},
        // Only one Remainder-2
        {{2}, 0},
        // Two Remainder-1s (Sum=2, rem 2. Need remove rem-2 (none) or two rem-1s (sum 2)).
        // Result 0 (2 - 2).
        {{1, 1}, 0},
        // Two Remainder-2s (Sum=4, rem 1. Need remove rem-1 (none) or two rem-2s (sum 4)).
        // Result 0 (4 - 4).
        {{2, 2}, 0},
        // Two Remainder-1s but large
        {{100, 100}, 0}, 
        // Two Remainder-2s but large
        {{200, 200}, 0},

        // --- Order Independence (Smallest numbers at end) ---
        // Sum % 3 == 1. Smallest rem-1 is at the very end.
        {{100, 13, 7, 4}, 120}, // Sum 124(rem 1). Remove 4. 

        // --- Large Vector Stress Test (Simulated) ---
        // Many 1s and 2s
        {{1, 1, 1, 2, 2, 2}, 9},
    };

    runTests(tests, [](const Test& test){
        auto nums = test.nums;
        int maxSum = maxSumDivThree(nums);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, maxSum) << std::endl;
        return maxSum == test.expectedResult;
    });
}