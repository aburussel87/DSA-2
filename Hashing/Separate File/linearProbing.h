#ifndef LINEAR_PROBING_HASH_TABLE_H
#define LINEAR_PROBING_HASH_TABLE_H

#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

class LinearProbingHashTable {
private:
    int N, S, size;
    vector<pair<string, int>> linearTable;

    int hash1(const string& word);
    int hash2(const string& word);
    int nextPrime(int n);
    bool isPrime(int n);

public:
    LinearProbingHashTable(int n, int s);

    bool find(const string& key, int& probes, long long& time_taken, bool useHash2);
    bool insert(const string& key, bool useHash2, int& collision);
    bool remove(const string& key, bool useHash2);
};

LinearProbingHashTable::LinearProbingHashTable(int n, int s) {
    this->N = nextPrime(n);
    this->S = s;
    this->size = 0;
    linearTable.assign(N, {"", -1});
}

bool LinearProbingHashTable::isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= (int)sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int LinearProbingHashTable::nextPrime(int n) {
    while (!isPrime(n)) n++;
    return n;
}

int LinearProbingHashTable::hash1(const string& word) {
    long long hash = 0;
    for (char c : word) {
        hash = ((hash * 31) + c) % N;
    }
    return (int)hash;
}

int LinearProbingHashTable::hash2(const string& word) {
    unsigned long hash = 5381;
    for (char c : word)
        hash = ((hash << 5) + hash) + c;
    return (int)((hash % (N - 1)) + 1);
}

bool LinearProbingHashTable::find(const string& key, int& probes, long long& time_taken, bool useHash2) {
    auto start = high_resolution_clock::now();
    int base = useHash2 ? hash2(key) : hash1(key);
    probes = 0;
    for (int i = 0; i < N; i++) {
        int idx = (base + i * S) % N;
        probes++;
        if (linearTable[idx].first == "") break;
        if (linearTable[idx].first != "#DELETED#" && linearTable[idx].first == key) {
            time_taken = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
            return true;
        }
    }
    time_taken = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
    return false;
}

bool LinearProbingHashTable::insert(const string& key, bool useHash2, int& collision) {
    int probes_dummy;
    long long time_taken_dummy;
    if (find(key, probes_dummy, time_taken_dummy, useHash2)) {
        return false;
    }

    int value = size + 1;
    int base = useHash2 ? hash2(key) : hash1(key);
    for (int i = 0; i < N; i++) {
        int idx = (base + i * S) % N;
        if (linearTable[idx].first == "" || linearTable[idx].first == "#DELETED#") {
            linearTable[idx] = {key, value};
            size++;
            return true;
        } else {
            collision++;
        }
    }
    return false;
}

bool LinearProbingHashTable::remove(const string& key, bool useHash2) {
    int base = useHash2 ? hash2(key) : hash1(key);
    for (int i = 0; i < N; i++) {
        int idx = (base + i * S) % N;
        if (linearTable[idx].first == "") break;
        if (linearTable[idx].first != "#DELETED#" && linearTable[idx].first == key) {
            linearTable[idx].first = "#DELETED#";
            size--;
            return true;
        }
    }
    return false;
}

#endif 