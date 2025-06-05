#include "RBT.h"
#include <vector>
#include <string>
using namespace std;

class INVENTORY {
    RBTREE* tree;

public:
    INVENTORY() {
        tree = new RBTREE();
    }

    ~INVENTORY() {
        delete tree;
    }

    bool AddItem(string id, string name, string amount) {
        if (tree->insert(stoi(id), name, stoi(amount))) {
            tree->print_RBT();
            return true;
        }
        return false;
    }

    bool BuyItem(string id, string amount) {
        if (tree->decrease_amount(stoi(id), stoi(amount))) {
            tree->print_RBT();
            return true;
        }
        tree->print_RBT();
        return false;
    }

    int CheckItem(string id) {
        Node* item = tree->find(stoi(id));
        if (item == nullptr) {
            return -1;
        }
        return item->amount;
    }

    bool ClearInventory() {
        if (tree->length() == 0) {
            return false;
        }
        delete tree;
        tree = new RBTREE();
        return true;
    }

    bool Empty() {
        return tree->length() == 0;
    }

    int InventorySize() {
        return tree->length();
    }

    void ListInventory() {
        tree->sortedList();
    }
};
