#include <chrono>
#include <iostream>
using namespace std;
using namespace chrono;

int main() {
    auto start = high_resolution_clock::now();

    for (long long int i = 0; i < 100000000; ++i){
        cout<<i<<endl;
    }

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds\n";
    return 0;
}
