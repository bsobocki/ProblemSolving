# Problem

Given a positive integer `k`, you need to find the length of the smallest positive integer `n` such that `n` is divisible by `k`, and `n` only contains the digit `1`.

Return the length of `n`. If there is no such `n`, return `-1`.

Note: `n` may not fit in a 64-bit signed integer.

#### Example 1:
```
Input: k = 1
Output: 1
Explanation: The smallest answer is n = 1, which has length 1.
```

#### Example 2:
```
Input: k = 2
Output: -1
Explanation: There is no such positive integer n divisible by 2.
```

#### Example 3:
```
Input: k = 3
Output: 3
Explanation: The smallest answer is n = 111, which has length 3.
```

#### Constraints:

- `1 <= k <= 105`

---

# Intuition
The problem asks for the smallest number consisting only of the digit '1' (a repunit) that is divisible by `k`.
Since repunits grow extremely fast (1, 11, 111, ...), even a 64-bit integer will overflow quickly. We cannot store the number itself. Instead, we can use the property of modular arithmetic:
`(a * 10 + b) % k == ((a % k) * 10 + b) % k`.

This allows us to compute the remainder of the *next* repunit based solely on the remainder of the *current* repunit.

Additionally, we can observe that any number ending in the digit '1' is odd and not divisible by 5. Therefore, if `k` is divisible by 2 or 5, it is impossible to find such a number.

# Approach
1.  **Pruning**: First, check if `k` is divisible by 2 or 5. If so, return `-1` immediately, as a number ending in '1' cannot be divisible by even numbers or multiples of 5.
2.  **Simulation**: We simulate the process of building the number digit by digit. We start with a remainder of 0. In every iteration, we update the remainder using the formula: `remainder = (remainder * 10 + 1) % k`.
3.  **Cycle Detection**: By the Pigeonhole Principle, there are only `k` possible remainders ($0$ to $k-1$). If we encounter a remainder we have seen before, it means we have entered a cycle and will never reach 0. We use a `vector<bool>` to keep track of visited remainders.
4.  **Termination**:
    *   If `remainder == 0`, we found the answer. Return the current length.
    *   If we repeat a remainder, return `-1`.

# Complexity
- Time complexity: $O(k)$
  - In the worst case, we might iterate through all possible remainders from $1$ to $k-1$ before finding $0$ or detecting a cycle. Since there are $k$ possible remainders, the loop runs at most $k$ times.

- Space complexity: $O(k)$
  - We use a boolean vector of size `k` to store visited remainders. (Note: `std::vector<bool>` is specialized to use 1 bit per boolean, so for $k=10^5$, this takes only ~12.5 KB of memory). This is much better than use a hashset `std::unordered_set` for that.