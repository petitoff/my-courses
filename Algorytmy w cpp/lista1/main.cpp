#include <iostream>
#include <vector>
#include <sstream> // Do obsługi strumieni stringów

using namespace std;

// Funkcja do sortowania metodą wstawiania
void insertionSort(vector<int> &arr, long long &comparisons) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            comparisons++; // Liczenie porównań
        }
        comparisons++; // Dla ostatniego porównania w while
        arr[j + 1] = key;
    }
}

int main() {
    string line;
    cout << "Podaj liczby do posortowania, oddzielajac je spacja: ";
    getline(cin, line); // Wczytanie całej linii jako string
    stringstream ss(line); // Utworzenie strumienia stringowego

    vector<int> arr;
    int number;
    while (ss >> number) { // Czytanie kolejnych liczb z linii
        arr.push_back(number);
    }

    long long comparisons = 0; // Zmienna do zliczania porównań

    insertionSort(arr, comparisons);

    // Wypisanie posortowanej tablicy
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    double a = comparisons / (double) (arr.size() * arr.size()); // Obliczenie wartości ilorazu a

    cout << "Liczba wykonanych porownan: " << comparisons << endl;
    cout << "Wartosc a = t/n^2: " << a << endl;

    return 0;
}
