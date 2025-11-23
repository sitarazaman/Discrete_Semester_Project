#pragma once
#include "student.h"

class SetOperationsStudent {
private:
    Student** arr;
    int size;
    int capacity;

public:
    SetOperationsStudent(int cap = 20);
    ~SetOperationsStudent();

    void add(Student* s);
    bool contains(Student* s) const;

    SetOperationsStudent unionWith(const SetOperationsStudent& other) const;
    SetOperationsStudent intersectionWith(const SetOperationsStudent& other) const;
    SetOperationsStudent differenceWith(const SetOperationsStudent& other) const;

    void print() const;
    void printPowerSet() const;
    bool isSubsetOf(const SetOperationsStudent& other);
    void powerSetRec(int index, Student** subset, int subsetSize) const;
};
