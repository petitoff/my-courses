#include <iostream>
#include <vector>
#include <stack>

// Maksymalny rozmiar drzewa (indeksowane od 1 do MAX_SIZE)
const int MAX_SIZE = 100;

// Definicja tablic reprezentujących drzewo BST
std::vector<int> p(MAX_SIZE + 1, 0);    // rodzic
std::vector<int> key(MAX_SIZE + 1, 0);  // klucz
std::vector<int> left(MAX_SIZE + 1, 0); // lewe dziecko
std::vector<int> right(MAX_SIZE + 1, 0); // prawe dziecko

int root = 0; // globalna zmienna dla korzenia drzewa

// Funkcja znajdująca największy klucz w drzewie BST
int BST_MAX(int root) {
    while (right[root] != 0) {
        root = right[root];
    }
    return key[root];
}

// Funkcja znajdująca najmniejszy klucz w drzewie BST
int BST_MIN(int root) {
    while (left[root] != 0) {
        root = left[root];
    }
    return key[root];
}

// Funkcja wstawiająca klucz do drzewa BST
void BST_INSERT(int z, int z_key) {
    key[z] = z_key;
    int y = 0;  // zmienna pomocnicza na rodzica z
    int x = root;  // zaczynamy od korzenia

    while (x != 0) {
        y = x;
        if (key[z] < key[x]) {
            x = left[x];
        } else {
            x = right[x];
        }
    }
    p[z] = y;
    if (y == 0) {
        root = z; // Drzewo było puste, z staje się korzeniem
    } else if (key[z] < key[y]) {
        left[y] = z;
    } else {
        right[y] = z;
    }
}

// Funkcja sprawdzająca, czy klucz jest w drzewie BST
bool BST_MEMBER(int k, int root) {
    while (root != 0) {
        if (key[root] == k) return true;
        else if (k < key[root]) root = left[root];
        else root = right[root];
    }
    return false;
}

// Funkcja wykonująca przechodzenie inorder drzewa BST (bez rekurencji)
void BST_INORDER(int root) {
    std::stack<int> s;
    int current = root;
    while (current != 0 || !s.empty()) {
        while (current != 0) {
            s.push(current);
            current = left[current];
        }
        current = s.top(); s.pop();
        std::cout << key[current] << " ";
        current = right[current];
    }
}

int main() {
    // Wczytywanie danych
    int n, z_key;
    std::cout << "Enter the number of nodes to insert: ";
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cout << "Enter key for node " << i << ": ";
        std::cin >> z_key;
        BST_INSERT(i, z_key);
    }

    std::cout << "BST Inorder Traversal: ";
    BST_INORDER(root);
    std::cout << std::endl;

    std::cout << "BST Maximum Key: " << BST_MAX(root) << std::endl;
    std::cout << "BST Minimum Key: " << BST_MIN(root) << std::endl;

    std::cout << "Enter a key to check membership: ";
    std::cin >> z_key;
    std::cout << "Membership result: " << (BST_MEMBER(z_key, root) ? "Present" : "Not present") << std::endl;

    return 0;
}
