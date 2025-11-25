#pragma once
#include <string>
using namespace std;

class SetOperationsString {
private:
    string* arr;
    int size;
    int capacity;

public:
    SetOperationsString(int cap = 20);
    ~SetOperationsString();

    void add(const string& s);
    bool contains(const string& s) const;

    SetOperationsString unionWith(const SetOperationsString& other) const;
    SetOperationsString intersectionWith(const SetOperationsString& other) const;
    SetOperationsString differenceWith(const SetOperationsString& other) const;

    void print() const;
};
