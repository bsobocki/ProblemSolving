#include <iostream>
#include <utils/utils.hpp>
#include <numeric>
#include <climits>

using namespace std;

/*
 * Problem: time limit exceeded
 * ----------------------------
 * Time Complexity: O(n^2(n/k))
 * Space Complexity: O(1)
 * ----------------------------
 */
long long maxSubarraySumSlow(vector<int>& nums, int k) {
    if (k > nums.size()) return 0;

    long long maxSum = std::accumulate(nums.begin(), nums.begin() + k, 0LL);
    for(int subSize = k; subSize <= nums.size(); subSize += k) {
        for (int i = 0; i <= nums.size()-subSize; i++) {
            auto begin = nums.begin() + i;
            auto end = begin + subSize;
            const long long sum = std::accumulate(begin, end, 0LL);
            if (maxSum < sum)
                maxSum = sum;
        }
    }

    return maxSum;
}

/*
 * Problem: time limit exceeded
 * ----------------------------
 * Time Complexity: O(n(n/k))
 * Space Complexity: O(1)
 * ----------------------------
 */
long long maxSubarraySumSlightlyBetterThanSlow(vector<int>& nums, int k) {
    if (k > nums.size()) return 0;

    long long maxSum = std::accumulate(nums.begin(), nums.begin() + k, 0LL);

    for(int subSize = k; subSize <= nums.size(); subSize += k) {
        long long prevSum = std::accumulate(nums.begin(), nums.begin() + subSize, 0LL);
        maxSum = std::max(prevSum, maxSum);
        for (int i = 1; i <= nums.size()-subSize; i++) {
            const int numBeforeRange = nums[i - 1];
            const int lastNumFromCurrRange = nums[i + subSize - 1];
            const long long sum = prevSum - numBeforeRange + lastNumFromCurrRange;
            maxSum = std::max(sum, maxSum);
            prevSum = sum;
        }
    }

    return maxSum;
}

/*
 * Problem: time limit exceeded
 * Problem: Memory Limit Exceeded
 * ----------------------------
 * Time Complexity: O(n(n/k))
 * Space Complexity: O(n(n/k))
 * ----------------------------
 * we will solve it with DP      ->  dp array for state memorizing
 * state: i - start, subSize     ->  size of range from where we get the sum
 * step: i - start, subSize + k  ->  the sum = dp[i][subSize] + dp[i+subsize][k]
 * each time we will extend range by k elements (so previous subSize + k)
 * lets name our prevoius subSize 'prevSubSize' then we know that prevSubSize = subSize-k
 * in that case our sum will be equal (sum from the prevoius range + sum of those next k elements)
 * but sum of those next k element has been calculated before and saved in sums[i+prevSubSize][k] - sum of k elements starts after previous range
 */
long long maxSubarraySumDP(vector<int>& nums, int k) {
    if (k > nums.size()) return 0;

    const int numOfSubSizes = nums.size()/k;

    // we will save sums for subarrays [i ... i+subSize-1]
    vector<vector<long long>> sums(nums.size(), vector<long long>(numOfSubSizes, 0));

    // we need to calculate the sum of the first subarray with length k
    sums[0][0] = std::accumulate(nums.begin(), nums.begin()+k, 0LL);

    long long maxSum = sums[0][0];

    // at first we will fill sums for subSize = k because there are the most such sums
    // that means we have first state for each i - indexed from 0
    // each sum is just sum from index before without its first element and with last element from current range
    for (int i = 1; i <= nums.size()-k; i++) {
        sums[i][0] = sums[i-1][0] - nums[i-1] + nums[i+k-1];
        maxSum = std::max(maxSum, sums[i][0]);
    }

    // check the rest sums of subarrays [i...i+subSize+1] for other subSizes [2*k, 3*k, ..., maxSubSize]
    // note: we don't need an actual subSize - we just need an index represents current subsize: 0 => k, 1 => 2k, 2 => 3k, ...
    for(int subSizeIdx = 1; subSizeIdx < numOfSubSizes; subSizeIdx++) {
        const int prevSubSizeIdx = subSizeIdx-1;
        const int subSize = (subSizeIdx+1)*k;
        const int prevSubSize = subSize - k;
        for (int i = 0; i <= nums.size()-subSize; i++) {
            // current sum is sum for prevoius range starting from i and next k elements after previous range
            // so from range started from i + prevSubSize
            sums[i][subSizeIdx] = sums[i][prevSubSizeIdx] + sums[i+prevSubSize][0];
            maxSum = std::max(maxSum, sums[i][subSizeIdx]);
        }
    }

    return maxSum;
}

/*
 * Problem: time limit exceeded
 * ----------------------------
 * Time Complexity: O(n(n/k))
 * Space Complexity: O(n) -- only three sum arrays of O(n) length: for k-subarrays, prev and current
 * ----------------------------
 *  we will solve it with DP      ->  dp array for state memorizing
 * state: i - start, subSize     ->  size of range from where we get the sum
 * step: i - start, subSize + k  ->  the sum = dp[i][subSize] + dp[i+subsize][k]
 * each time we will extend range by k elements (so previous subSize + k)
 * lets name our prevoius subSize 'prevSubSize' then we know that prevSubSize = subSize-k
 * in that case our sum will be equal (sum from the prevoius range + sum of those next k elements)
 * but sum of those next k element has been calculated before and saved so we can use it
 */
