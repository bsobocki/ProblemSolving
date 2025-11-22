# Problem
You are given an integer array `nums`. In one operation, you can `add 1` or `subtract 1` from any element of `nums`.

Return the minimum number of operations to make all elements of nums `divisible by 3`.

#### Example 1:
```
Input: nums = [1,2,3,4]
Output: 3
Explanation:
All array elements can be made divisible by 3 using 3 operations:
- Subtract 1 from 1.
- Add 1 to 2.
- Subtract 1 from 4.
```

#### Example 2:
```
Input: nums = [3,6,9]
Output: 0
```

#### Constraints:
```
1 <= nums.length <= 50
1 <= nums[i] <= 50
```

# Intuition
A number `nums[i]` is divisible by 3 when `nums[i] % 3 == 0`.\
If we can `add 1` or `subtract 1`, then we can make every number divisible by 3 (`nums[i] % 3 == 0`) just in max one step:
- if `nums[i] % 3 == 0` - ***do nothing***
- if `nums[i] % 3 == 1` - **just subtract 1**
- if `nums[i] % 3 == 2` - **just add 1**

In that case we have to do something only when `nums[i] % 3 != 0` and we always do 1 operation, so all we have to do is to count how many `nums[i]` we need to change (`nums[i] % 3 != 0`);

# Approach
We use `std::count_if` for that.

# Complexity
- Time complexity: $O(n)$

- Space complexity: $O(1)$

# Code
```cpp []
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        return std::count_if(nums.begin(), nums.end(), [](const int& num) {
            return num % 3 != 0;
        });
    }
};
```