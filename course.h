#pragma once
#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;

class CourseSchedule {
private:
    string* courses;    // Array of course names
    string* prereq;     // Array of prerequisites
    int total;          // Current number of courses
    int capacity;       // Maximum courses array can hold

    void generateOrderRecursive(string* done, int doneCount);

public:
    CourseSchedule(int cap = 10);
    ~CourseSchedule();

    void addCourse(string courseName, string prerequisite);
    void generateOrder();
    bool isPrerequisiteChainSatisfied(string course);
    bool isPrerequisiteSatisfiedForStudent(string course, string* completedCourses, int completedCount);

  
    string getCourseName(int index) const;
    string getCoursePrerequisite(int index) const;
    int getCourseCount() const;
};

#endif
