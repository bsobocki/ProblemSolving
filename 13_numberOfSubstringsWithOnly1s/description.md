# Problem
Given a binary string `s`, return the number of substrings with all characters `1`'s. Since the answer may be too large, return it modulo $10^9 + 7$.


#### Example 1:

**Input:** `s = "0110111"`\
**Output:** `9`\
**Explanation:** `There are 9 substring in total with only 1's characters.`\
`"1" -> 5 times.`\
`"11" -> 3 times.`\
`"111" -> 1 time.`


#### Example 2:

Input: `s = "101"`\
Output: `2`\
Explanation: `Substring "1" is shown 2 times in s.`\
Example 3:

Input: `s = "111111"`\
Output: `21`\
Explanation: `Each substring contains only 1's characters.`
 

#### Constraints:

`1 <= s.length <= 105`\
`s[i] is either '0' or '1'.`

# Intuition
The key insight is that for a consecutive segment of `n` ones, the number of substrings is `1 + 2 + 3 + ... + n = (n+1)n/2`. This is because:
- There are `n` substrings of length 1
- There are `n-1` substrings of length 2
- There are `n-2` substrings of length 3
- And so on...

So we can find all consecutive segments of 1's, calculate the contribution of each segment using the formula, and sum them up.

# Approach
1. Use two iterators to find consecutive segments of 1's in the string
2. For each segment of length `n`, calculate the number of substrings as `(n+1)n/2`
3. Apply modular arithmetic properties to handle large numbers:
   - Distributive property: `(x+y) % n = ((x % n) + (y % n)) % n`
   - Works for multiplication too: `(x*y) % n = ((x % n) * (y % n)) % n`
4. Key optimization: Since `(n+1)n` is always even (one of two consecutive integers must be even), we can safely divide by 2 before taking modulo, avoiding modular division complications
5. Accumulate all contributions with proper modulo operations

# Complexity
- Time complexity: $O(n)$\
We traverse the string once using std::find, which internally scans through characters linearly

- Space complexity: $O(1)$\
We only use a constant amount of extra space for iterators and counters.


# Code
```cpp []
class Solution {
public:
    int numSub(string s) {
        constexpr int mod = 1000000007;
        auto l = s.begin();
        auto r = s.begin();
        int sum = 0;

        // Modular arithmetic property: (x+y) % n = ((x % n) + (y % n) ) % n
        // x + x-1 + x-2 + ... + 3 + 2 + 1 = (x+1)*x/2
        // so combined both: ((x+1)*x/2) % n = (((((x+1) % n) * x ) % n) / 2) % n
        // but you can skip %n on division because division only decreases number
        // so no need to do %n on that because the result is still less than 'n'
        // x % n is less than n but here it is also divided by 2 - still less
        while (r != s.end()) {
            l = std::find(r, s.end(), '1');
            r = std::find(l, s.end(), '0');
            size_t size1s = r - l;
            sum = (sum + ((((size1s + 1) % mod) * size1s) % mod) / 2) % mod;
        }

        return sum;
    }
};
```