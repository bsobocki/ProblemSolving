# Problem

You are given an array of integers `nums` and an integer `k`.

Return the maximum sum of a subarray of `nums`, such that the size of the subarray is divisible by `k`.

#### Example 1:
```
Input: nums = [1,2], k = 1
Output: 3
Explanation:
The subarray [1, 2] with sum 3 has length equal to 2 which is divisible by 1.
```

#### Example 2:
```
Input: nums = [-1,-2,-3,-4,-5], k = 4
Output: -10
Explanation:
The maximum sum subarray is [-1, -2, -3, -4] which has length equal to 4 which is divisible by 4.
```

#### Example 3:
```
Input: nums = [-5,1,2,-3,4], k = 2
Output: 4
Explanation:
The maximum sum subarray is [1, 2, -3, 4] which has length equal to 4 which is divisible by 2.
```

#### Constraints:

- `1 <= k <= nums.length <= 2 * 105`
- `-109 <= nums[i] <= 109`

---

# Development Process & Solution Evolution

My approach to solving this problem evolved through 5 distinct stages. I started with a simulation of the problem statement and progressively optimized the time and space complexity.

### 1. Brute Force
**Idea:** The problem asks for subarrays of length `k`, `2k`, `3k`, etc. My first thought was to literally iterate through every valid length. For each length, iterate through the array and sum the elements.

*   **Logic:** Three nested loops: `Length -> Start Index -> Summation Loop`.
*   **Time Complexity:** $O(N^3)$.
*   **Result:** **Time Limit Exceeded (TLE)**.

### 2. Sliding Window Optimization
**Idea:** I realized the summation loop was unnecessary. When moving a window of size `L` one step to the right, we don't need to re-sum everything. We can just subtract the leaving element and add the entering element.

*   **Logic:** `Length -> Start Index (Sliding Window)`.
*   **Time Complexity:** $O(N \cdot \frac{N}{k}) \approx O(N^2)$.
*   **Result:** **Time Limit Exceeded (TLE)**. Even though it's faster, iterating through every possible length is still quadratic in the worst case (e.g., $k=1$).

### 3. Dynamic Programming (Full Table)
**Idea:** I tried to construct larger subarrays from smaller ones. A subarray of length `size` is just a subarray of length `size - k` plus the next `k` elements.
*   **State:** `dp[i][subSize]` stores the sum of the subarray starting at `i` with length `subSize`.
*   **Transition:** `sums[i][sizeIdx] = sums[i][prevSizeIdx] + sums[i + prevSize][0]`.
*   **Space Complexity:** $O(N \cdot \frac{N}{k})$.
*   **Result:** **Memory Limit Exceeded (MLE)**. For small `k`, the table size becomes $N^2$, which is too large for RAM.

### 4. Dynamic Programming (Limited Space)
**Idea:** To fix the memory issue, I noticed we only need the sums from the *previous* length (`size - k`) to calculate the *current* length (`size`). We don't need the whole table, just two vectors (`prevSums` and `currSums`).

*   **Space Complexity:** $O(N)$. (Optimized).
*   **Time Complexity:** $O(N \cdot \frac{N}{k})$.
*   **Result:** **Time Limit Exceeded (TLE)**. While the memory issue was fixed, the algorithmic complexity remained quadratic because I was still iterating through specific lengths.

---

### 5. Optimal Solution: Prefix Sums & Modulo
To reach $O(N)$, I needed to stop iterating over lengths entirely. The breakthrough came from learning that I can use Prefix Sums combined with Modular Arithmetic to identify valid subarrays instantly.

`PrefixSum[j]` represents $\sum_{i=0}^{j} \text{nums}[i]$.

**Mathematical Insight:**
1.  Sum of subarray `nums[i...j]` = `PrefixSum[j] - PrefixSum[i-1]`.
2.  Length = `j - (i-1)`.
3.  If `Length` is divisible by `k`, then `j` and `(i-1)` must have the **same remainder** when divided by `k`.

**Mathematical Proof:**
Why do the remainders have to be the same?

1.  Let `PrefixSum[j]` be the sum from `0` to `j`.
    Then sum from `i` to `j` is `PrefixSum[j] - PrefixSum[i-1]`.
2.  `(j - (i - 1)) % k == 0` $\Longrightarrow$ `j % k == (i-1) % k`
    *   Proof:
        *   `j = n*k + remainderJ` for corresponding `n`
        *   `i-1 = m*k + remainderI` for corresponding `m`
        *   `length = (j - (i - 1)) = n*k + remainderJ - (m*k + remainderI)`
        *   `length = k(n-m) + remainderJ - remainderI`
        *   If `length % k == 0`, then `(k(n-m) + remainderJ - remainderI) % k == 0`.
        *   Since `k(n-m)` is divisible by `k`, we are left with `(remainderJ - remainderI) % k == 0`.
        *   This implies `remainderJ - remainderI` must be `0` (because the difference between two remainders `< k` cannot be `k` or larger).
        *   Therefore: `remainderJ == remainderI`.

**The Algorithm:**
We iterate through the array once. We maintain a `minPrefixSumForReminder` array where `minPrefixSumForReminder[r]` stores the minimum prefix sum seen so far at an index with remainder `r`.

#### Handling the "Start of Array" Case
There was a logical challenge: what if we check prefix sum for the `kth` element, when the current remainder is `0`?

I initially handled this with a separate `if (currReminder == 0)` check. After checking the current sum and updating `maxSum`, I checked if `currReminder` was `0`. If `true`, I just took `currPrefix` as the current sum (because the length of the subarray from 0 to k-1 is divisible by k) and compared it with `maxSum`.

This works because:
- If the prefix sum for the previous 0-remainder was non-negative, then `currPrefix >= currPrefix - minPrefixSumForReminder[currReminder]`.
- If it was negative, then the actual maximum from both considered sums will be `currPrefix - minPrefixSumForReminder[currReminder]`.

However, I realized I can handle this elegantly by changing my approach to consider the first remainder `0` as the start, and initializing the vector appropriately.

**Logic:** If we get to the `kth` element, we want `sum = currPrefix`. This implies we need to subtract `currPrefix - 0`.

**Implementation:** `minPrefixSumForReminder[0] = 0`.

**Why it works:** This acts exactly like the explicit `if` check for the 0-remainder case:
*   If `currPrefix` is non-negative, `max` will choose `currPrefix - 0`. Also, `minPrefixSumForReminder[0]` won't be overwritten, because we take `std::min(0, positive_val)`. Next time we will still subtract 0.
*   If `currPrefix` is negative, we overwrite `minPrefixSumForReminder[0]` with that negative value (since `negative < 0`). The next time we encounter a 0-remainder, we will subtract that negative value, which maximizes the result.