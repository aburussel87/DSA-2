#ifndef DOUBLE_HASHING_HASH_TABLE_H
#define DOUBLE_HASHING_HASH_TABLE_H

#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

class DoubleHashingHashTable {
private:
    int N, size;
    vector<pair<string, int>> doubleHashTable;

    int hash1(const string& word);
    int hash2(const string& word);
    int nextPrime(int n);
    bool isPrime(int n);

public:
    DoubleHashingHashTable(int n);

    bool find(const string& key, int& probes, long long& time_taken, bool useHash2);
    bool insert(const string& key, bool useHash2, int& collision);
    bool remove(const string& key, bool useHash2);
};

DoubleHashingHashTable::DoubleHashingHashTable(int n) {
    this->N = nextPrime(n);
    this->size = 0;
    doubleHashTable.assign(N, {"", -1});
}

bool DoubleHashingHashTable::isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= (int)sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int DoubleHashingHashTable::nextPrime(int n) {
    while (!isPrime(n)) n++;
    return n;
}

int DoubleHashingHashTable::hash1(const string& word) {
    long long hash = 0;
    for (char c : word) {
        hash = ((hash * 31) + c) % N;
    }
    return (int)hash;
}

int DoubleHashingHashTable::hash2(const string& word) {
    unsigned long hash = 5381;
    for (char c : word)
        hash = ((hash << 5) + hash) + c;
    return (int)((hash % (N - 1)) + 1);
}

bool DoubleHashingHashTable::find(const string& key, int& probes, long long& time_taken, bool useHash2) {
    auto start = high_resolution_clock::now();
    int h1, h2;
    if (useHash2) {
        h1 = hash2(key);
        h2 = hash1(key);
    } else {
        h1 = hash1(key);
        h2 = hash2(key);
    }
    if (h2 == 0) h2 = 1;
    probes = 0;
    for (int i = 0; i < N; i++) {
        int idx = (h1 + i * h2) % N;
        probes++;
        if (doubleHashTable[idx].first == "") break;
        if (doubleHashTable[idx].first != "#DELETED#" && doubleHashTable[idx].first == key) {
            time_taken = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
            return true;
        }
    }
    time_taken = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
    return false;
}

bool DoubleHashingHashTable::insert(const string& key, bool useHash2, int& collision) {
    int probes_dummy;
    long long time_taken_dummy;
    int h1, h2;
    if (useHash2) {
        h1 = hash2(key);
        h2 = hash1(key);
    } else {
        h1 = hash1(key);
        h2 = hash2(key);
    }
    if (h2 == 0) h2 = 1;
    for (int i = 0; i < N; i++) {
        int idx = (h1 + i * h2) % N;
        if(doubleHashTable[idx].first == key) {
            doubleHashTable[idx].second++; 
            return true;
        }else if (doubleHashTable[idx].first == "" || doubleHashTable[idx].first == "#DELETED#") {
            doubleHashTable[idx] = {key, 1};
            size++;
            return true;
        } else {
            collision++;
        }
    }
    return false;
}

bool DoubleHashingHashTable::remove(const string& key, bool useHash2) {
    int h1, h2;
    if (useHash2) {
        h1 = hash2(key);
        h2 = hash1(key);
    } else {
        h1 = hash1(key);
        h2 = hash2(key);
    }
    if (h2 == 0) h2 = 1;
    for (int i = 0; i < N; i++) {
        int idx = (h1 + i * h2) % N;
        if (doubleHashTable[idx].first == "") break;
        if (doubleHashTable[idx].first != "#DELETED#" && doubleHashTable[idx].first == key) {
            doubleHashTable[idx].first = "#DELETED#";
            size--;
            return true;
        }
    }
    return false;
}

#endif