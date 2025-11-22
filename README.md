# Algorithmic Problem Solving in C++20

![C++](https://img.shields.io/badge/Standard-C%2B%2B20-blue.svg?logo=c%2B%2B)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Build](https://img.shields.io/badge/Build-Make-orange.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS-lightgrey.svg)

A curated collection of efficient algorithmic solutions implemented in **Modern C++**. This project treats every problem as a case study, providing detailed documentation on intuition, complexity analysis, and testing.

## Key Features

*   **Deep-Dive Documentation:** Every problem includes a `description.md` containing:
    *   **Intuition:** The thought process behind the solution.
    *   **Approach:** Step-by-step logic breakdown.
    *   **Complexity:** Detailed Time $O(T)$ and Space $O(S)$ proofs.
*   **Modern C++ Practices:** Code utilizes C++20 concepts, `std::string_view`, smart pointers, and lambdas.
*   **Automated Testing:** Custom Python test runner with colorized diffs and edge-case validation.
*   **Clean Architecture:** Separation of logic, testing utilities, and documentation.

## Project Structure

Each problem is self-contained in its own directory featuring the solution code and the documentation.

```text
ProblemSolving/
├── utils/                  # Shared testing framework and printer utilities
├── ...
├── 14_regexMatching/       # Example Problem Directory
│   ├── description.md      # Deep dive: Intuition, Approach, and Complexity
│   └── solution.cpp        # C++ Implementation & Test Cases
├── ...
├── main.cpp                # Entry point
└── run_tests.py            # Automated test runner script
```

## My Engineering Philosophy

I treat algorithmic problems as engineering challenges. Instead of writing one-off scripts, I built a reusable C++20 testing framework with a custom Python runner to ensure code quality, performance, and readability.

I also adhere to a "Documentation First" approach. Each problem includes a `description.md` detailing my thought process, trade-offs, and the evolution from an initial brute-force solution to the final optimized algorithm. Writing these documents helps clarify my thinking and serves as a knowledge base for future review.

## Getting Started

### Prerequisites
*   **Compiler:** GCC (`g++`) or Clang with C++20 support.
*   **Build System:** GNU Make.
*   **Python:** 3.x (for the test runner).

### Compilation & Execution

You can use the included scripts to run tests for specific problems or the entire suite.

**1. Run All Tests**
```bash
python run_tests.py
```

**2. Run a Specific Problem**
Target a problem by ID or directory name:
```bash
python run_tests.py --test=14
# OR
python run_tests.py 14_regexMatching
```

**3. Manual Build (Make)**
```bash
make compile 14_regexMatching
make run 14_regexMatching
```

## Solutions Index

| ID | Problem | Difficulty | Approach | Time | Space |
|:---:|:---|:---:|:---|:---:|:---:|
| 0 | [Sort Array By Parity](./0_sortArrayByParity) | Easy | Two Pointers (In-place) | $O(n)$ | $O(1)$ |
| 1 | [Longest Palindrome Substring](./1_longestPalindromeSubstring) | Medium | Expand Around Center | $O(n^2)$ | $O(1)$ |
| 2 | [Two Sum](./2_twoNumbersSum) | Easy | Hash Map | $O(n)$ | $O(n)$ |
| 3 | [Add Two Numbers](./3_sumTwoNumsAsLists) | Medium | Linked List Traversal | $O(n)$ | $O(n)$ |
| 4 | [Longest Substring No Repeats](./4_lengthOfLongestSubstringWithUniqeChars) | Medium | Sliding Window | $O(n)$ | $O(1)$ |
| 5 | [Palindrome Number](./5_palindromeNumber) | Easy | Half-Number Reversal | $O(\log n)$ | $O(1)$ |
| 6 | [Longest Common Prefix](./6_longestCommonPrefix) | Easy | Vertical Scanning | $O(S)$ | $O(1)$ |
| 7 | [Halves Are Alike](./7_halvesAreAlike) | Easy | Counting | $O(n)$ | $O(1)$ |
| 8 | [Zigzag Conversion](./8_zigzagConversion) | Medium | Mathematical Traversal | $O(n)$ | $O(n)$ |
| 9 | [Median of Two Sorted Arrays](./9_medianOfTwoSortedArrays) | Hard | Binary Search Partitioning | $O(\log n)$ | $O(1)$ |
| 10 | [Reverse Integer](./10_reverseInteger) | Medium | Modulo Arithmetic | $O(\log x)$ | $O(1)$ |
| 11 | [String to Integer (atoi)](./11_atoi) | Medium | Deterministic Finite Automaton | $O(n)$ | $O(1)$ |
| 12 | [Lowest Common Ancestor](./12_lowestCommonAncestor) | Medium | Recursive DFS | $O(n)$ | $O(h)$ |
| 13 | [Substrings With Only 1s](./13_numberOfSubstringsWithOnly1s) | Medium | Arithmetic Progression | $O(n)$ | $O(1)$ |
| 14 | [Regular Expression Matching](./14_regexMatching) | Hard | Dynamic Programming (Bottom-Up) | $O(nm)$ | $O(nm)$ |
| 15 | [Check 1s Distance](./15_checkIfAll1sAreAtLeastKPlacesAway) | Easy | Linear Scan | $O(n)$ | $O(1)$ |
| 16 | [1-bit and 2-bit Characters](./16_1bit2bitCharacters) | Easy | Linear Simulation | $O(n)$ | $O(1)$ |
| 17 | [Keep Multiplying Found Values](./17_keepMultiplyingFoundValuesByTwo) | Easy | Hash Set / Linear Search | $O(n)$ | $O(n)$ |
| 18 | [Container With Most Water](./18_containerWithMostWater) | Medium | Greedy Two Pointers | $O(n)$ | $O(1)$ |
| 19 | [Set Intersection Size At Least Two](./19_setIntersectionSizeAtLeastTwo) | Hard | Greedy (Sorted Intervals) | $O(n \log n)$ | $O(1)$ |
| 20 | [Unique Length 3 Palindromic Subsequences](./20_UniqueLen3PalindromicSubsequence) | Medium | Ranges | $O(n)$ | $O(1)$ |
| 21 | [Minimum Operations To Make All Numbers Divisable By 3](./21_minimumOperationsToMakeAllDivisibleBy3) | Easy | Count numbers where `nums[i] % 3 != 0` | $O(n)$ | $O(1)$ |
| 22 | [Integer To Roman](./20_UniqueLen3PalindromicSubsequence) | Medium | Create digit by digit | $O(log_{10}num)$ in general, but with constraints $O(1)$ | $O(log_{10}num)$ in general, but with constraints $O(1)$ |


## Utility Framework

The repository includes a header-only library (`utils/utils.hpp`) to streamline competitive programming in C++.

**Features:**
*   **Pretty Printing:** Overloaded `operator<<` for `std::vector`, `std::map`, and other STL containers to simplify debugging.
*   **Test Macros:** Helper functions to assert equality and print formatted pass/fail logs in the console.

You can read more in [utils/README.md](./utils/README.md).

```cpp
#include <utils/utils.hpp>

std::vector<int> vec = {1, 2, 3};
std::cout << vec; // Outputs: "{1, 2, 3}"
```

## Contributing

1.  Run the generation script: `./create_solution.sh <problem_name>`
2.  Implement the logic in `solution.cpp`.
3.  Fill out the `description.md` with your intuition and complexity analysis.
4.  Ensure all tests pass via `python run_tests.py`.

## License

Distributed under the MIT License. See `LICENSE` for more information.