#include "setOperationsH.h"
#include <iostream>
using namespace std;

SetOperationsString::SetOperationsString(int cap) {
    capacity = cap;
    size = 0;
    arr = new string[capacity];
}

SetOperationsString::~SetOperationsString() {
    delete[] arr;
}

void SetOperationsString::add(const string& s) {
    if (contains(s)) return;
    if (size == capacity) {
        capacity *= 2;
        string* newArr = new string[capacity];
        for (int i = 0; i < size; i++) newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
    }
    arr[size++] = s;
}

bool SetOperationsString::contains(const string& s) const {
    for (int i = 0; i < size; i++)
        if (arr[i] == s) return true;
    return false;
}

SetOperationsString SetOperationsString::unionWith(const SetOperationsString& other) const {
    SetOperationsString result(size + other.size);
    for (int i = 0; i < size; i++) result.add(arr[i]);
    for (int i = 0; i < other.size; i++) result.add(other.arr[i]);
    return result;
}

SetOperationsString SetOperationsString::intersectionWith(const SetOperationsString& other) const {
    SetOperationsString result(size);
    for (int i = 0; i < size; i++)
        if (other.contains(arr[i])) result.add(arr[i]);
    return result;
}

SetOperationsString SetOperationsString::differenceWith(const SetOperationsString& other) const {
    SetOperationsString result(size);
    for (int i = 0; i < size; i++)
        if (!other.contains(arr[i])) result.add(arr[i]);
    return result;
}

void SetOperationsString::print() const {
    cout << "{ ";
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << "}" << endl;
}
