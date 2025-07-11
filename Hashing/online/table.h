#include <bits/stdc++.h>
using namespace std;

struct InnerEntry {
    int user_id;
    string permission;
    bool is_occupied;
    bool is_deleted;
    InnerEntry() : user_id(-1), permission(""), is_occupied(false), is_deleted(false) {}
};

struct InnerHashTable {
    int size;
    vector<InnerEntry> table;

    InnerHashTable(int n) : size(n), table(n) {}

    int hash2(int key) {
        return (key * 7 + 3) % size;
    }

    void insert(int user_id, const string& permission) {
        for (int i = 0; i < size; i++) {
            int idx = (hash2(user_id) + i * i) % size;
            if (!table[idx].is_occupied || table[idx].is_deleted || table[idx].user_id == user_id) {
                table[idx].user_id = user_id;
                table[idx].permission = permission;
                table[idx].is_occupied = true;
                table[idx].is_deleted = false;
                return;
            }
        }
        cout<<"Table is Full\n";
    }


    string search(int user_id) {
        for (int i = 0; i < size; i++) {
            int idx = (hash2(user_id) + i * i) % size;
            if (!table[idx].is_occupied) return ""; 
            if (!table[idx].is_deleted && table[idx].user_id == user_id) return table[idx].permission;
        }
        return "";
    }

    pair<int, string> remove(int user_id) {
        for (int i = 0; i < size; i++) {
            int idx = (hash2(user_id) + i * i) % size;
            if (!table[idx].is_occupied) break;
            if (!table[idx].is_deleted && table[idx].user_id == user_id) {
                table[idx].is_deleted = true;
                return {table[idx].user_id, table[idx].permission};
            }
        } 
        return {-1, ""};
    }

    vector<pair<int, string>> get_all() {
        vector<pair<int, string>> result;
        for (auto& e : table) {
            if (e.is_occupied && !e.is_deleted)
                result.push_back({e.user_id, e.permission});
        }
        return result;
    }
};

struct OuterEntry {
    int group_id;
    InnerHashTable* inner_table;
    bool is_occupied;
    bool is_deleted;
    OuterEntry() : group_id(-1), inner_table(nullptr), is_occupied(false), is_deleted(false) {}
};

struct OuterHashTable {
    int size;
    vector<OuterEntry> table;

    OuterHashTable(int n) : size(n), table(n) {}

    int hash1(int key) {
        return key % size;
    }

    pair<int, bool> find_group_idx(int group_id) {
        for (int i = 0; i < size; i++) {
            int idx = (hash1(group_id) + i) % size;
            if (!table[idx].is_occupied) return {idx, false};
            if (!table[idx].is_deleted && table[idx].group_id == group_id) return {idx, true};
        }
        return {-1, false}; 
    }

    void insert(int group_id, int user_id, const string& permission) {
        pair<int,bool> data  = find_group_idx(group_id);
        if (data.first == -1) return;
        if (!data.second) {
            table[data.first].group_id = group_id;
            table[data.first].inner_table = new InnerHashTable(size);
            table[data.first].is_occupied = true;
            table[data.first].is_deleted = false;
        }
        table[data.first].inner_table->insert(user_id, permission);
    }

    string search_user(int group_id, int user_id) {
        pair<int,bool> data  = find_group_idx(group_id);
        if (!data.second) return "Group not found";
        string perm = table[data.first].inner_table->search(user_id);
        if (perm == "") return "User not found in group " + to_string(group_id);
        return perm;
    }

    vector<pair<int, string>> search_group(int group_id, bool &found_flag) {
        pair<int,bool> data  = find_group_idx(group_id);
        if (!data.second) {
            found_flag = false;
            return {};
        }
        found_flag = true;
        return table[data.first].inner_table->get_all();
    }

    pair<int, string> remove(int group_id, int user_id, bool &found_flag) {
       pair<int,bool> data  = find_group_idx(group_id);
        if (!data.second) {
            found_flag = false;
            return {-1, ""};
        }
        pair<int, string> res = table[data.first].inner_table->remove(user_id);
        if (res.first == -1) {
            found_flag = false;
            return res;
        }
        found_flag = true;
        return res;
    }
};

