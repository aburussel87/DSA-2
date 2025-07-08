#include <bits/stdc++.h>
#include "rbt.h"
using namespace std;
using namespace chrono;

class HashTable
{
private:
    int N, S, size;
    vector<RBTREE *> chainingTable;
    vector<pair<string, int>> linearTable;
    vector<pair<string, int>> doubleHashTable;

    int hash1(const string &word);
    int hash2(const string &word);
    int nextPrime(int n);
    bool isPrime(int n);
public:
    HashTable(int n, int s);
    ~HashTable();

    bool find(const string &key, const string &method, int &probes, long long &time_taken, bool useHash2);
    bool insert(const string &key, const string &method, bool useHash2, int &collision);
    bool remove(const string &key, const string &method, bool useHash2);
};

HashTable::HashTable(int n, int s)
{
    this->N = nextPrime(n);
    cout<<"Size of Table: "<<N<<endl;
    this->S = s;
    size = 0;

    chainingTable.resize(N);
    for (int i = 0; i < N; i++)
        chainingTable[i] = new RBTREE();

    linearTable.assign(N, {"", -1});
    doubleHashTable.assign(N, {"", -1});
}

HashTable::~HashTable()
{
    for (int i = 0; i < N; i++)
        delete chainingTable[i];
}

bool HashTable::isPrime(int n)
{
    if (n <= 1)
        return false;
    for (int i = 2; i <= (int)sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int HashTable::nextPrime(int n)
{
    while (!isPrime(n))
        n++;
    return n;
}

int HashTable::hash1(const string &word)
{
    long long hash = 0;
    for (char c : word)
    {
        hash = ((hash * 31) + c) % N;
    }
    return (int)hash;
}

int HashTable::hash2(const string &word)
{
    unsigned long hash = 5381;
    for (char c : word)
        hash = ((hash << 5) + hash) + c; 
    return (int)((hash % (N - 1)) + 1);
}

bool HashTable::find(const string &key, const string &method, int &probes, long long &time_taken, bool useHash2)
{
    auto start = high_resolution_clock::now();
    int idx;

    if (method == "RBT")
    {
        idx = useHash2 ? hash2(key) : hash1(key);
        bool found = chainingTable[idx]->find(key);
        probes = 1;
        time_taken = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
        return found;
    }
    else if (method == "LP")
    {
        int base = useHash2 ? hash2(key) : hash1(key);
        probes = 0;
        for (int i = 0; i < N; i++)
        {
            idx = (base + i * S) % N;
            probes++;
            if (linearTable[idx].first == "")
                break;
            if (linearTable[idx].first != "#DELETED#" && linearTable[idx].first == key)
            {
                time_taken = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
                return true;
            }
        }
        time_taken = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
        return false;
    }
    else if (method == "DH")
    {

        int h1, h2;
        if (useHash2)
        {
            h1 = hash2(key);
            h2 = hash1(key);
        }
        else
        {
            h1 = hash1(key);
            h2 = hash2(key);
        }
        if (h2 == 0)
            h2 = 1;
        probes = 0;
        for (int i = 0; i < N; i++)
        {
            idx = (h1 + i * h2) % N;
            probes++;
            if (doubleHashTable[idx].first == "")
                break;
            if (doubleHashTable[idx].first != "#DELETED#" && doubleHashTable[idx].first == key)
            {
                time_taken = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
                return true;
            }
        }
        time_taken = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
        return false;
    }
    else
    {
        cerr << "Invalid method: " << method << endl;
        return false;
    }
}

bool HashTable::insert(const string &key, const string &method, bool useHash2, int &collision)
{
    int probes = 0;
    long long time_taken;

    if (find(key, method, probes, time_taken, useHash2))
    {
        return false;
    }

    int value = size + 1;
    int idx;

    if (method == "RBT")
    {
        idx = useHash2 ? hash2(key) : hash1(key);
        if (!chainingTable[idx]->isEmpty())
            collision++;
        bool inserted = chainingTable[idx]->insert({key, value});
        if (!inserted)
            return false;
        size++;
        return true;
    }
    else if (method == "LP")
    {
        int base = useHash2 ? hash2(key) : hash1(key);
        for (int i = 0; i < N; i++)
        {
            idx = (base + i * S) % N;
            if (linearTable[idx].first == "" || linearTable[idx].first == "#DELETED#")
            {
                linearTable[idx] = {key, value};
                size++;
                return true;
            }
            else
            {
                collision++;
            }
        }
        return false;
    }
    else if (method == "DH")
    {
        int h1, h2;
        if (useHash2)
        {
            h1 = hash2(key);
            h2 = hash1(key);
        }
        else
        {
            h1 = hash1(key);
            h2 = hash2(key);
        }
        if (h2 == 0)
            h2 = 1;
        for (int i = 0; i < N; i++)
        {
            idx = (h1 + i * h2) % N;
            if (doubleHashTable[idx].first == "" || doubleHashTable[idx].first == "#DELETED#")
            {
                doubleHashTable[idx] = {key, value};
                size++;
                return true;
            }
            else
            {
                collision++;
            }
        }
        return false;
    }
    else
    {
        cerr << "Invalid method: " << method << endl;
        return false;
    }
}

bool HashTable::remove(const string &key, const string &method, bool useHash2)
{
    int idx;

    if (method == "RBT")
    {
        idx = useHash2 ? hash2(key) : hash1(key);
        bool removed = chainingTable[idx]->remove(key);
        if (removed)
            size--;
        return removed;
    }
    else if (method == "LP")
    {
        int base = useHash2 ? hash2(key) : hash1(key);
        for (int i = 0; i < N; i++)
        {
            idx = (base + i * S) % N;
            if (linearTable[idx].first == "")
                break;
            if (linearTable[idx].first != "#DELETED#" && linearTable[idx].first == key)
            {
                linearTable[idx].first = "#DELETED#";
                size--;
                return true;
            }
        }
        return false;
    }
    else if (method == "DH")
    {
        int h1, h2;
        if (useHash2)
        {
            h1 = hash2(key);
            h2 = hash1(key);
        }
        else
        {
            h1 = hash1(key);
            h2 = hash2(key);
        }
        if (h2 == 0)
            h2 = 1;
        for (int i = 0; i < N; i++)
        {
            idx = (h1 + i * h2) % N;
            if (doubleHashTable[idx].first == "")
                break;
            if (doubleHashTable[idx].first != "#DELETED#" && doubleHashTable[idx].first == key)
            {
                doubleHashTable[idx].first = "#DELETED#";
                size--;
                return true;
            }
        }
        return false;
    }
    else
    {
        cerr << "Invalid method: " << method << endl;
        return false;
    }
}
