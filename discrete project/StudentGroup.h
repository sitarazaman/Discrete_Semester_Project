#pragma once
#ifndef STUDENTGROUP_H
#define STUDENTGROUP_H

#include <string>
#include "student.h"
#include "course.h"
using namespace std;

class StudentGroup {
private:
    Student** students;
    int totalStudents;
    int capacity;
    void generateGroupsRecursive(Student** group, int index, int start, int groupSize);

public:
    StudentGroup(int cap = 10);
    ~StudentGroup();

    void addStudent(Student* s);
    void assignCourse(Student* s, string course, CourseSchedule& cs);
    void generateGroups(int groupSize);
   
    Student** getStudents() { return students; }
    int getTotalStudents() { return totalStudents; }

    Student** getAllStudents() const;
    int getStudentCount() const;
    bool isEnrolledIn(Student* s, const string& courseName) const;


};

#endif
