#include "setOperations.h"
#include <iostream>
using namespace std;

SetOperationsStudent::SetOperationsStudent(int cap) {
    capacity = cap;
    size = 0;
    arr = new Student * [capacity];
}

SetOperationsStudent::~SetOperationsStudent() {
    delete[] arr;
}

void SetOperationsStudent::add(Student* s) {
    if (contains(s)) return;
    if (size == capacity) {
        capacity *= 2;
        Student** newArr = new Student * [capacity];
        for (int i = 0; i < size; i++) newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
    }
    arr[size++] = s;
}

bool SetOperationsStudent::contains(Student* s) const {
    for (int i = 0; i < size; i++)
        if (arr[i] == s) return true;
    return false;
}

SetOperationsStudent SetOperationsStudent::unionWith(const SetOperationsStudent& other) const {
    SetOperationsStudent result(size + other.size);
    for (int i = 0; i < size; i++) result.add(arr[i]);
    for (int i = 0; i < other.size; i++) result.add(other.arr[i]);
    return result;
}

SetOperationsStudent SetOperationsStudent::intersectionWith(const SetOperationsStudent& other) const {
    SetOperationsStudent result(size);
    for (int i = 0; i < size; i++)
        if (other.contains(arr[i])) result.add(arr[i]);
    return result;
}

SetOperationsStudent SetOperationsStudent::differenceWith(const SetOperationsStudent& other) const {
    SetOperationsStudent result(size);
    for (int i = 0; i < size; i++)
        if (!other.contains(arr[i])) result.add(arr[i]);
    return result;
}

void SetOperationsStudent::print() const {
    cout << "{ ";
    for (int i = 0; i < size; i++)
        cout << arr[i]->getName() << " ";
    cout << "}" << endl;
}

void SetOperationsStudent::printPowerSet() const {
    Student** subset = new Student * [size];
    powerSetRec(0, subset, 0);
    delete[] subset;
}

void SetOperationsStudent::powerSetRec(int index, Student** subset, int subsetSize) const {
    if (index == size) {
        cout << "{ ";
        for (int i = 0; i < subsetSize; i++)
            cout << subset[i]->getName() << " ";
        cout << "}" << endl;
        return;
    }
    subset[subsetSize] = arr[index];
    powerSetRec(index + 1, subset, subsetSize + 1);
    powerSetRec(index + 1, subset, subsetSize);
}
bool SetOperationsStudent::isSubsetOf(const SetOperationsStudent& other) {
    for (int i = 0; i < size; i++) {
        if (!other.contains(arr[i]))
            return false;
    }
    return true;
}
