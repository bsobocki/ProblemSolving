# Problem
Given an binary array `nums` and an integer `k`, return `true` if all `1`'s are at least `k` places away from each other, otherwise return `false`.

#### Example 1:

Input: `nums = [1,0,0,0,1,0,0,1], k = 2` \
Output: `true` \
Explanation: `Each of the 1s are at least 2 places away from each other.`

#### Example 2:

Input: `nums = [1,0,0,1,0,1], k = 2` \
Output: `false` \
Explanation: `The second 1 and third 1 are only one apart from each other.`
 

#### Constraints:

`1 <= nums.length <= 105` \
`0 <= k <= nums.length` \
`nums[i] is 0 or 1`

# Intuition
We will go through the array and search `1`'s. Each time you find the next one - count `0`'s between them.

# Approach
- Find the first `1`.
- While you are successfully finding `1`:
    - Search for the next `1`. If you don't find one then finish.
    - If you found one then check how many `0`'s are between newly found `1` and the previous one. If less than `k` then return `false` immediately.
 
If every number of `0`'s are `k` or more, and we reached the end of the array, then just return `true`.

***NOTE:*** If you have `1` at position `it` and the next one at `next` then the number of `0`'s is `next - it - 1`, because you are counting number of elements between, not the distance between them.


# Complexity
- Time complexity: $O(n)$

- Space complexity: $O(1)$

# Code
```cpp []
class Solution {
public:
    bool kLengthApart(vector<int>& nums, int k) {
        auto it = std::find(nums.begin(), nums.end(), 1);
        while(it != nums.end()) {
            auto next = std::find(it+1, nums.end(), 1);
            // if it is on 0th position and next is on 1st then we have next - it = 1
            // but k tells about how many 0s we have between 1s, so we need to subtract 1
            // to not have the distance but number of elements between those 1s
            // 1 0 0 1 0 0 0 1
            // ^it   ^next   =>  next - it == 3, but there are 2 * 0s
            // we also don't want to count 0s at the end, so we need to check first if next is valid 
            if (next != nums.end() && (next - it - 1) < k) return false;
            it = next;
        }
        return true;
    }
};
```