# Problem
Given an integer array `nums`, move all the even integers at the beginning of the array followed by all the odd integers.

Return ***any array** that satisfies this condition*.


### Example 1:

Input: `nums = [3,1,2,4]` \
Output: `[2,4,3,1]` \
Explanation: `The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.`


### Example 2:

Input: `nums = [0]` \
Output: `[0]`
 

Constraints:

`1 <= nums.length <= 5000` \
`0 <= nums[i] <= 5000`

# Solution

## Solution "In Place"

Time complexity $O(n)$ \
Space complexity $O(1)$ - only if we use non-const reference `vector<int>& nums` as an argument! \
Space complexity $O(n)$ - if we pass `nums` by value or copy vector in case `const reference` argument

We will go from the left to the right looking for an odd number and from the right to the left looking for an even number.
If we find then then we swap them.
We are doing this until `left` index and `right` index meet.

## Solution "Linear"

Time complexity $O(n)$ \
Space complexity $O(n)$ - because we copy vector

Very similar to the previous one, but instead of doing it in place we are doing it simpler - by creating another vector and push elements front or back.

## Solution "std::sort"

Time complexity $O(n log n)$ - because of std::sort
Space complexity $O(1)$ in case of non-const reference as argument and $O(n)$ otherwise - we just do std::sort and returns result