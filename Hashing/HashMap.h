#include <bits/stdc++.h>
using namespace std;

class HashMapString {
    int capacity;
    int size;
    vector<pair<string, int>> table;

    unsigned long long hashString(const string &s) {
        const unsigned long long p = 131; 
        unsigned long long hash = 0;
        for (char c : s) {
            hash = hash * p + c;
        }
        return hash % capacity;
    }

public:
    HashMapString(int n) {
        capacity = n;
        size = 0;
        table.assign(n, {"", -1});
    }

    void put(const string &key, int value) {
        int idx = (int)hashString(key);
        for (int i = 0; i < capacity; ++i) {
            int pos = (idx + i) % capacity;
            if (table[pos].first == "" || table[pos].first == "#") {
                table[pos] = make_pair(key, value);
                ++size;
                return;
            }
            if (table[pos].first == key) {
                table[pos].second = value;
                return;
            }
        }
        cout << "HashMap full, can't insert key: " << key << "\n";
    }

    bool contains(const string &key) {
        int idx = (int)hashString(key);
        for (int i = 0; i < capacity; ++i) {
            int pos = (idx + i) % capacity;
            if (table[pos].first == "") return false;
            if (table[pos].first == key) return true;
        }
        return false;
    }

    void remove(const string &key) {
        int idx = (int)hashString(key);
        for (int i = 0; i < capacity; ++i) {
            int pos = (idx + i) % capacity;
            if (table[pos].first == "") return;
            if (table[pos].first == key) {
                table[pos] = make_pair("#", -1);
                --size;
                return;
            }
        }
    }

    int* get(const string &key) {
        int idx = (int)hashString(key);
        for (int i = 0; i < capacity; ++i) {
            int pos = (idx + i) % capacity;
            if (table[pos].first == "") return nullptr;
            if (table[pos].first == key) return &table[pos].second;
        }
        return nullptr;
    }

    void print() {
        cout << "HashMapString Contents:\n";
        for (int i = 0; i < capacity; ++i) {
            if (table[i].first != "" && table[i].first != "#") {
                cout << "[" << i << "] " << table[i].first << " => " << table[i].second << "\n";
            }
        }
    }
};

class HashMapChar {
    int capacity;
    int size;
    vector<pair<char, int>> table;

    int hashChar(char c) {
        return c % capacity;
    }

public:
    HashMapChar(int n) {
        capacity = n;
        size = 0;
        table.assign(n, {'\0', -1});
    }

    void put(char key, int value) {
        int idx = hashChar(key);
        for (int i = 0; i < capacity; ++i) {
            int pos = (idx + i) % capacity;
            if (table[pos].first == '\0' || table[pos].first == '#') {
                table[pos] = make_pair(key, value);
                ++size;
                return;
            }
            if (table[pos].first == key) {
                table[pos].second = value;
                return;
            }
        }
        cout << "HashMapChar full, can't insert key: " << key << "\n";
    }

    bool contains(char key) {
        int idx = hashChar(key);
        for (int i = 0; i < capacity; ++i) {
            int pos = (idx + i) % capacity;
            if (table[pos].first == '\0') return false;
            if (table[pos].first == key) return true;
        }
        return false;
    }

    void remove(char key) {
        int idx = hashChar(key);
        for (int i = 0; i < capacity; ++i) {
            int pos = (idx + i) % capacity;
            if (table[pos].first == '\0') return;
            if (table[pos].first == key) {
                table[pos].first = '#';
                table[pos].second = -1;
                --size;
                return;
            }
        }
    }

    int* get(char key) {
        int idx = hashChar(key);
        for (int i = 0; i < capacity; ++i) {
            int pos = (idx + i) % capacity;
            if (table[pos].first == '\0') return nullptr;
            if (table[pos].first == key) return &table[pos].second;
        }
        return nullptr;
    }

    void print() {
        cout << "HashMapChar Contents:\n";
        for (int i = 0; i < capacity; ++i) {
            if (table[i].first != '\0' && table[i].first != '#') {
                cout << "[" << i << "] " << table[i].first << " => " << table[i].second << "\n";
            }
        }
    }
};


unsigned int hashIntImproved(unsigned int key) {
    key = ~key + (key << 15); 
    key = key ^ (key >> 12);
    key = key + (key << 2);
    key = key ^ (key >> 4);
    key = key * 2057;  
    key = key ^ (key >> 16);
    return key;
}

class HashMapInt {
    int capacity;
    int size;
    vector<pair<int, int>> table;

    int hashInt(int key) {
        unsigned int h = hashIntImproved((unsigned int)key);
        return h % capacity;
    }

public:
    HashMapInt(int n) {
        capacity = n;
        size = 0;
        table.assign(n, {-1, -1});
    }

    void put(int key, int value) {
        int idx = hashInt(key);
        for (int i = 0; i < capacity; ++i) {
            int pos = (idx + i) % capacity;
            if (table[pos].first == -1 || table[pos].first == -2) {
                table[pos] = make_pair(key, value);
                ++size;
                return;
            }
            if (table[pos].first == key) {
                table[pos].second = value;
                return;
            }
        }
        cout << "HashMapInt full, can't insert key: " << key << "\n";
    }

    bool contains(int key) {
        int idx = hashInt(key);
        for (int i = 0; i < capacity; ++i) {
            int pos = (idx + i) % capacity;
            if (table[pos].first == -1) return false;
            if (table[pos].first == key) return true;
        }
        return false;
    }

    void remove(int key) {
        int idx = hashInt(key);
        for (int i = 0; i < capacity; ++i) {
            int pos = (idx + i) % capacity;
            if (table[pos].first == -1) return;
            if (table[pos].first == key) {
                table[pos].first = -2;
                table[pos].second = -1;
                --size;
                return;
            }
        }
    }

    int* get(int key) {
        int idx = hashInt(key);
        for (int i = 0; i < capacity; ++i) {
            int pos = (idx + i) % capacity;
            if (table[pos].first == -1) return nullptr;
            if (table[pos].first == key) return &table[pos].second;
        }
        return nullptr;
    }

    void print() {
        cout << "HashMapInt Contents:\n";
        for (int i = 0; i < capacity; ++i) {
            if (table[i].first != -1 && table[i].first != -2) {
                cout << "[" << i << "] " << table[i].first << " => " << table[i].second << "\n";
            }
        }
    }
};


