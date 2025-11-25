#include "Student.h"
#include <iostream>
using namespace std;

Student::Student(string n, int id, int cap) {
    name = n;
    studentId = id;
    if (cap <= 0) cap = 5;
    capacity = cap;
    completedCount = 0;
    completedCourses = new string[capacity];
}

Student::~Student() {
    delete[] completedCourses; // safe delete, no need for nullptr check
}

// --- Add a course safely ---
void Student::completeCourse(string course) {
    if (completedCount >= capacity) {
        capacity *= 2;
        string* newArray = new string[capacity];
        for (int i = 0; i < completedCount; i++)
            newArray[i] = completedCourses[i];
        delete[] completedCourses;
        completedCourses = newArray;
    }
    completedCourses[completedCount++] = course;
}

bool Student::hasCompleted(string course) {
    for (int i = 0; i < completedCount; i++)
        if (completedCourses[i] == course)
            return true;
    return false;
}

string Student::getName() { return name; }
string* Student::getCompletedCourses() { return completedCourses; }
int Student::getCompletedCount() { return completedCount; }
