#include <iostream>
#include <vector>
#include <sstream>
#include <random>
#include <chrono>

using namespace std;

void insertionSort(vector<int> &arr, long long &comparisons) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // aktualna liczba sortowana
        int j = i - 1;

        // Porównanie i przesunięcie elementów
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            comparisons++;
        }
        if (j >= 0) comparisons++; // Dla ostatniego porównania, jeśli było
        arr[j + 1] = key;
    }
}

vector<int> generateRandomNumbers(int n) {
    vector<int> numbers(n);
    // Ustawienie generatora liczb losowych
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(INT_MIN, INT_MAX);

    for (int i = 0; i < n; i++) {
        numbers[i] = dis(gen);
    }

    return numbers;
}

int main() {
    cout << "Wybierz opcje: 1 - Wprowadz dane recznie, 2 - Generuj dane losowo: ";
    int choice;
    cin >> choice;

    vector<int> numbers;

    if (choice == 1) {
        cout << "Wprowadz liczby oddzielone spacja: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Czyszczenie bufora

        string input;
        getline(cin, input);
        istringstream iss(input);
        int number;
        while (iss >> number) {
            numbers.push_back(number);
        }
    } else if (choice == 2) {
        cout << "Podaj liczbę elementów do wygenerowania: ";
        int n;
        cin >> n;
        numbers = generateRandomNumbers(n);
    } else {
        cerr << "Nieprawidłowy wybór." << endl;
        return 1;
    }

    long long comparisons = 0;
    insertionSort(numbers, comparisons);

    cout << "Posortowane liczby: ";
    for (int num: numbers) {
        cout << num << " ";
    }
    cout << "\nLiczba porownan: " << comparisons << endl;

    // Obliczanie i wyświetlanie wartości a
    double a = static_cast<double>(comparisons) / (numbers.size() * numbers.size());
    cout << "Wartość a = t/n^2: " << a << endl;

    return 0;
}
