# Problem

Given a signed 32-bit integer `x`, return `x` with its digits reversed. If reversing `x` causes the value to go outside the signed 32-bit integer range `[-231, 231 - 1]`, then return `0`.

***Assume the environment does not allow you to store 64-bit integers (signed or unsigned).***

 

### Example 1:

Input: `x = 123`\
Output: `321`


### Example 2:

Input: `x = -123`\
Output: `-321`


### Example 3:

Input: `x = 120`\
Output: `21`
 

### Constraints:

`-231 <= x <= 231 - 1`

# Intuition
The problem asks us to reverse the digits of an integer while handling overflow cases. The key insights are:
1. We can extract digits one by one using modulo and division operations
2. We need to handle negative numbers separately by tracking the sign
3. We must check for overflow before performing operations that could exceed 32-bit integer limits
4. INT_MIN is a special case since we cannot negate it without overflow

# Approach
1. **Handle Sign**: Extract the sign and work with positive numbers to simplify the logic
2. **Special Case INT_MIN**: Since `-INT_MIN` would overflow, we handle it separately by skipping the loop entirely (returns 0)
3. **Build Reversed Number**: Extract digits from right to left using `x % 10` and build the result by multiplying by 10 and adding each digit
4. **Overflow Prevention**: Before each multiplication by 10, check if `result > INT_MAX/10`. If true, the next operation would overflow, so return 0
5. **Return Result**: Apply the original sign to the reversed number

The overflow check works because:
- If `result > INT_MAX/10`, then `result * 10` will exceed INT_MAX
- We don't need to check the final digit addition because any input that would cause overflow at `result == INT_MAX/10` would itself be outside the valid input range

# Complexity
- Time complexity: $O(\log_{10}(x))$
  - We process each digit of the number exactly once
  - The number of digits in x is $\log_{10}(x)$

- Space complexity: $O(1)$
  - We only use a constant amount of extra space (sign, result variables)
  - No additional data structures are needed

# Code
```cpp []
class Solution {
public:
    int reverse(int x) {
        int sign = 1;
        // for x == INT_MIN we just skip loop and return 0 at the end
        if (x < 0 && x != INT_MIN){
            sign = -1;
            x *= -1; // for while loop
        }

        int result = 0;
        while (x > 0) {
            // check if next step is possible, if not (result*10 will be bigger than INT_MAX)
            // then we will have an overflow, so return 0 
            if (result && result > INT_MAX/10) return 0; // overflow
            result = result * 10 + x % 10;
            x /= 10;
        }

        return sign * result;
    }
};
```