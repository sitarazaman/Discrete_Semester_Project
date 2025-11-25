#pragma once
#include <string>
using namespace std;

class Student {
private:
    string name;
    int studentId;
    int capacity;
    int completedCount;
    string* completedCourses;

public:
    Student(string n, int id, int cap = 5);
    ~Student();

    void completeCourse(string course);
    bool hasCompleted(string course);
    string getName();
    string* getCompletedCourses();
    int getCompletedCount();
};
