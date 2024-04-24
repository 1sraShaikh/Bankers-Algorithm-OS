#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int NUM_RESOURCES = 3;
const int NUM_PROCESSES = 5;

// Function to check if the system is in a safe state
bool isSafeState(vector<vector<int>>& allocation, vector<vector<int>>& max, vector<int>& available) {
    vector<int> work = available;
    vector<bool> finish(NUM_PROCESSES, false);
    vector<int> safeSequence;

    int count = 0;
    while (count < NUM_PROCESSES) {
        bool found = false;
        for (int i = 0; i < NUM_PROCESSES; ++i) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < NUM_RESOURCES; ++j) {
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < NUM_RESOURCES; ++j)
                        work[j] += allocation[i][j];
                    finish[i] = true;
                    safeSequence.push_back(i);
                    ++count;
                    found = true;
                }
            }
        }
        if (!found) // If no process found that can be allocated resources, then system is in unsafe state
            return false;
    }
    // System is in safe state
    cout << "System is in a safe state.\nSafe sequence: ";
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        cout << "P" << safeSequence[i];
        if (i < NUM_PROCESSES - 1)
            cout << " -> ";
    }
    cout << endl;
    return true;
}

int main() {
    // Initialize allocation, max, and available arrays
    vector<vector<int>> allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    vector<vector<int>> max = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    vector<int> available = {3, 3, 2};

    // Check if the system is in a safe state
    isSafeState(allocation, max, available);

    return 0;
}
