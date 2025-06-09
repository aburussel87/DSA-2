#include "RBT.h"
#include <vector>
#include <string>
#include <fstream>
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

    void AddItem(ofstream& out, string id, string name, string amount) {
        if (tree->insert(stoi(id), name, stoi(amount))) {
            tree->print_RBT(out);
        }
    }

    void BuyItem(ofstream& out, string id, string amount) {
        if (tree->decrease_amount(stoi(id), stoi(amount))) {
            tree->print_RBT(out);
            return;
        }
        tree->print_RBT(out);
        cout<<"Not Available\n";
        out<<"Not Available\n";
    }

    void CheckItem(ofstream& out, string id) {
        Node* item = tree->find(stoi(id));
        if (item == nullptr) {
            cout<<"Not Available\n";
            out<<"Not Available\n";
            return ;
        }
        cout << "Stock Left: " << item->amount << endl;
        out << "Stock Left: " << item->amount << endl;
    }

    void ClearInventory(ofstream& out) {
        if (tree->length() == 0) {
            cout<<"Unsuccessful\n";
            out<<"Unsuccessful\n";
            return;
        }
        delete tree;
        tree = new RBTREE();
        cout<<"Successful\n";
        out<<"Successful\n";
    }

    void Empty(ofstream& out) {
        if(tree->length() == 0){
            cout<<"Yes\n";
            out<<"Yes\n";
            return;
        }
        cout<<"No\n";
        out<<"No\n";
    }

    void InventorySize(ofstream& out) {
        cout<< tree->length()<<endl;
    }

    void ListInventory(ofstream& out) {
        tree->sortedList(out);
    }
};
