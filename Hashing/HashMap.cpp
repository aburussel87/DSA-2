#include "HashMap.h"

int main() {
    string s = "abcdefaghijbklmc";
    int n = (int)s.size();

    HashMapChar map(n);
    int l = 0, maxLen = 0, startIndex = 0;

    for (int r = 0; r < n; ++r) {
        char currentChar = s[r];
        if (map.contains(currentChar)) {
            int prevIndex = *map.get(currentChar);
            if (prevIndex >= l) {
                l = prevIndex + 1;
            }
        }
        map.put(currentChar, r);

        if (r - l + 1 > maxLen) {
            maxLen = r - l + 1;
            startIndex = l;
        }
    }

    cout << "Longest non-repeating substring length: " << maxLen << "\n";
    cout << "Substring: " << s.substr(startIndex, maxLen) << "\n";

    return 0;
}
