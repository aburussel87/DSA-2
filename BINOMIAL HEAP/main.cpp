#include "heap.h"

int main() {
    Advanced_Heap heap;
    ifstream input("input.txt");
    ofstream output("output.txt");

    if (!input.is_open()) {
        cout << "Couldnt open input file." << endl;
        return 1;
    }
    if (!output.is_open()) {
        cout << "Couldnt open output file." << endl;
        return 1;
    }

    string line;
    while (getline(input, line)) {
        stringstream ss(line);
        string cmd;
        ss >> cmd;
        try {
            if (cmd == "I") {
                int key;
                ss >> key;
                heap.insert(key);
            } else if (cmd == "F") {
                int minKey = heap.findMin();
                if (minKey != -1)
                    output << "Find Min returned: " << minKey << endl;
            } else if (cmd == "E") {
                int minKey = heap.extractMin();
                if (minKey != -1)
                    output << "Extract Min returned: " << minKey << endl;
            } else if (cmd == "D") {
                int oldKey, newKey;
                ss >> oldKey >> newKey;
                heap.updateKey(oldKey, newKey);
            } else if (cmd == "R") {
                int key;
                ss >> key;
                heap.removeKey(key);
            } else if (cmd == "P") {
                heap.printHeap(output);
            }
        } catch (...) {
            output << "couldn't execute command: " << line << endl;
        }
    }

    input.close();
    output.close();
    return 0;
}
