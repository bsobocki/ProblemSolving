# Problem

You are given a ***0-indexed*** `m x n` integer matrix `grid` and an integer `k`. You are currently at position `(0, 0)` and you want to reach position `(m - 1, n - 1)` moving only down or right.

Return the number of paths where the sum of the elements on the path is divisible by `k`. Since the answer may be very large, return it modulo `10^9 + 7`.

#### Example 1:
![](./descriptionImages/example1.png)
```
Input: grid = [[5,2,4],[3,0,5],[0,7,2]], k = 3
Output: 2
Explanation: There are two paths where the sum of the elements on the path is divisible by k.
The first path highlighted in red has a sum of 5 + 2 + 4 + 5 + 2 = 18 which is divisible by 3.
The second path highlighted in blue has a sum of 5 + 3 + 0 + 5 + 2 = 15 which is divisible by 3.
```

#### Example 2:
![](./descriptionImages/example2.png)
```
Input: grid = [[0,0]], k = 5
Output: 1
Explanation: The path highlighted in red has a sum of 0 + 0 = 0 which is divisible by 5.
```

#### Example 3:
![](./descriptionImages/example3.png)
```
Input: grid = [[7,3,4,9],[2,3,6,2],[2,3,7,0]], k = 1
Output: 10
Explanation: Every integer is divisible by 1 so the sum of the elements on every possible path is divisible by k.
```

#### Constraints:

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 5 * 104`
- `1 <= m * n <= 5 * 104`
- `0 <= grid[i][j] <= 100`
- `1 <= k <= 50`

---

# Intuition
The problem asks for the number of paths from the top-left to the bottom-right of a grid where the sum of elements is divisible by $k$.
A standard Depth First Search (DFS) or Brute Force approach would try to explore every possible path. However, given the constraints ($m \times n$ up to $5 \cdot 10^4$), the number of paths can be exponential, leading to a Time Limit Exceeded (TLE).

To optimize this, we notice overlapping subproblems. Reaching a specific cell $(i, j)$ with a specific path sum remainder is a state that we might encounter multiple times from different path origins.
The key insight is that we don't need to track the absolute path sum (which could be very large). We only care about the sum modulo $k$. According to modular arithmetic, $(a + b) \pmod k = ((a \pmod k) + (b \pmod k)) \pmod k$. This allows us to use Dynamic Programming.

# Approach
We use **Top-Down Dynamic Programming with Memoization**.

1.  **State Definition**: We define a state as `(row, col, current_remainder)`.
    *   `row`, `col`: Current position in the grid.
    *   `current_remainder`: The sum of elements along the path so far modulo $k$.
2.  **Memoization Table**: We use a 3D array `mem[row][col][remainder]` to store the number of valid paths from that state to the destination. Initialized with -1 to indicate unvisited states.
3.  **Recursive Logic (`paths` function)**:
    *   **Base Case (Boundaries)**: If `i` or `j` is out of bounds, return 0.
    *   **Memoization Check**: If `mem[i][j][reminder]` is not -1, return the stored result.
    *   **Update Remainder**: Calculate the new remainder including the current cell: `currReminder = (reminder + grid[i][j]) % k`.
    *   **Base Case (Destination)**: If we are at the bottom-right cell `(m-1, n-1)`, check if `currReminder == 0`. Return 1 if true (valid path), 0 otherwise.
    *   **Transitions**: Recursively call the function for the Right cell `(i, j+1)` and the Down cell `(i+1, j)` using the updated `currReminder`.
    *   **Aggregation**: Sum the results of the two recursive calls, apply modulo $10^9 + 7$, and store the result in the memo table.

# Complexity
- **Time complexity**: $O(m \cdot n \cdot k)$
    *   $m$ is the number of rows, $n$ is the number of columns.
    *   There are $m \times n$ cells. For each cell, there are $k$ possible incoming remainder states (0 to $k-1$).
    *   We compute each state exactly once.

- **Space complexity**: $O(m \cdot n \cdot k)$
    *   This is the size of the 3D memoization vector used to store the results.
    *   The recursion stack depth is $O(m + n)$, which is negligible compared to the 3D vector.