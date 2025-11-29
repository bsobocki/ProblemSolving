#include <iostream>
#include <vector>
#include <utils/utils.hpp>
#include <random>
#include <cmath>

using namespace std;

constexpr int inf = std::numeric_limits<int>::max();
constexpr int _inf  = std::numeric_limits<int>::min();

double findMedianSortedArraysBinSearch(const vector<int>& nums1, const vector<int>& nums2) {
    // we want nums1 to be the shorter vector
    if (nums1.size() > nums2.size())
        return findMedianSortedArraysBinSearch(nums2, nums1);

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

vector<int> mergedArrays(const vector<int>& nums1, const vector<int>& nums2) {
    const size_t totalSize = nums1.size() + nums2.size();

    vector<int> merged;
    merged.reserve(totalSize);
    
    auto num1 = nums1.begin();
    auto num2 = nums2.begin();

    while(num1 != nums1.end() || num2 != nums2.end()) {
        if (num2 == nums2.end()) {
            while (num1 != nums1.end()) merged.push_back(*num1++);
        }
        else if (num1 == nums1.end()) {
            while (num2 != nums2.end()) merged.push_back(*num2++);
        }
        else if (*num1 < *num2) {
            merged.push_back(*num1++);
        }
        else {
            merged.push_back(*num2++);
        }
    }

    return merged;
}

// O(n) - time & space complexity
// easy way - merge vectors into one and get median from that
double findMedianWholeSortedArrays_WholeMergedArray(const vector<int>& nums1, const vector<int>& nums2) {
    const size_t totalSize = nums1.size() + nums2.size();
    const size_t medianIndex = (totalSize+1)/2 - 1;
    const vector<int> merged = mergedArrays(nums1, nums2);
    return totalSize%2 == 0 ? (merged[medianIndex] + merged[medianIndex+1]) / 2.0 : merged[medianIndex];
}


// O(n) - time complexity
// O(1) - space complexity
// easy way but a little bit upgraded - go through vectors one by one in order until you get median (basically just a half of elements)
double findMedianSortedArrays_HalfOfMergedArray(const vector<int>& nums1, const vector<int>& nums2) {
    size_t totalSize = nums1.size() + nums2.size();
    size_t medianIndex = (totalSize+1)/2 - 1;

    auto getMedian = [](size_t medianIndex, vector<int> nums) -> double {
        if (nums.size() % 2 == 0) {
            return (nums[medianIndex] + nums[medianIndex+1]) / 2.0;
        }
        return nums[medianIndex];
    };

    if (nums1.empty())
        return getMedian(medianIndex, nums2);
    else if (nums2.empty())
        return getMedian(medianIndex, nums1);

    double median = 0.0;
    size_t count = 0;
    size_t idx1 = 0;
    size_t idx2 = 0;

    // we are going through both vectors to find medianIndex'th element in merged array
    // at each step we will mark current lowest element as median
    while(count <= medianIndex) {
        // if we have only nums2 elements left then we have to go further in nums2
        if (idx1 >= nums1.size()) {
            median = nums2[idx2];
            idx2++;
        }
        // if we have only nums1 elements left
        // or we have elements in both arrays but current element from nums1 is smaller 
        // then we go further in nums1
        else if(idx2 >= nums2.size() || nums1[idx1] < nums2[idx2]) {
            median = nums1[idx1];
            idx1++;
        }
        // if we have elements in both arrays but current element from nums2 is smaller or equal current element from nums1
        // then we go further in nums2
        else {
            median = nums2[idx2];
            idx2++;
        }
        count++;
    }

    // now if we find median, but our total size is even
    // then we need to calculate median as average of two elements in the middle
    // so current found median and next smallest available element
    if (totalSize % 2 == 0) {
        // if we have no more elements in nums1 then the next element is the first element from the rest of nums2
        if (idx1 >= nums1.size())
            return (median + nums2[idx2]) / 2.0;
        // if we do have more elements in nums 1 but we don't have more elements in nums2
        // or nums1 element is smaller then the second element for median calculations is current nums1 element
        else if (idx2 >= nums2.size() || nums1[idx1] < nums2[idx2])
            return (median + nums1[idx1]) / 2.0;
        // if we have more elements in both arrays but current element from nums2 is smaller
        // then this element is the second element we need to calculate median
        else
            return (median + nums2[idx2]) / 2.0;
    }

    return median;
}

struct Test {
    vector<int> nums1;
    vector<int> nums2;
    double expectedResult;

    string getInfo() const {
        stringstream ss;
        ss << nums1 << " + " << nums2 << " => " << mergedArrays(nums1, nums2);
        return ss.str();
    }
};

vector<int> generateRandomSortedVector(size_t size) {
    if (size == 0) return {};

    vector<int> vec;
    vec.reserve(size);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1,100);

    int current = dist(gen);
    vec.push_back(current);

    for (size_t i = 1; i < size; i++) {
        current += dist(gen);
        vec.push_back(current);
    }

    return vec;
}

