#include <iostream>
using namespace std;

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

int main() {
    cout << RED << "This is red text" << RESET << endl;
    cout << GREEN << "This is green text" << RESET << endl;
    cout << BLUE << "This is blue text" << RESET << endl;
    return 0;
}
