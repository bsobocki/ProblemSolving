# Set Intersection Size At Least Two

## Problem
You are given a 2D integer array `intervals` where `intervals[i] = [start_i, end_i]` represents all the integers from `start_i` to `end_i` inclusively.

A `containing set` is an array `nums` where each `interval` from `intervals` has at least two integers in `nums`.

For example, if `intervals = [[1,3], [3,7], [8,9]]`, then `[1,2,4,7,8,9]` and `[2,3,4,8,9]` are `containing sets`.

Return the minimum possible size of a `containing set`.

### Examples

**Example 1:**
```text
Input: intervals = [[1,3],[3,7],[8,9]]
Output: 5
Explanation: let nums = [2, 3, 4, 8, 9].
It can be shown that there cannot be any containing array of size 4.
```

**Example 2:**
```text
Input: intervals = [[1,3],[1,4],[2,5],[3,5]]
Output: 3
Explanation: let nums = [2, 3, 4].
It can be shown that there cannot be any containing array of size 2.
```

**Constraints:**
*   `1 <= intervals.length <= 3000`
*   `intervals[i].length == 2`
*   `0 <= starti < endi <= 10^8`

---

## The Engineering Process: From Scratch to Optimal

This solution was developed in two distinct phases. 

### Phase 1: The Intuitive Approach (Discretization & Sets)
*Derived independently using pen-and-paper visualization.*

**The Concept:**
Initially, without prior knowledge of the specific greedy pattern, I analyzed the problem geometrically. I realized that the "best" points to pick are the ones where intervals overlap. These overlap points usually align with the **start** and **end** boundaries of the input intervals.

**The Algorithm:**
1.  **Discretization:** Collect all `start` and `end` coordinates into a `std::set` (`uniqueIntervalBoundaries`). This reduces the search space from $10^8$ integers to just $2N$ critical points.
2.  **Tracking:** Use a `std::set` (`mcs`) to store the final chosen numbers to handle deduplication automatically.
3.  **Selection:** Iterate through intervals sorted by end-time. If an interval isn't satisfied, pick the largest available numbers from the `uniqueIntervalBoundaries` set that fit in the interval.

**Pros:** Robust, handles duplicates effectively, derived from first principles.\
**Cons:** High constant overhead due to `std::set` operations and memory usage.

---

### Phase 2: The Optimized Approach (Greedy with Variables)
*Refined for optimal space and time complexity.*

**The Realization:**
While the Set approach works, we can observe that:
1.  Since we sort intervals by **End Time**, we are always moving Left-to-Right.
2.  To maximize the "usefulness" of a chosen number for *future* intervals, we should always pick numbers as far to the **Right** as possible (i.e., `end` and `end-1`).
3.  We don't need to store the entire history of chosen numbers. We only need to know the **two largest numbers** added so far to check for overlaps with the next interval.

**The Algorithm:**
1.  **Sorting:** Sort intervals by **End Time Ascending**.
    *   *Critical Logic:* If end times are equal, sort by **Start Time Descending**. This ensures we process the "tightest" (shortest) interval first. Satisfying the subset interval automatically satisfies the larger one.
2.  **State Tracking:** Maintain only two integers:
    *   `lastAdded`: The largest number currently in the set.
    *   `prevAdded`: The second largest number.
3.  **Greedy Logic:** For each interval `[start, end]`:
    *   **0 Overlap:** (`lastAdded < start`) $\rightarrow$ Add `end` and `end-1`.
    *   **1 Overlap:** (`prevAdded < start`) $\rightarrow$ Add `end`.
    *   **2 Overlap:** (`prevAdded >= start`) $\rightarrow$ Do nothing.

---

## Complexity Analysis

### Time Complexity: $O(N \log N)$
Both approaches fall into this class, but the constant factors differ.
*   **Sorting:** Takes $O(N \log N)$.
*   **Iteration:**
    *   *Phase 1 (Set):* Requires $O(\log N)$ set lookups per interval, resulting in a slower $O(N \log N)$.
    *   *Phase 2 (Optimal):* Requires constant time $O(1)$ operations per interval. The loop is $O(N)$.
    *   **Total:** Dominated by sorting, $O(N \log N)$.

### Space Complexity
*   **Phase 1 (Set):** $O(N)$ to store the `uniqueIntervalBoundaries` and the result set `mcs`.
*   **Phase 2 (Optimal):** $O(1)$ auxiliary space (ignoring sorting stack), as we only store two integers (`lastAdded`, `prevAdded`).
