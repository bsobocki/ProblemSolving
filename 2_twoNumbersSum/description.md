# Two Sum

Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.

You may assume that each input would have **exactly one solution**, and you may not use the *same* element twice.

You can return the answer in any order.

#### Example 1:

**Input:** `nums = [2,7,11,15], target = 9` \
**Output:** `[0,1]` \
**Explanation:** `Because nums[0] + nums[1] == 9, we return [0, 1].`


#### Example 2:

**Input:** `nums = [3,2,4], target = 6` \
**Output:** `[1,2]`


#### Example 3:

**Input:** `nums = [3,3], target = 6` \
**Output:** `[0,1]`
 

#### Constraints:

- `2 <= nums.length <= 104`
- `-109 <= nums[i] <= 109`
- `-109 <= target <= 109`
- `Only one valid answer exists.`

---

# Solution Evolution

This problem is a classic example of the **Time-Space Trade-off**. We can solve it with no extra memory (slow), or use extra memory to make it instant.

## 1. Brute Force Approach
**Time Complexity**: $O(N^2)$ \
**Space Complexity**: $O(1)$

**The Intuition:**
The simplest way is to check every possible pair of numbers.
1. Pick the first number.
2. Loop through the rest of the array to see if any other number adds up to the target.
3. Repeat for the second number, third number, etc.

**Why avoid it:**
Nested loops result in quadratic time complexity. For large inputs (e.g., 10,000 items), this performs roughly 100,000,000 operations, which is very slow.

## 2. Sorting (Two Pointers Technique)
**Time Complexity**: $O(N \log N)$ (Dominated by Sorting) \
**Space Complexity**: $O(N)$ (To store original indices)

**The Logic:**
If the numbers were sorted, we wouldn't need to check every pair. We could use the "Two Pointers" strategy:
1. Place a pointer at the start (`left` = smallest number) and end (`right` = largest number).
2. Calculate sum: `nums[left] + nums[right]`.
   *   **Too big?** We need a smaller sum, so move `right` pointer to the left.
   *   **Too small?** We need a larger sum, so move `left` pointer to the right.
   *   **Match?** We found it.

**The Implementation Detail:**
Since sorting the array destroys the original indices (which the problem requires us to return), we cannot sort `nums` directly.
*   **Vector Approach:** We create a `vector<pair<int, int>>` to store `{value, original_index}` and sort that. This is fast and cache-friendly.
*   **Multimap Approach:** We insert items into a `std::multimap`. While this sorts automatically, it is significantly slower in practice due to tree-node memory allocation overhead.

## 3. Hash Map (One-Pass) - The Optimal Solution
**Time Complexity**: $O(N)$ \
**Space Complexity**: $O(N)$

**The Mathematical Insight:**
Instead of searching for a pair, we can use simple algebra.
$$a + b = target \implies b = target - a$$

**The Algorithm:**
We iterate through the array just once. For every number `x` we see:
1. Calculate the number we *need* to find: `needed = target - x`.
2. Ask the Hash Map: "Have I seen `needed` before?"
   *   **Yes:** We found the pair! Return current index and the index stored in the map.
   *   **No:** Store the current number `x` and its index in the map for future lookups.

**Why this is best:**
Lookup in a Hash Map (`std::unordered_map`) is $O(1)$ on average. This allows us to solve the problem in a single pass through the data.

---

## Complexity Summary

| Algorithm | Time Complexity | Space Complexity | Notes |
| :--- | :--- | :--- | :--- |
| **Brute Force** | $O(N^2)$ | $O(1)$ | Too slow for large inputs. |
| **Sorting (Vector)** | $O(N \log N)$ | $O(N)$ | Good middle ground. |
| **Sorting (Multimap)**| $O(N \log N)$ | $O(N)$ | Slower constants due to tree allocation. |
| **Hash Map** | $O(N)$ | $O(N)$ | **Fastest / Optimal Solution.** |