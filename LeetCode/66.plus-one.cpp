#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int carry = 1; // we want to add 1
        for (int i = digits.size() - 1; i >= 0 && carry; --i) {
            int sum = digits[i] + carry;
            digits[i] = sum % 10;
            carry    = sum / 10;
        }
        if (carry) {
            digits.insert(digits.begin(), carry);
        }
        return digits;
    }
};

