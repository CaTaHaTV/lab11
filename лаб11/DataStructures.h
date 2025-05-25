#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <stdexcept>
#include <cstring>
#include <type_traits>
using namespace std;


inline int cmpStrings(const char* a, const char* b) {
    return strcmp(a, b);
}


template<typename T>
struct Comparator {
    static int compare(const T& a, const T& b) {
        if (a < b) return -1;
        if (a > b) return 1;
        return 0;
    }
};

template<>
struct Comparator<char*> {
    static int compare(const char* a, const char* b) {
        return cmpStrings(a, b);
    }
};


template<typename T>
class Stack {
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };
    Node* top;
public:
    Stack() : top(nullptr) {}
    ~Stack() { clear(); }

    void push(const T& value) {
        Node* node = new Node(value);
        node->next = top;
        top = node;
    }

    void input() {
        T value;
        cout << "Enter value: ";
        cin >> value;
        push(value);
    }

    bool search(const T& key) {
        for (Node* curr = top; curr; curr = curr->next)
            if (Comparator<T>::compare(curr->data, key) == 0)
                return true;
        return false;
    }

    void remove(const T& key) {
        Node* prev = nullptr;
        Node* curr = top;
        while (curr) {
            if (Comparator<T>::compare(curr->data, key) == 0) {
                if (prev)
                    prev->next = curr->next;
                else
                    top = curr->next;
                delete curr;
                curr = (prev ? prev->next : top);
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
    }

    void print() {
        for (Node* curr = top; curr; curr = curr->next)
            cout << curr->data << " ";
        cout << endl;
    }

    void save(const string& filename) {
        ofstream ofs(filename, ios::binary);
        if (!ofs) throw runtime_error("Cannot open file");
        for (Node* curr = top; curr; curr = curr->next)
            ofs.write((char*)&curr->data, sizeof(T));
    }

    void load(const string& filename) {
        clear();
        ifstream ifs(filename, ios::binary);
        if (!ifs) throw runtime_error("Cannot open file");
        T value;
        while (ifs.read((char*)&value, sizeof(T)))
            push(value);
    }

    void clear() {
        while (top) {
            Node* tmp = top;
            top = top->next;
            delete tmp;
        }
    }

    void sort() {
        
        if (!top || !top->next) return;
        bool swapped;
        do {
            swapped = false;
            Node* curr = top;
            while (curr->next) {
                if (Comparator<T>::compare(curr->data, curr->next->data) > 0) {
                    swap(curr->data, curr->next->data);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
    }
};


template<typename T>
class Queue {
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };
    Node* front;
    Node* rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}
    ~Queue() { clear(); }

    void enqueue(const T& value) {
        Node* node = new Node(value);
        if (!rear) {
            front = rear = node;
        }
        else {
            rear->next = node;
            rear = node;
        }
    }

    void input() {
        T value;
        cout << "Enter value: ";
        cin >> value;
        enqueue(value);
    }

    bool search(const T& key) {
        for (Node* curr = front; curr; curr = curr->next)
            if (Comparator<T>::compare(curr->data, key) == 0)
                return true;
        return false;
    }

    void remove(const T& key) {
        Node* curr = front;
        Node* prev = nullptr;
        while (curr) {
            if (Comparator<T>::compare(curr->data, key) == 0) {
                Node* tmp = curr;
                if (prev)
                    prev->next = curr->next;
                else
                    front = curr->next;
                if (curr == rear)
                    rear = prev;
                curr = (prev ? prev->next : front);
                delete tmp;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
    }

    void print() {
        for (Node* curr = front; curr; curr = curr->next)
            cout << curr->data << " ";
        cout << endl;
    }

    void save(const string& filename) {
        ofstream ofs(filename, ios::binary);
        if (!ofs) throw runtime_error("Cannot open file");
        for (Node* curr = front; curr; curr = curr->next)
            ofs.write((char*)&curr->data, sizeof(T));
    }

    void load(const string& filename) {
        clear();
        ifstream ifs(filename, ios::binary);
        if (!ifs) throw runtime_error("Cannot open file");
        T value;
        while (ifs.read((char*)&value, sizeof(T)))
            enqueue(value);
    }

    void clear() {
        while (front) {
            Node* tmp = front;
            front = front->next;
            delete tmp;
        }
        rear = nullptr;
    }

    void sort() {
        
        if (!front || !front->next) return;
        bool swapped;
        do {
            swapped = false;
            Node* curr = front;
            while (curr->next) {
                if (Comparator<T>::compare(curr->data, curr->next->data) > 0) {
                    swap(curr->data, curr->next->data);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
    }
};


template<typename T>
class DoublyCircularList {
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& val) : data(val), next(this), prev(this) {}
    };
    Node* head;
public:
    DoublyCircularList() : head(nullptr) {}
    ~DoublyCircularList() { clear(); }

    void add(const T& value) {
        Node* node = new Node(value);
        if (!head) {
            head = node;
        }
        else {
            Node* tail = head->prev;
            tail->next = node;
            node->prev = tail;
            node->next = head;
            head->prev = node;
        }
    }

    void input() {
        T value;
        cout << "Enter value: ";
        cin >> value;
        add(value);
    }

    bool search(const T& key) {
        if (!head) return false;
        Node* curr = head;
        do {
            if (Comparator<T>::compare(curr->data, key) == 0)
                return true;
            curr = curr->next;
        } while (curr != head);
        return false;
    }

    void remove(const T& key) {
        if (!head) return;
        Node* curr = head;
        do {
            if (Comparator<T>::compare(curr->data, key) == 0) {
                if (curr->next == curr) {
                    delete curr;
                    head = nullptr;
                    return;
                }
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                if (curr == head)
                    head = curr->next;
                Node* tmp = curr;
                curr = curr->next;
                delete tmp;
            }
            else {
                curr = curr->next;
            }
        } while (curr != head);
    }

    void print() {
        if (!head) { cout << "List empty\n"; return; }
        Node* curr = head;
        do {
            cout << curr->data << " ";
            curr = curr->next;
        } while (curr != head);
        cout << endl;
    }

    void save(const string& filename) {
        ofstream ofs(filename, ios::binary);
        if (!ofs) throw runtime_error("Cannot open file");
        if (!head) return;
        Node* curr = head;
        do {
            ofs.write((char*)&curr->data, sizeof(T));
            curr = curr->next;
        } while (curr != head);
    }

    void load(const string& filename) {
        clear();
        ifstream ifs(filename, ios::binary);
        if (!ifs) throw runtime_error("Cannot open file");
        T value;
        while (ifs.read((char*)&value, sizeof(T)))
            add(value);
    }

    void clear() {
        if (!head) return;
        Node* curr = head->next;
        while (curr != head) {
            Node* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
        delete head;
        head = nullptr;
    }

    void sort() {
        if (!head || head->next == head) return;
        bool swapped;
        do {
            swapped = false;
            Node* curr = head;
            do {
                Node* nextNode = curr->next;
                if (nextNode != head && Comparator<T>::compare(curr->data, nextNode->data) > 0) {
                    swap(curr->data, nextNode->data);
                    swapped = true;
                }
                curr = curr->next;
            } while (curr->next != head);
        } while (swapped);
    }
};