long long maxSubarraySumDPLimitedSpace(const vector<int>& nums, int k) {
    if (k > nums.size()) return 0;

    const int numOfSubSizes = nums.size()/k;

    // we will save maximum sums for subarrays [i ... i+subSize-1]
    // we need only previous and current sums to calculate that
    vector<long long> sumsK(nums.size(), 0);

    // we need to calculate the sum of the first subarray with length k
    sumsK[0] = std::accumulate(nums.begin(), nums.begin()+k, 0LL);

    long long maxSum = sumsK[0];

    // at first we will fill sums for subSize = k because there are the most such sums
    // that means we have first state for each i - indexed from 0
    // each sum is just sum from index before without its first element and with last element from current range
    for (int i = 1; i <= nums.size()-k; i++) {
        sumsK[i] = sumsK[i-1] - nums[i-1] + nums[i+k-1];
        maxSum = std::max(maxSum, sumsK[i]);
    }

    vector<long long> sums = sumsK;
    // check the rest sums of subarrays [i...i+subSize+1] for other subSizes [2*k, 3*k, ..., maxSubSize]
    for(int subSize = 2 * k; subSize <= nums.size(); subSize += k) {
        vector<long long> prevSums = sums;
        const int prevSubSize = subSize - k;
        for (int i = 0; i <= nums.size()-subSize; i++) {
            // current sum is sum for prevoius range starting from i and next k elements after previous range
            // so from range started from i + prevSubSize
            sums[i] = prevSums[i] + sumsK[i+prevSubSize];
            maxSum = std::max(maxSum, sums[i]);
        }
    }

    return maxSum;
}

/*
 * Time Complexity: O(n) - we are going through each num from array only once and get min prefix in O(1) times
 * Space Complexity: O(k) -- only min prefixes for k reminders and O(1) memory
 * ----------------------------
 * Idea: use prefix sums and 2 tricks
 * 1. if we have prefix sum from 0 to j as PrefixSum[j] 
 *    then we know that the sum from i to j is equal PrefixSum[j] - PrefixSum[i-1];
 *    because we take summ of all elements from 0 to j and remove elements from 0 to i-1
 * 2. if lenghts (j - (i - 1)) is divisible by k then j and i-1 has the same remonder when divided by k
 *    Proof:
 *       j = n*k + reminderJ and i = m*k + reminderI (for the corresponding n and m)
 *       length = (j - (i - 1)) = n*k + reminderJ - (m*k + reminderI) = n*k + reminderJ - m*k - reminderI = k(n-m) + reminderJ - reminderI
 *       then length % k = ( k(n-m) + reminderJ - reminderI ) % k = k(n-m) % k + (reminderJ - reminderI) % k = 0 + (reminderJ - reminderI) % k
 *       then if length % k == 0 then (reminderJ - reminderI) % k = 0, so
 *          reminderJ - reminderI = 0 or
 *          reminderJ - reminderI = k*a (for some a) => this is false because reminderJ would have to be bigger than k
 *       in that case we know that both reminders are equal
 *
 * from that we know that if you would like to take sum with length divisible by k ending at j, then you know that you should consider only i with the same reminders
 * so if we know that our sum that ends on j has to be maximized and sum = PrefixSum[j] - PrefixSum[i] (for some i) then PrefixSum[i] has to be as minimum as possible,
 * so we need to take i with the same reminder as j and i < j and with the minimum value PrefixSum[i]
 * the best way to know which value is minimal for current i is to store those minimal values
 * in that case the best approach would be just store the minimal PrefixSum based on reminder
 * then we can check PrefixSum for j, take reminder for j and take minimal PrefixSum we seen for this reminder
 * if we go from left to the right we have guaranteed that all seen PrefixSum will be on the left from current j
 * so we don't need to worry about taking PrefixSum of some i >= j if their reminders are the same
 *
 * we will then go through the array creating such PrefixSums and checking maximum PrefixSum[j] - PrefixSum[i] for them
 */
long long maxSubarraySum(const vector<int>& nums, int k) {
    long long maxSum = LLONG_MIN;

    // we will go through the array creating prefix sums but we don't need to store all of them, just minimal one for each reminder and current prefix
    // prefix sum of reminder = sum from 0 to each seen i where i % k == reminder
    vector<long long> minPrefixSumForReminder(k, LLONG_MAX);
    long long currPrefix = 0;

    // indexing from 0, so to take a position, not index, we need to add 1
    for (int j = 0; j < nums.size(); j++) {
        // we are building current prefix just by simply adding subsequent elements in a loop
        currPrefix += nums[j];

        const int currReminder = (j+1) % k;

        // if we have minimal prefix sum for current reminder then we take it to count our sum
        if (minPrefixSumForReminder[currReminder] != LLONG_MAX) {
            const long long currMaxSum = currPrefix - minPrefixSumForReminder[currReminder];
            maxSum = std::max(maxSum, currMaxSum);
        }
        // if we have currReminder at 0 then it means that we reached kth element
        // so we need to handle it properly - just take currentPrefix as maximal sum for reminder 0
        // if previous prefix for reminder 0 was bigger then it will remains the same
        // but if current prefix is bigger then we know that its length is divisible by k so we can take it
        if (currReminder == 0) {
            maxSum = std::max(maxSum, currPrefix);
        }
        
        // update min prefix sum for current reminder if needed
        minPrefixSumForReminder[currReminder] = std::min(minPrefixSumForReminder[currReminder], currPrefix);
    }

    return maxSum;
}

