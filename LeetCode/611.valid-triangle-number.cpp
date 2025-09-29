#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int immediateSmallerIndex(const vector<int> &nums, int l, int x) {
        int r = (int)nums.size() - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (nums[m] < x)
                l = m + 1;
            else
                r = m - 1;
        }
        return r; // largest index with nums[r] < x, or -1 if none
    }

    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int total = 0;

        for (int i = 0; i < (int)nums.size() - 2; i++) {
            for (int j = i + 1; j < (int)nums.size() - 1; j++) {
                int k = immediateSmallerIndex(nums, j + 1, nums[i] + nums[j]);
                if (k > j)              // ensure we found at least one valid k
                    total += k - j;     // not +1
            }
        }
        return total;
    }
};
