# Intuition
<!-- Describe your first thoughts on how to solve this problem. -->
Go through each row and calculate a position of the next letter in a row.

For the first and the last row we are making steps as $(numRows - 1)*2$, because we are visiting each row $2$ times except start and the lowest one - this is the biggest step.

The rest steps (odd) increases and (even) decreases by $2$. 


# Complexity
- Time complexity: $O(n)$

- Space complexity: $O(n)$

Where $n = s.length()$

# Code
```cpp []
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1 || s.length() == 0 || numRows >= s.length()) return s;

        string result;

        // we are going through all rows by taking numRows-1 steps twice (up and down) 
        int initStep = (numRows - 1) * 2;

        // for the first [0] row
        for (int i = 0; i < s.length(); i += initStep)
            result += s[i];
 
        // even steps are different than odd steps (expect the middle row when numRows is odd)
        int evenStep = 2; // for second row we make 2 steps to the next letter
        int oddStep = initStep-2; // for second row we will make less steps by 2 than initStep number

        // for steps inside
        for (int currRowNum = 1; currRowNum < numRows-1; currRowNum++) {
            bool isOddStep = true;
            int i = currRowNum;
            while (i < s.length()) {
                result += s[i];

                if (isOddStep) i += oddStep;
                else i += evenStep;
                isOddStep = !isOddStep;
            }
            // with each row we are lower, so odd steps will be shorter by 2 and even steps will be longer by 2
            oddStep -= 2;
            evenStep += 2;
        }

        // for the last [numRows-1] row
        for (int i = numRows-1; i < s.length(); i += initStep)
            result += s[i];

        return result;
    }
};
```