/*
 * Exactly the same as maxSubarraySum but with different approach of handling cases for (n*k)th elements
 */
long long maxSubarraySumButInitializeMinPrefixArrayAt0(vector<int>& nums, int k) {
    long long maxSum = LLONG_MIN;

    vector<long long> minPrefixSumForReminder(k, LLONG_MAX);
    long long currPrefix = 0;

    // if we will get to the kth element we want to have sum = currPrefix, so we need to subtract 0
    // we can think of it the same as "min prefix sum for elements seen before j = 0 is 0, because there is no elements before j = 0"
    minPrefixSumForReminder[0] = 0;

    for (int j = 0; j < nums.size(); j++) {
        currPrefix += nums[j];

        const int currReminder = (j+1) % k;

        if (minPrefixSumForReminder[currReminder] != LLONG_MAX) {
            const long long currMaxSum = currPrefix - minPrefixSumForReminder[currReminder];
            maxSum = std::max(maxSum, currMaxSum);
        }
        // we don't need additional if statement that checks if currReminder is 0
        // because for currReminder == 0 we wil find min prefix sum for reminder 0 => 0
        // so we will just subtract 0 from currPrefix => currMaxSum == currPrefix as we want
        // and if current prefix for reminder 0 will be bigger than 0 then minPrefixSumForReminder[0] remains 0
        // but if it will be negative, then minPrefixSumForReminder will be overwritten and subtracted next time
        // note: effect is the same as using 'if' statement, because when prefix sum is negative for remainder 0 we will overwrite minPrefixSumForReminder
        // and next time we will find it, check maxSum, then we will go into 'if (currRemainder == 0)' statement and compare maxSum with currPrefix
        // so result remains the same because we will compare maxSum with currPrefix - found minPrefixSumForReminder[0] and with currPrefix only
        
        // update min prefix sum for current reminder if needed
        minPrefixSumForReminder[currReminder] = std::min(minPrefixSumForReminder[currReminder], currPrefix);
    }

    return maxSum;
}

struct Test {
    vector<int> nums;
    int k;
    long long expectedResult;

    std::string getInfo() const {
        stringstream ss;
        ss << "k: " << k << " | nums: " << nums;
        return ss.str();
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        // --- Leetcode example when I failed before ---
        {{13,-30,-29, 48}, 1, 48},

        // --- Basic Cases (From Problem Description) ---
        { {1, 2}, 1, 3},
        { {-1, -2, -3, -4, -5}, 4, -10},
        { {-5, 1, 2, -3, 4}, 2, 4},

        // --- Edge Cases ---
        { {5}, 1, 5},
        { {1, 2, 3}, 3, 6},

        // --- The 'Else' logic verifiers ---
        // Case where subarray starts at index 0 (currReminder == 0) logic is crucial
        { {10, 20}, 2, 30},
        
        // Case where starting at 0 is BETTER than cutting 
        // Prefixes: [10, 30, 60, 100]. K=2.
        // At 40 (Idx 3, Sum 100): 
        // Option A (Cut at K): 100 - 30 = 70.
        // Option B (Start 0): 100 - 0 = 100. -> Winner.
        { {10, 20, 30, 40}, 2, 100},

        // Case where cutting is BETTER than starting at 0 (Negative prefix)
        // Prefixes: [-10, -20]. K=1.
        // At -20: 
        // Option A (Cut): -20 - (-10) = -10. -> Winner
        // Option B (Start 0): -20.
        { {-10, -10}, 1, -10},

        // --- Tricky Mixed Cases ---
        // Array: [5, -10, 5, 20], K=2
        // Prefixes: [5, -5, 0, 20]
        // i=1 (-5): Rem 0. Max so far: -5 (Start 0). MinPref[0]=-5.
        // i=3 (20): Rem 0. 
        //    Cut at MinPref[0](-5) -> 20 - (-5) = 25. (Subarray [5, 20] -> sums to 25? Wait, subarray is indices 2,3 -> [5, 20])
        //    Start at 0 -> 20.
        //    Result 25.
        { {5, -10, 5, 20}, 2, 25},
        
        // Large negative start
        // [-1000, 5, 5], k=2
        // Subarray [5, 5] = 10.
        { {-1000, 5, 5}, 2, 10},
        
        // All negative but increasing
        // [-10, -5, -2], k=1 -> max is -2
        { {-10, -5, -2}, 1, -2}
    };

    runTests(tests, [](const Test& test){
        long long result = maxSubarraySum(test.nums, test.k);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, result) << std::endl;
        return result == test.expectedResult;
    });
}