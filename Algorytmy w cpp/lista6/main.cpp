#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct MultiArrayDoublyLinkedList {
    static const int MAX_SIZE = 100;
    string key[MAX_SIZE];
    int next[MAX_SIZE];
    int prev[MAX_SIZE];
    int free;
    int head;

    MultiArrayDoublyLinkedList() {
        for (int i = 0; i < MAX_SIZE - 1; ++i) {
            next[i] = i + 1;
        }
        next[MAX_SIZE - 1] = -1;
        free = 0;
        head = -1;
        fill(prev, prev + MAX_SIZE, -1);
    }

    void insert(string surname) {
        if (free == -1) {
            cout << "List is full!" << endl;
            return;
        }

        int current = free;
        free = next[free];

        key[current] = surname;

        int idx = head;
        int last = -1;
        while (idx != -1 && key[idx] < surname) {
            last = idx;
            idx = next[idx];
        }

        if (last == -1) {
            next[current] = head;
            head = current;
            if (idx != -1) {
                prev[idx] = current;
            }
        } else {
            next[current] = next[last];
            prev[current] = last;
            next[last] = current;
            if (next[current] != -1) {
                prev[next[current]] = current;
            }
        }
    }

    void print(bool reverse = false) {
        if (head == -1) {
            cout << "List is empty!" << endl;
            return;
        }

        int index = head;
        vector<string> names;
        while (index != -1) {
            names.push_back(key[index]);
            index = next[index];
        }
        if (reverse) {
            std::reverse(names.begin(), names.end());
        }
        for (const auto &name: names) {
            cout << name << endl;
        }
    }

    void printFromChar(char start) {
        int index = head;
        while (index != -1) {
            if (key[index][0] == start) {
                cout << key[index] << endl;
            }
            index = next[index];
        }
    }
};

int main() {
    MultiArrayDoublyLinkedList list;
    string command, surname;
    char startChar;

    while (true) {
        cout << "Enter command (insert, print, print_reverse, print_from_char, exit): ";
        cin >> command;

        if (command == "insert") {
            cout << "Enter surname: ";
            cin >> surname;
            list.insert(surname);
        } else if (command == "print") {
            list.print();
        } else if (command == "print_reverse") {
            list.print(true);
        } else if (command == "print_from_char") {
            cout << "Enter start character: ";
            cin >> startChar;
            list.printFromChar(startChar);
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command!" << endl;
        }
    }

    return 0;
}
