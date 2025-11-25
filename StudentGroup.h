#pragma once
#include "Student.h"
#include "course.h"

class StudentGroup {
private:
    Student** students;
    int capacity;
    int totalStudents;

    void generateGroupsRecursive(Student** group, int index, int start, int groupSize);

public:
    StudentGroup(int cap = 5);
    ~StudentGroup();

    void addStudent(Student* s);
    void assignCourse(Student* s, string course, CourseSchedule& cs);
    void generateGroups(int groupSize);

    Student** getAllStudents() const;
    int getStudentCount() const;
    bool isEnrolledIn(Student* s, const string& courseName) const;
};
