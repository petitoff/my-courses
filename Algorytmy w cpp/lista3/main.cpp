#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

void printArray(const vector<int> &arr, int limit = 50) {
    for (int i = 0; i < min(limit, (int) arr.size()); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void heapify(vector<int> &arr, int n, int i, long long &comparisons) {
    int largest = i;
    bool done = false;

    // Use loop instead of recursion
    while (!done) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        largest = i;

        if (l < n && arr[l] > arr[largest]) {
            largest = l;
        }

        if (r < n && arr[r] > arr[largest]) {
            largest = r;
        }

        comparisons += (l < n) + (r < n); // Update comparisons

        if (largest != i) {
            swap(arr[i], arr[largest]);
            i = largest;
        } else {
            done = true;
        }
    }
}

void heapSort(vector<int> &arr, long long &comparisons) {
    int n = arr.size();
    comparisons = 0;

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, comparisons);
    }

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, comparisons);
    }
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    long long comparisons;

    cout << "Original array is: ";
    printArray(arr);

    auto start = high_resolution_clock::now();
    heapSort(arr, comparisons);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Sorted array is: ";
    printArray(arr);
    cout << "Number of comparisons: " << comparisons << "\n";
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    return 0;
}
