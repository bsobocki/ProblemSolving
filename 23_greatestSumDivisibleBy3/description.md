# Problem

Given an integer array `nums`, return the `maximum possible sum` of elements of the array such that it is divisible by three.

#### Example 1:
```
Input: `nums = [3,6,5,1,8]`\
Output: `18`\
Explanation: `Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).`
```


#### Example 2:
```
Input: `nums = [4]`\
Output: `0`\
Explanation: `Since 4 is not divisible by 3, do not pick any number.`
```

#### Example 3:
```
Input: `nums = [1,2,3,4,4]`\
Output: `12`\
Explanation: `Pick numbers 1, 3, 4 and 4 their sum is 12 (maximum sum divisible by 3).`
```

#### Constraints:

- `1 <= nums.length <= 4 * 104`
- `1 <= nums[i] <= 104`

---

# Idea

The core insight is to start by assuming we take **all numbers** to get the maximum possible sum. If the total sum is already divisible by 3, we are done.

If the total sum is not divisible by 3, it will have a remainder of either `1` or `2`. To make the sum divisible by 3 while keeping it maximal, we must subtract the **smallest possible combination of numbers** that has the same remainder as the total sum.

We rely on modular arithmetic properties:
1.  **To remove a remainder of 1:** We can remove **one** number with remainder 1, OR **two** numbers with remainder 2 (since $2+2 \equiv 4 \equiv 1 \pmod 3$).
2.  **To remove a remainder of 2:** We can remove **one** number with remainder 2, OR **two** numbers with remainder 1 (since $1+1 \equiv 2 \pmod 3$).

Since we need to subtract the smallest possible values, we only need to track the **smallest** and **second smallest** numbers for remainders 1 and 2.

# Solution

1.  **Iterate through the array once (`O(N)`):**
    -   Calculate the `totalSum` of all elements.
    -   Simultaneously, track the **two smallest numbers** that have `num % 3 == 1` (`min1`, `prevMin1`).
    -   Track the **two smallest numbers** that have `num % 3 == 2` (`min2`, `prevMin2`).
    -   Initialize these trackers to a large value (infinity) to handle cases where such numbers don't exist.

2.  **Check `totalSum % 3`:**
    -   **Case 0:** Return `totalSum`.
    -   **Case 1:** Subtract the minimum of:
        -   The smallest number with remainder 1 (`min1`).
        -   The sum of the two smallest numbers with remainder 2 (`min2 + prevMin2`).
    -   **Case 2:** Subtract the minimum of:
        -   The smallest number with remainder 2 (`min2`).
        -   The sum of the two smallest numbers with remainder 1 (`min1 + prevMin1`).

3.  **Return** the adjusted sum.

# Complexity

-   **Time Complexity:** `O(N)`
    -   We iterate through the `nums` array once for sum and once for `min`s. All other operations (comparisons, additions) are constant time `O(1)`.
-   **Space Complexity:** `O(1)`
    -   We only use a fixed number of integer variables (`sum`, `min1`, `min2`, etc.) regardless of the input size. No extra arrays or data structures are used.