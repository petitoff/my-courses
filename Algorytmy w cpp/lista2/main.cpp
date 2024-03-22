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

int partition(vector<int> &arr, int low, int high, long long &comparisons) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
        comparisons++;
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int> &arr, int low, int high, long long &comparisons) {
    if (low < high) {
        int pivot = partition(arr, low, high, comparisons);
        quickSort(arr, low, pivot - 1, comparisons);
        quickSort(arr, pivot + 1, high, comparisons);
    }
}

// Funkcja do wyświetlania fragmentu wektora
void printVectorFragment(const vector<int> &vec) {
    for (int i = 0; i < 50 && i < vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << "..."; // Znak kontynuacji, jeśli wektor jest dłuższy
    cout << endl;
}

int main() {
    cout << "Wybierz opcje: 1 - Wprowadz dane recznie, 2 - Generuj dane losowo: ";
    int choice;
    cin >> choice;

    vector<int> numbers;
    if (choice == 1) {
        cout << "Wprowadz liczby oddzielone spacja: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

    cout << "Wybierz algorytm sortowania: 1 - Sortowanie przez wstawianie, 2 - Quick Sort: ";
    int sortChoice;
    cin >> sortChoice;

    long long comparisons = 0;
    auto start = chrono::steady_clock::now();
    if (sortChoice == 1) {
        insertionSort(numbers, comparisons);
    } else if (sortChoice == 2) {
        quickSort(numbers, 0, numbers.size() - 1, comparisons);
    } else {
        cerr << "Nieprawidłowy wybór algorytmu." << endl;
        return 1;
    }
    auto end = chrono::steady_clock::now();

    cout << "Fragment tablicy przed sortowaniem: " << endl;
    printVectorFragment(numbers);
    cout << "Fragment tablicy po sortowaniu: " << endl;
    printVectorFragment(numbers);

    cout << "Liczba porownan: " << comparisons << endl;
    double a = static_cast<double>(comparisons) / (numbers.size() * numbers.size());
    cout << "Wartość a = t/n^2: " << a << endl;

    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Czas wykonania (ms): " << elapsed << endl;

    return 0;
}
