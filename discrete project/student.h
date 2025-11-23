#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class Student {
private:
    string name;
    int studentId;
    string* completedCourses;
    int completedCount;
    int capacity;

public:
    Student(string n,int id, int cap = 10);
    ~Student();

    void completeCourse(string course);
    bool hasCompleted(string course);
    string getName();
    string* getCompletedCourses();
    int getCompletedCount();
};

#endif
