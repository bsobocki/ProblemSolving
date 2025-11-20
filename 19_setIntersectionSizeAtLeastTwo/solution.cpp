#include <iostream>
#include <utils/utils.hpp>
#include <set>

using namespace std;

std::string intervalsToString(const vector<vector<int>>& intervals) {
    std::stringstream ss;
    ss << "{ ";
    for (auto in : intervals) ss << in <<", ";
    ss << "}";
    return ss.str();
}

// optimal solution - built based on my previous one and the power of internet :D 
int intersectionSizeTwo(const vector<vector<int>>& intervals) {
    // for my tests (i have const reference because of how i run my tests) - additional copy O(n)
    std::vector<std::vector<int>> intvls = intervals;

    // sort intervals by end_i and if ends are equal, put the one with the LARGER start first
    // if two intervals end at the same time, e.g., [2, 5] and [4, 5], it is safer to process the smaller (subset) interval [4, 5] first.
    // if you satisfy [4, 5] first (picking 4, 5), then [2, 5] is automatically satisfied.
    std::sort(intvls.begin(), intvls.end(), [](const vector<int>& intvl1, const vector<int>& intvl2) {
        return  intvl1[1] < intvl2[1] || // check ends 
                (intvl1[1] == intvl2[1] && intvl1[0] > intvl2[0]); // if ends are equal then check starts
    });

    int lastAddedMCS = -1;
    int prevAddedMCS = -1;
    int count = 0;

    // we will build MCS (minimal containing set) from interval end values to make sure that we putting
    // numbers that are from those intervals and in correct order
    for (auto& intvl:  intvls) {
        int start = intvl[0];
        int end = intvl[1];
        
        // if last value added to mcs is less then start then we need to add values from this interval
        if (lastAddedMCS < start) {
            lastAddedMCS = end;
            prevAddedMCS = end-1;
            count += 2;
        }
        // if we already have value that are from intvl, so we need to check if there is a second one
        // if previously added value to mcs is less than start it meand that we need additional value from this interval
        else if (prevAddedMCS < start) {
            prevAddedMCS = lastAddedMCS;
            lastAddedMCS = end;
            count++;
        }

        // if the element previously added is also in the interval then we have two values we need
        // so we don't need to do anything
    }
    return count;
}

// find maximum value that is less or equal than val
// returns set.end() if there is no such value
auto find_max_less_equal(const std::set<int>& set, int val)
{
    if (set.empty()) return set.end();

    auto i = set.lower_bound(val);

    if (i == set.end() && !set.empty()) return std::prev(i);

    // we found our value or i is set.end() then just return i
    if (*i == val) return i;
    
    // we found i, but it is more than val

    // if i is set.begin() and *i is greater then there is no max less value
    if (i == set.begin()) return set.end();

    return std::prev(i);
}

