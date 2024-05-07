#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

int liczbaPorownan = 0;

int podziel(vector<int> &arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        liczbaPorownan++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

int quickSelect(vector<int> &arr, int low, int high, int k) {
    if (low <= high) {
        int pi = podziel(arr, low, high);
        if (pi - low == k - 1)
            return arr[pi];
        else if (pi - low > k - 1)
            return quickSelect(arr, low, pi - 1, k);
        else
            return quickSelect(arr, pi + 1, high, k - pi + low - 1);
    }
    return INT_MAX;
}

vector<int> generujLosoweDane(int n) {
    vector<int> dane(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(-1000000, 1000000);
    for (int &element: dane) {
        element = distrib(gen);
    }
    return dane;
}

int main() {
    int n, k;
    cout << "Podaj liczbę elementów: ";
    cin >> n;
    cout << "Podaj k-ty najmniejszy element do znalezienia: ";
    cin >> k;

    vector<int> dane = generujLosoweDane(n);
    auto start = high_resolution_clock::now();
    int ktyElement = quickSelect(dane, 0, n - 1, k);
    auto stop = high_resolution_clock::now();
    auto czasTrwania = duration_cast<microseconds>(stop - start);

    cout << "k-ty najmniejszy element to: " << ktyElement << endl;
    cout << "Liczba porównań: " << liczbaPorownan << endl;
    cout << "Stosunek liczby porównań do liczby elementów: " << static_cast<double>(liczbaPorownan) / n << endl;
    cout << "Czas wykonania: " << czasTrwania.count() << " mikrosekund" << endl;

    return 0;
}