void runSolution() {
    const vector<Test> tests = {
        // Basic cases
        {{1,3}, {2}, 2.0},
        {{1,2}, {3,4}, 2.5},
        
        // Empty array cases
        {{}, {1}, 1.0},
        {{2}, {}, 2.0},
        {{}, {1,2,3,4,5}, 3.0},
        {{}, {2,3}, 2.5},
        
        // Single element in both
        {{1}, {2}, 1.5},
        {{2}, {1}, 1.5},
        
        // Different sizes
        {{1,2,3}, {4,5,6,7,8}, 4.5},
        {{1}, {2,3,4,5,6}, 3.5},
        
        // All elements in nums1 < all in nums2
        {{1,2}, {3,4}, 2.5},
        {{1,2,3}, {4,5,6}, 3.5},
        
        // All elements in nums2 < all in nums1
        {{3,4}, {1,2}, 2.5},
        {{4,5,6}, {1,2,3}, 3.5},
        
        // Overlapping ranges
        {{1,3,5,7,9}, {2,4,6,8,10}, 5.5},
        {{1,2,3,4,5}, {6,7,8,9,10}, 5.5},
        
        // Duplicates
        {{1,1,1}, {1,1,1}, 1.0},
        {{1,2,2}, {2,3,4}, 2.0},
        {{1,1,3,3}, {1,1,3,3}, 2.0},
        
        // Negative numbers
        {{-5,-3,-1}, {0,2,4}, -0.5},
        {{-10,-5,0}, {5,10}, 0.0},
        {{-2,-1}, {3}, -1.0},
        
        // Large difference in sizes
        {{1}, {2,3,4,5,6,7,8,9,10}, 5.5},
        {{1,2,3,4,5,6,7,8,9}, {10}, 5.5},
        
        // Same arrays
        {{1,2,3}, {1,2,3}, 2.0},
        
        // Even and odd total lengths
        {{1,3,5}, {2,4,6,8}, 4.0},
        {{1,2,3,4}, {5,6}, 3.5},
        
        // Edge values
        {{-1000000}, {1000000}, 0.0},
        {{1}, {1}, 1.0},
        
        // Complex interleaving
        {{1,3,8,9,15}, {7,11,18,19,21,25}, 11.0},
        {{1,2}, {1,2,3}, 2.0},
        {{3}, {1,2,4,5,6}, 3.5},
        {{2}, {1,3,4,5,6}, 3.5},
    };

    runTests(tests, [](const Test& test) {
        double medianWholeArr = findMedianWholeSortedArrays_WholeMergedArray(test.nums1, test.nums2);
        double medianHalfArr = findMedianSortedArrays_HalfOfMergedArray(test.nums1, test.nums2);
        double medianBinSearch = findMedianSortedArraysBinSearch(test.nums1, test.nums2);
        bool result = medianWholeArr == medianHalfArr && medianHalfArr == test.expectedResult && medianBinSearch == test.expectedResult;
        std::cout << "\ninfo: "  << test.getInfo() << "," << endl;
        std::cout << "median whole: " << medianWholeArr << "," << endl;
        std::cout << "median half: " << medianHalfArr << "," << endl;
        std::cout << "median BinSearch: " << medianBinSearch << "," << endl;
        std::cout << "expected: " << test.expectedResult << "," << endl;
        std::cout << "result: " << getColoredResult(result) << endl << endl;
        return result;
    });

    std::cout << "\n----- RANDOM TESTS - CHECK IF RESULTS THE SAME AS FOR TRIVIAL SOLUTION ----\n" << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist_0_100(0, 100);
    uniform_int_distribution<int> dist_1_100(1, 100);

    constexpr size_t RANDOM_TESTS_NUM = 10;
    for (size_t i = 1; i <= RANDOM_TESTS_NUM; i++) {
        int size1 = dist_0_100(gen);
        int size2 = dist_0_100(gen);

        if (size1 == 0 && size2 == 0)
            size1 = dist_1_100(gen);
        
        vector<int> nums1 = generateRandomSortedVector(size1);
        vector<int> nums2 = generateRandomSortedVector(size2);

        double medianWholeArr = findMedianWholeSortedArrays_WholeMergedArray(nums1, nums2);
        double medianHalfArr = findMedianSortedArrays_HalfOfMergedArray(nums1, nums2);
        double medianBinSearch = findMedianSortedArraysBinSearch(nums1, nums2);

        std::cout << "\n" << "size1: " << size1 << ",\nsize2: " << size2;
        std::cout << ",\nmedianWholeArr: " << medianWholeArr << ",\nmedianHalfArr: " << medianHalfArr << ",\nmedianBinSearch: " << medianBinSearch;
        std::cout << ",\nresult: " << getColoredResult(medianWholeArr==medianHalfArr && medianHalfArr==medianBinSearch) << endl << endl;
    }
}
