#ifndef RELATIONMODULE_H
#define RELATIONMODULE_H

#include "student.h"
#include <iostream>
#include <string>
using namespace std;
struct StudentCourse {
    Student* student;
    string course;
};

struct FacultyCourse {
    string faculty;
    string course;
};

struct CourseRoom {
    string course;
    string room;
};

struct StudentRoom {
    Student* student;
    string room;
};

struct FacultyRoom {
    string faculty;
    string room;
};

class RelationsModule {
public:
    // Compose relations
    void composeStudentCourseRoom(StudentCourse* sc, int scCount,CourseRoom* cr, int crCount,StudentRoom* out, int& outCount, int maxOut);

    void composeFacultyCourseRoom(FacultyCourse* fc, int fcCount,CourseRoom* cr, int crCount,FacultyRoom* out, int& outCount, int maxOut);

    // Detect conflicts
    void detectStudentConflict(StudentRoom* sr, int srCount);
    void detectFacultyConflict(FacultyRoom* fr, int frCount);

    // Relation properties
    bool isReflexive(StudentCourse* sc, int scCount, Student** students, int studentCount);
    bool isSymmetric(StudentCourse* sc, int scCount);
    bool isTransitive(StudentCourse* sc, int scCount);
    bool isEquivalence(StudentCourse* sc, int scCount, Student** students, int studentCount);
    bool isPartialOrder(StudentCourse* sc, int scCount, Student** students, int studentCount);
};

#endif
