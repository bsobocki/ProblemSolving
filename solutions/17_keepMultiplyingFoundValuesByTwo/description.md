# Problem

You are given an array of integers `nums`. You are also given an integer `original` which is the first number that needs to be searched for in `nums`.

You then do the following steps:

1. If `original` is found in `nums`, multiply it by two (i.e., set `original = 2 * original`).
2. Otherwise, **stop** the process.
3. **Repeat** this process with the new number as long as you keep finding the number.

Return the **final** value of *original*.

#### Example 1:

Input: `nums = [5,3,6,1,12], original = 3`\
Output: `24`\
Explanation: 
- `3 is found in nums. 3 is multiplied by 2 to obtain 6.`
- `6 is found in nums. 6 is multiplied by 2 to obtain 12.`
- `12 is found in nums. 12 is multiplied by 2 to obtain 24.`
- `24 is not found in nums. Thus, 24 is returned.`

#### Example 2:

Input: `nums = [2,7,9], original = 4`
Output: `4`
Explanation:
- `4 is not found in nums. Thus, 4 is returned.`
 

#### Constraints:

`1 <= nums.length <= 1000`\
`1 <= nums[i], original <= 1000`


# Intuition
In this task we can do exactly what problem description suggest.

# Intuition
In this task, we can do exactly what the problem description suggests. We will iterate through the array and look for `original`. If we find it, we multiply it by 2; otherwise, we return the current `original`.

# Approach
We have two main options:
1. Search through the whole array every time we look for `original`.
2. Build a `hash set` (unordered_set) first and use it for $O(1)$ lookups.

In a general scenario with large inputs, the `hash set` solution would be much faster. However, in this problem, we have the constraints `1 <= nums[i], original <= 1000`.

This means we will search for `original` a maximum of **10 times** (since $\lceil \log_2(1000) \rceil = 10$). The sequence would look like: `[1, 2, 4, 8, 16, 32, 64, 128, 256, 512]`.

Because the loop runs a constant number of times (max 10), the brute-force algorithm effectively performs $O(10 \cdot n)$ operations. Since 10 is a constant, this simplifies to linear time $O(n)$, making it efficient enough without the memory overhead of a hash set.

# Complexity
- **Time complexity:** $O(n)$ under the given constraints (it would be $O(n^2)$ without constraints).
- **Space complexity:** $O(1)$ for the first solution (no auxiliary data structures used).

# Code
```cpp []
#include <unordered_set>

class Solution {
public:
    // time complexity O(n^2) - but actually constraints makes it fast
    // because we will find the next original no more than log_2 1000, so max 9 times
    // so by taking it into account it is O(n)
    // space complexity O(1)
    int findFinalValue(vector<int>& nums, int original) {
        while(std::find(nums.begin(), nums.end(), original) != nums.end())
            original *= 2;
        return original;
    }

    // time complexity O(n) amortized - but much slower because constraints make the solution above linear
    // and here we have to build unordered set and makes lookup O(1) amortized, but it can be O(n)
    // space complexity O(n)
    int findFinalValueHashMap(vector<int>& nums, int original) {
        std::unordered_set<int> numsMap(nums.begin(), nums.end());
        while(numsMap.count(original))
            original *= 2;
        return original;
    }
};
```