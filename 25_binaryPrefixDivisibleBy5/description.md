# Problem

You are given a binary array nums (0-indexed).

We define xi as the number whose binary representation is the subarray nums[0..i] (from most-significant-bit to least-significant-bit).

For example, if nums = [1,0,1], then x0 = 1, x1 = 2, and x2 = 5.
Return an array of booleans answer where answer[i] is true if xi is divisible by 5.

#### Example 1:
```
Input: nums = [0,1,1]
Output: [true,false,false]
Explanation: The input numbers in binary are 0, 01, 011; which are 0, 1, and 3 in base-10.
Only the first number is divisible by 5, so answer[0] is true.
```


#### Example 2:
```
Input: nums = [1,1,1]
Output: [false,false,false]
```


#### Constraints:

- `1 <= nums.length <= 105`
- `nums[i] is either 0 or 1.`

---

# Intuition
The problem asks us to check divisibility for a binary number that grows with every element in the array. With a constraint of length up to $10^5$, the resulting binary number is far too large to store in standard integer types (a `long long` can only hold ~63 bits, while this number can have 100,000 bits).

The key intuition is that we don't need to store the entire number. According to the properties of modular arithmetic, $(a \times b + c) \pmod k$ is the same as $((a \pmod k) \times b + c) \pmod k$. This means we only need to keep track of the **remainder** at each step.

# Approach
1.  Initialize a variable `curr` to 0 to represent the current remainder.
2.  Create a boolean vector `result` to store our answers. Using `reserve()` is a good practice to avoid multiple memory reallocations as the vector grows.
3.  Iterate through the input array `nums`. For every bit `x`:
    *   Shift the current number to the left (multiply by 2) and add the new bit `x`.
    *   Immediately apply modulo 5 to keep `curr` small (it will always be between 0 and 4).
    *   Check if `curr` is 0. If it is, the number represented so far is divisible by 5.
4.  Push the boolean result into our list.

# Complexity
- Time complexity: $O(N)$\
  We iterate through the array `nums` exactly once. Inside the loop, we perform constant time arithmetic operations.

- Space complexity: $O(1)$\
  Ignoring the space required for the output vector `result`, we only use a single integer variable `curr` for our calculations.