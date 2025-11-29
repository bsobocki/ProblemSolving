# Problem

Roman numerals are represented by seven different symbols: `I`, `V`, `X`, `L`, `C`, `D` and `M`.

|Symbol       |Value
|-|-|
|I             |1
|V             |5
|X             |10
|L             |50
|C             |100
|D             |500
|M             |1000

For example, `2` is written as `II` in Roman numeral, just two ones added together. `12` is written as `XII`, which is simply `X` + `II`. The number `27` is written as `XXVII`, which is `XX` + `V` + `II`.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not `IIII`. Instead, the number four is written as `IV`. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as `IX`. There are six instances where subtraction is used:

- `I` can be placed before `V` (5) and `X` (10) to make `4` and `9`.
- `X` can be placed before `L` (50) and `C` (100) to make `40` and `90`.
- `C` can be placed before `D` (500) and `M` (1000) to make `400` and `900`.

Given a roman numeral, convert it to an integer.

 

#### Example 1:
```
Input: s = "III"
Output: 3
Explanation: III = 3.
```


#### Example 2:
```
Input: s = "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
```

#### Example 3:
```
Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
```

#### Constraints:

- `1 <= s.length <= 15`
- `s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').`
- `It is guaranteed that s is a valid roman numeral in the range [1, 3999].`

---

# Intuition

The fundamental rule of Roman numerals is that they are generally additive (e.g., `VI` is `5 + 1`). However, specific subtraction instances exist where a smaller value precedes a larger one (e.g., `IV` is `5 - 1`).

Initially, one might try to hardcode checks for every specific subtraction pair (`IV`, `IX`, `CD`, etc.), but this leads to complex and repetitive code.

A more generalized intuition is to iterate through the string and look at the **current** digit versus the **next** digit:
1. If the current value is **greater than or equal** to the next value (or if it's the last digit), we simply **add** it.
2. If the current value is **less than** the next value, it implies a subtraction pair (e.g., `IV`). We calculate `(next - current)` and skip the next character since we've already processed it.

# Approach

1.  **Fast Conversion**: Instead of using a `HashMap` (which has hashing overhead), we use a local lambda function with a `switch` statement to convert Roman characters to integers. This ensures the fastest possible lookup time $O(1)$.

2.  **Linear Scan with Lookahead**: We iterate through the string from left to right using index `i`.

3.  **Boundary Handling**: Inside the loop, we fetch the value of the current character (`left`). To get the next character (`right`), we use a ternary operator to check bounds. If `i` is at the last character, we treat the `right` value as `0` to ensure correct logic without accessing out-of-bounds memory.

4.  **Logic**:
    -   **Case 1 (Normal):** If `left >= right`, add `left` to the total. The loop naturally increments `i` to the next digit.
    -   **Case 2 (Subtraction):** If `left < right`, we have a pair. We add `right - left` to the total. Crucially, we manually increment `i` (`i++`) inside this block to skip the `right` digit in the next iteration, as it has now been consumed.

# Complexity

-   **Time Complexity**: $O(N)$
    -   We traverse the string exactly once. Although we look ahead, every character is processed a constant number of times.
-   **Space Complexity**: $O(1)$
    -   We only use a few integer variables (`num`, `left`, `right`) and the helper lambda does not allocate extra memory.