// my first attempt build 100% on my own: overcomplicated
int intersectionSizeTwoOvercomplicated(const vector<vector<int>>& intervals) {
    // for my tests (i have const reference because of how i run my tests) - additional copy O(n)
    std::vector<std::vector<int>> intvls = intervals;

    // create unique interval boundaries set - it will tell us about where intervals are crossing each others (like OX-asis)
    // for example: {[1,7],[2,7],[3,30],[4,8],[12,16]} -> {1,2,3,4,7,8,12,16}
    // they overlapping each others creating intervals: {[1,2],[2,3],[3,4],[4,7],[7,8],[8,12],[12,16]}
    // those intervalse would give us numbers we are looking for (because those numbers are in one or more intervals)
    std::set<int> uniqueIntervalBoundaries;
    for (auto interval: intvls) {
        uniqueIntervalBoundaries.insert(interval[0]);
        uniqueIntervalBoundaries.insert(interval[1]);
    }

    // sort intervals by end_i for checking values in result MCS (minimal containing set)
    std::sort(intvls.begin(), intvls.end(), [](const vector<int>& intvl1, const vector<int>& intvl2) {
        return intvl1[1] < intvl2[1];
    });

    // we will build MCS (minimal containing set) from unique boundaries to make sure that we putting
    // numbers that are from those intervals in correct order
    std::set<int> mcs;
    for (auto intvl:  intvls) {
        int start = intvl[0];
        int end = intvl[1];

        auto maxFromMCS = find_max_less_equal(mcs, end);
        
        // if MCS doesn't have end value that is part of interval
        // then we need to add two max values from unique bonundaries that are part of interval
        if (maxFromMCS == mcs.end() || *maxFromMCS < start) {
            // they have to be available - that is how we created this unique bonundaries set!
            // they are two maximum values from this interval that are in unique bondaries
            // it means that they belongs to one or more intervals
            auto maxFromUniqueBoundaries = find_max_less_equal(uniqueIntervalBoundaries, end);
            mcs.insert(*maxFromUniqueBoundaries);
            mcs.insert(*std::prev(maxFromUniqueBoundaries));
        }
        // if we already have value that are from intvl, so we need to check if there is a second one
        else {
            // if found element is the first or there is one but it doesn't belong to interval
            // then we need to add one from unique boundaries
            if (maxFromMCS == mcs.begin() || *std::prev(maxFromMCS) < start) {
                auto maxFromUniqueBoundaries = find_max_less_equal(uniqueIntervalBoundaries, end);
                // if we have found max from unique boundaries in mcs then we will add previous value from unique boundaries
                // because we can be sure that this one will be part of current interval (unique boundaries have at least 2 nums from this interval)
                if (*maxFromUniqueBoundaries == *maxFromMCS)
                    mcs.insert(*std::prev(maxFromUniqueBoundaries));
                // if max from unique boundaries is different than found max from mcs then we just add it
                else
                    mcs.insert(*maxFromUniqueBoundaries);
            }
            // if the element before maxFromMCS alse belongs to interval then we have both values as well
            // so we don't need to do anything
        }
    }

    return mcs.size();
}

struct Test {
    vector<vector<int>> intervals;
    int expectedResult;

    std::string getInfo() const {
        return intervalsToString(intervals);
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        // Bigger custom test
        {
            {{4,8},{2,7},{3,30},{1,7}, {15,42}, {12,16}, {142,458}, {256,400}, {10,300}},
            6
        },

        // Standard gaps
        // [1,3] needs {2,3}. [3,7] overlaps on 3, needs 7. [8,9] needs {8,9}. Total 5.
        {
            {{1,3}, {3,7}, {8,9}},
            5
        },

        // Heavy overlap
        // Solution {2,3,5} satisfies all.
        {
            {{1,3}, {1,4}, {2,5}, {3,5}},
            3
        },

        // Tight boundaries
        // [1,2]->{1,2}, [2,3]->{3} (2 exists), [4,5]->{4,5}. Total 5.
        {
            {{1,2}, {2,3}, {2,4}, {4,5}},
            5
        },

        // Completely Disjoint
        // Each interval [x, x+1] requires 2 unique numbers. 3 * 2 = 6.
        {
            {{1,2}, {5,6}, {10,11}},
            6
        },

        // Fully Nested
        // Solving for the smallest inner interval [3,8] ({7,8}) satisfies outer ones.
        {
            {{1,10}, {2,9}, {3,8}},
            2
        },

        // Chain Overlap
        // [1,3]->{2,3}. [2,4] has {2,3}. [3,5] has {3}, adds {5}. Total 3.
        {
            {{1,3}, {2,4}, {3,5}},
            3
        },

        // Large Range vs Tiny Range
        // [49,50] needs {49,50}. [0,10000] contains that.
        {
            {{0,100000}, {49,50}},
            2
        },

        // Minimal Length Chain
        // [1,2]->{1,2}. [2,3] adds {3}. [3,4] adds {4}. Total 4.
        {
            {{1,2}, {2,3}, {3,4}},
            4
        },

        // Unsorted Input / Complex Overlap
        // Logic sorts by end: [2,4], [4,7], [6,8], [1,9]. Result: {3,4,7,8}.
        {
            {{6,8}, {1,9}, {2,4}, {4,7}},
            4
        },
        
        // Identical intervals
        // Should just be 2.
        {
            {{1,3}, {1,3}, {1,3}},
            2
        },
        
        // Same end times, different start times
        // Sorted: [4,5], [3,5], [2,5], [1,5]. 
        // [4,5] -> {4,5}. All others contain {4,5}.
        {
            {{1,5}, {2,5}, {3,5}, {4,5}},
            2
        }
    };

    runTests(tests, [](const Test& test){
        int intersection = intersectionSizeTwo(test.intervals);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, intersection) << std::endl;
        return intersection == test.expectedResult;
    });
}