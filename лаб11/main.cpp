#include "DataStructures.h"
#include <string>

int main() {
    try {
        Stack<int> intStack;
        Queue<float> floatQueue;
        DoublyCircularList<string> stringList;

        intStack.push(5);
        intStack.push(10);
        intStack.print();
        intStack.sort();
        intStack.print();

        floatQueue.enqueue(1.5f);
        floatQueue.enqueue(2.7f);
        floatQueue.print();
        floatQueue.sort();
        floatQueue.print();

        stringList.add("Привіт");
        stringList.add("Пока");
        stringList.print();
        stringList.sort();
        stringList.print();

        cout << "Searching 10 in stack: " << intStack.search(10) << endl;
        intStack.remove(10);
        intStack.print();

        intStack.save("stack.bin");
        intStack.clear();
        intStack.load("stack.bin");
        intStack.print();

    }
    catch (const exception& ex) {
        cerr << "Exception: " << ex.what() << endl;
    }
    return 0;
}