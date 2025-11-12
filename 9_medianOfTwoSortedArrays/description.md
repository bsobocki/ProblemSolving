# Problem

Given two sorted arrays `nums1` and `nums2` of size `n` and `m` respectively, return the median of the two sorted arrays.

The overall run time complexity should be `O(log (m+n))`.

### Example 1:

Input: `nums1 = [1,3], nums2 = [2]` \
Output: `2.00000` \
Explanation: `merged array = [1,2,3] and median is 2.`


### Example 2:

Input: `nums1 = [1,2], nums2 = [3,4]` \
Output: `2.50000` \
Explanation: `merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.` 
 

### Constraints:

`nums1.length == n` \
`nums2.length == m` \
`0 <= n <= 1000` \
`0 <= m <= 1000` \
`1 <= m + n <= 2000` \
`-106 <= nums1[i], nums2[i] <= 106`

# Intuition
The median divides a dataset into two equal halves. Instead of merging two sorted arrays (which would be O(n+m)), we can find the correct "partition point" in each array using binary search. If we partition both arrays such that all elements on the left are smaller than all elements on the right, the median lies at this boundary.

# Approach

1. **Binary search on the smaller array** to minimize time complexity to O(log(min(n,m)))

2. **Partition both arrays**: For each candidate partition of `nums1`, calculate the corresponding partition of `nums2` such that the total left half (left part of `nums1` partition and left part of  `nums2` partition combined) contains exactly `(n+m+1)/2` smallest elements

3. **Validate the partition**: A valid partition satisfies:
   - `maxLeft1 ≤ minRight2` (largest element in left half of nums1 ≤ smallest in right half of nums2)
   - `maxLeft2 ≤ minRight1` (largest element in left half of nums2 ≤ smallest in right half of nums1)
   - `maxLeft1 ≤ minRight1 AND maxLeft2 ≤ minRight2` but those conditions are covered because of arrays orders 

4. **Adjust binary search**:
   - If `maxLeft1 > minRight2`: partition1 is too large, search left half
   - If `maxLeft2 > minRight1`: partition1 is too small, search right half

5. **Calculate median**: Once valid partition found:
   - **Odd total size**: return `max(maxLeft1, maxLeft2)` (the middle element is in the left partition)
   - **Even total size**: return average of `max(maxLeft1, maxLeft2)` and `min(minRight1, minRight2)`

6. **Edge cases**: Use infinity guards (`INT_MIN`/`INT_MAX`) when a partition is at the boundary (0 or array size)

# Complexity
- Time complexity: $O(\log(\min(n, m)))$
  - Binary search on the smaller array

- Space complexity: $O(1)$
  - Only using constant extra space for variables

# Code
```cpp []
constexpr int inf = std::numeric_limits<int>::max();
constexpr int _inf  = std::numeric_limits<int>::min();

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    // we want nums1 to be the shorter vector
    if (nums1.size() > nums2.size())
        return findMedianSortedArrays(nums2, nums1);

    const size_t n = nums1.size();
    const size_t m = nums2.size();

    // we will divide elements into two partitions (smaller half "left" and bigger half "right")
    // the median is the biggest element from smaller "left" partition if total size is odd
    // or it is an average from the biggest element from the smaller partition
    // and smallest element from the bigger one

    // in our smaller partition ((n+m)/2 smallest elements) we want to include median, so
    // for even totalSize N we will make (N+1)/2 so it is the same as N/2 (one of two middle values for median covered)
    // for odd totalSize N we want to have median in the smaller part, so we will do (N+1)/2
    // to include it (take a ceil from the division)
    const size_t partitionSize = (n + m + 1) / 2;

    // we will consider partitioning based on nums1 (shorter vector)
    // because we will process binary search on it to find correct partitions
    // so we will initialize this partitioning position on nums1 edge elements and we will move them to the left or right
    // only for this vector and adjust the second partitioning (for nums2) based on this one
    int left = 0;
    int right = nums1.size();

    // Binary search finds the valid partition (guaranteed to exist in sorted arrays)
    // - If partition1's left has elements too large → move left (shift elements to partition2)
    // - If partition2's left has elements too large → move right (take more from partition1)
    while(true) {
        // partition represents the number of elements taken from each array for the left half
        const int partition1 = (left + right) / 2;
        const int partition2 = partitionSize - partition1 ;
        
        // use -inf and +inf for compariosns when there is no leftMax or minRight in one of partitions
        const int maxLeft1 = partition1 == 0 ? _inf : nums1[partition1 -1];
        const int minRight1 = partition1 == n ? inf : nums1[partition1];
        const int maxLeft2 = partition2 == 0 ? _inf : nums2[partition2 - 1];
        const int minRight2 = partition2 == m ? inf : nums2[partition2];

        if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
            // if we found correct partitions then we will return max left element
            // if n+m is odd or an average of max left and min right
            if ((n + m) % 2 == 0) {
                return (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2.0;
            }
            return max(maxLeft1, maxLeft2);
        }
        else if (maxLeft1 > minRight2) {
            // our smaller partition have bigger elements, so we need to move it left
            right = partition1 - 1;
        }
        else {
            // our right partition have smaller elements, so we need to move it right
            left = partition1 + 1;
        }
    }

    return 0.0; // unreachable - satisfies compiler
}
};
```