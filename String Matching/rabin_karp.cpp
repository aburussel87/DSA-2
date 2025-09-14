#include <bits/stdc++.h>
using namespace std;

int main() {
    string text, pattern;
    cout<<"Enter text: ";
    getline(cin, text);
    cout<<"Enter Pattern: ";
    getline(cin, pattern);

    transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    int n = text.size();
    int m = pattern.size();
    int d = 256;
    int q = 101;    
    int p = 0, t = 0, h = 1;

    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (p == t && text.compare(i, m, pattern) == 0)
            cout << "MATCHING FOUND AT " << i+1 << "\n";
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) t += q;
        }
    }
    return 0;
}
