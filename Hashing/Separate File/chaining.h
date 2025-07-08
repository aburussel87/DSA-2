#ifndef CHAINING_HASH_TABLE_H
#define CHAINING_HASH_TABLE_H

#include <bits/stdc++.h>
#include "rbt.h" 
using namespace std;
using namespace chrono;

class ChainingHashTable {
private:
    int N, size;
    vector<RBTREE*> chainingTable;

    int hash1(const string& word);
    int hash2(const string& word);
    int nextPrime(int n);
    bool isPrime(int n);

public:
    ChainingHashTable(int n);
    ~ChainingHashTable();

    bool find(const string& key, int& probes, long long& time_taken, bool useHash2);
    bool insert(const string& key, bool useHash2, int& collision);
    bool remove(const string& key, bool useHash2);
};


ChainingHashTable::ChainingHashTable(int n) {
    this->N = nextPrime(n);
    this->size = 0;
    chainingTable.resize(N);
    for (int i = 0; i < N; i++)
        chainingTable[i] = new RBTREE();
}

ChainingHashTable::~ChainingHashTable() {
    for (int i = 0; i < N; i++)
        delete chainingTable[i];
}

bool ChainingHashTable::isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= (int)sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int ChainingHashTable::nextPrime(int n) {
    while (!isPrime(n)) n++;
    return n;
}

int ChainingHashTable::hash1(const string& word) {
    long long hash = 0;
    for (char c : word) {
        hash = ((hash * 31) + c) % N;
    }
    return (int)hash;
}

int ChainingHashTable::hash2(const string& word) {
    unsigned long hash = 5381;
    for (char c : word)
        hash = ((hash << 5) + hash) + c;
    return (int)((hash % (N - 1)) + 1);
}

bool ChainingHashTable::find(const string& key, int& probes, long long& time_taken, bool useHash2) {
    auto start = high_resolution_clock::now();
    int idx = useHash2 ? hash2(key) : hash1(key);
    bool found = chainingTable[idx]->find(key);
    probes = 1;
    time_taken = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
    return found;
}

bool ChainingHashTable::insert(const string& key, bool useHash2, int& collision) {
    int probes_dummy;
    long long time_taken_dummy;
    if (find(key, probes_dummy, time_taken_dummy, useHash2)) {
        return false;
    }

    int value = size + 1;
    int idx = useHash2 ? hash2(key) : hash1(key);
    if (!chainingTable[idx]->isEmpty())
        collision++;
    bool inserted = chainingTable[idx]->insert({key, value});
    if (!inserted) return false;
    size++;
    return true;
}

bool ChainingHashTable::remove(const string& key, bool useHash2) {
    int idx = useHash2 ? hash2(key) : hash1(key);
    bool removed = chainingTable[idx]->remove(key);
    if (removed) size--;
    return removed;
}

#endif 