#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>

using namespace std;
using namespace std::chrono;

// Funkcja do wypisywania elementów wektora
void printArray(const vector<int>& arr, int limit = 50) {
    for (int i = 0; i < min(limit, (int)arr.size()); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Funkcja scalająca dwie posortowane części wektora
void merge(vector<int>& arr, int left, int mid, int right, long long& comparisons) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
        comparisons++; // Liczenie porównań
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Główna funkcja algorytmu sortowania przez scalanie
void mergeSort(vector<int>& arr, int left, int right, long long& comparisons) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comparisons);
        mergeSort(arr, mid + 1, right, comparisons);
        merge(arr, left, mid, right, comparisons);
    }
}

// Funkcja do generowania losowego wektora
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000000); // Zakres wartości od 1 do 1000000

    for (int& element : arr) {
        element = dis(gen);
    }
    return arr;
}

// Główna funkcja programu
int main() {
    int n = 100000; // Rozmiar ciągu do sortowania
    vector<int> arr = generateRandomArray(n);
    long long comparisons = 0; // Licznik porównań

    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1, comparisons);
    auto stop = high_resolution_clock::now();

    cout << "Pierwsze 50 elementów posortowanego ciągu: ";
    printArray(arr);

    auto duration = duration_cast<microseconds>(stop - start);
    double c = (double)comparisons / (n * log2(n));

    cout << "Czas działania algorytmu: " << duration.count() << " mikrosekund" << endl;
    cout << "Ilość porównań: " << comparisons << endl;
    cout << "Wartość ilorazu c = t/(n*log(n)): " << c << endl;
    
    return 0;
}
