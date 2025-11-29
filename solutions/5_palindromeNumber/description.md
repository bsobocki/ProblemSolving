# Problem

Given an integer `x`, return true if `x` is a palindrome, and false otherwise.

#### Example 1:

Input: `x = 121`\
Output: `true`\
Explanation: `121 reads as 121 from left to right and from right to left.`

#### Example 2:

Input: `x = -121`\
Output: `false`\
Explanation: `From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.`

#### Example 3:

Input: `x = 10`\
Output: `false`\
Explanation: `Reads 01 from right to left. Therefore it is not a palindrome.`
 

#### Constraints:

`-231 <= x <= 231 - 1`
 

Follow up: ***Could you solve it without converting the integer to a string?***

---

# Solution
We can calculate a new number using digits from `x` and compare.

We can do it using `std::vector<int8_t>`, or just an `int` with arithmetic operations `mod 10`, `/ 10^k` and `* 10^k`.

Time complexity: $O(log_{10} n)$
Space complexity: $O(1)$ for `int` version, and $O(log_{10} n)$ for `std::vector<int8_t>` version.