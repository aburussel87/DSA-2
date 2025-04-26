#include<iostream>
#include<vector> 
#include<queue>

#include<algorithm>
using namespace std;

int is_prime(int n){
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++){
        if (n % i == 0) return 0;
    }
    return 1;
}
int is_palindrome(int n){
    int rev = 0, original = n;
    while (n > 0){
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return original == rev;
}

int main(){
    
    return 0;
}