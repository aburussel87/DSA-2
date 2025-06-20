#include <iostream>
#include "avl_tree.h"
using namespace std;

int main() {
    AVL_TREE tree;
    tree.print_tree();
    tree.insert(10);
    tree.print_tree();
    tree.insert(20);
    tree.print_tree();
    tree.insert(30);
    tree.print_tree();
    tree.insert(40);
    tree.print_tree();
    tree.insert(50);
    tree.print_tree();
    tree.insert(25);
    tree.print_tree();
    tree.insert(60);
    tree.print_tree();
    tree.insert(70);
    tree.print_tree();
    tree.insert(80);
    tree.print_tree();
    tree.insert(90);
    tree.print_tree();
    tree.insert(100);
    tree.print_tree();
    tree.insert(110);
    tree.print_tree();
    tree.print_bst();
    return 0;
}
