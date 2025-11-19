# Problem
You are given an integer array height of length `n`. There are `n` vertical lines drawn such that the two endpoints of the ith line are `(i, 0)` and `(i, height[i])`.

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.


#### Example 1:
<img src="./question_18.jpg"/>

Input: `height = [1,8,6,2,5,4,8,3,7]`\
Output: `49`\
Explanation: `The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.`


#### Example 2:

Input: `height = [1,1]`\
Output: `1`
 

#### Constraints:

`n == height.length`\
`2 <= n <= 105`\
`0 <= height[i] <= 104`

# Intuition
The brute force approach would check every pair of lines, which is $$O(n^2)$$. To optimize this, we need to make a decision without checking every pair.

The key realization is that the area is determined by:
$$Area = Width \times \min(Height_{left}, Height_{right})$$

If we start with pointers at the very beginning and very end of the array, we maximize the **Width**. From this point on, as we move pointers inward, the width will strictly decrease.

Since the width is shrinking, the **only way** to find a larger area is if the height of the bottleneck (the shorter wall) increases. If we keep the shorter wall and move the taller one, the width decreases and the height is still limited by the shorter wall — meaning the area is guaranteed to be smaller. Therefore, our only logical move is to discard the shorter line in hopes of finding a taller one.

# Approach
1.  **Two Pointers**: Initialize `left` at index `0` and `right` at index `n-1`.
2.  **Loop**: Continue while `left < right`.
3.  **Calculate Area**: Compute the current area using the distance between pointers and the height of the shorter wall. Update the maximum area found so far.
4.  **Move Pointers**: Compare `height[left]` and `height[right]`.
    *   If `height[left]` is smaller, it is the bottleneck. Move `left` forward (`left++`).
    *   If `height[right]` is smaller (or equal), move `right` backward (`right--`).
    *   This effectively "eliminates" the shorter wall because it cannot possibly form a better container with any other line inside the current range.

# Complexity
- Time complexity: $O(n)$
  We use a two-pointer approach where `left` moves right and `right` moves left. Each element in the array is visited at most once.

- Space complexity: $O(1)$
  We only use a few variables to store pointers and the area calculation, regardless of the input size.

# Code
```cpp []
class Solution {
public:
    // we go through the vector looking for highest walls
    // time complexity O(n)
    // space complexity O(1)
    int maxArea(const vector<int>& height) {
        // start with the biggest width (distance between walls)
        int left = 0;
        int right = height.size()-1;

        int maxAreaVal = 0;
        // we will go through the vector moving left or right
        while(left < right) {
            int area = std::min(height[left], height[right]) * (right - left);
            maxAreaVal = std::max(maxAreaVal, area);

            // maximize areas by leaving higher walls and moving from smaller
            // because each step decreases width, so to maximize areas we need to choose higher walls
            if (height[left] > height[right])
                right--; // move left
            else
                left++; // move right
        }
        return maxAreaVal;
    }
};
```