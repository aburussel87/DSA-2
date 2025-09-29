#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestPalindrome(const string &s) {
        if (s.empty()) return "";

        int n = s.size();
        int start = 0, end = 0;
        int maxLen = 1;

        for (int i = 0; i < n; i++) {
            int j = i - 1, k = i + 1;
            while (j >= 0 && k < n && s[j] == s[k]) {
                j--; k++;
            }
            int len = k - j - 1;
            if (len > maxLen) {
                maxLen = len;
                start  = j + 1;
                end    = k - 1;
            }
            
            j = i; k = i + 1;
            while (j >= 0 && k < n && s[j] == s[k]) {
                j--; k++;
            }
            len = k - j - 1;
            if (len > maxLen) {
                maxLen = len;
                start  = j + 1;
                end    = k - 1;
            }
        }

        return s.substr(start, end - start + 1);
    }
};