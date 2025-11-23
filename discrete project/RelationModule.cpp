#include "RelationModule.h"
#include <iostream>
using namespace std;

// Compose student-course and course-room into student-room
void RelationsModule::composeStudentCourseRoom(StudentCourse* sc, int scCount,CourseRoom* cr, int crCount,StudentRoom* out, int& outCount, int maxOut) {
    outCount = 0;
    for (int i = 0; i < scCount; i++) {
        for (int j = 0; j < crCount; j++) {
            if (sc[i].course == cr[j].course) {
                if (outCount >= maxOut) return;
                out[outCount].student = sc[i].student;
                out[outCount].room = cr[j].room;
                outCount++;
            }
        }
    }
}

// Compose faculty-course and course-room into faculty-room
void RelationsModule::composeFacultyCourseRoom(FacultyCourse* fc, int fcCount,CourseRoom* cr, int crCount,FacultyRoom* out, int& outCount, int maxOut) {
    outCount = 0;
    for (int i = 0; i < fcCount; i++) {
        for (int j = 0; j < crCount; j++) {
            if (fc[i].course == cr[j].course) {
                if (outCount >= maxOut) return;
                out[outCount].faculty = fc[i].faculty;
                out[outCount].room = cr[j].room;
                outCount++;
            }
        }
    }
}

// Detect student conflicts 
void RelationsModule::detectStudentConflict(StudentRoom* sr, int srCount) {
    for (int i = 0; i < srCount; i++) {
        for (int j = i + 1; j < srCount; j++) {
            if (sr[i].student == sr[j].student && sr[i].room == sr[j].room) {
                cout << "Conflict: Student " << sr[i].student->getName()<< " has two courses in room " << sr[i].room << endl;
            }
        }
    }
}

// Detect faculty conflicts
void RelationsModule::detectFacultyConflict(FacultyRoom* fr, int frCount) {
    for (int i = 0; i < frCount; i++) {
        for (int j = i + 1; j < frCount; j++) {
            if (fr[i].faculty == fr[j].faculty && fr[i].room == fr[j].room) {
                cout << "Conflict: Faculty " << fr[i].faculty<< " has two courses in room " << fr[i].room << endl;
            }
        }
    }
}

// Reflexive: every student appears with their own "name" course
bool RelationsModule::isReflexive(StudentCourse* sc, int scCount, Student** students, int studentCount) {
    for (int i = 0; i < studentCount; i++) {
        bool found = false;
        for (int j = 0; j < scCount; j++) {
            if (sc[j].student == students[i] && sc[j].course == students[i]->getName()) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

// Symmetric
bool RelationsModule::isSymmetric(StudentCourse* sc, int scCount) {
    for (int i = 0; i < scCount; i++) {
        bool found = false;
        for (int j = 0; j < scCount; j++) {
            if (sc[i].student->getName() == sc[j].course && sc[i].course == sc[j].student->getName()) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

// Transitive
bool RelationsModule::isTransitive(StudentCourse* sc, int scCount) {
    for (int i = 0; i < scCount; i++) {
        for (int j = 0; j < scCount; j++) {
            if (sc[i].course == sc[j].student->getName()) {
                bool found = false;
                for (int k = 0; k < scCount; k++) {
                    if (sc[k].student == sc[i].student && sc[k].course == sc[j].course) {
                        found = true;
                        break;
                    }
                }
                if (!found) return false;
            }
        }
    }
    return true;
}

// Equivalence: reflexive + symmetric + transitive
bool RelationsModule::isEquivalence(StudentCourse* sc, int scCount, Student** students, int studentCount) {
    return isReflexive(sc, scCount, students, studentCount) &&
           isSymmetric(sc, scCount) &&
           isTransitive(sc, scCount);
}

// Partial order: reflexive + antisymmetric + transitive
bool RelationsModule::isPartialOrder(StudentCourse* sc, int scCount, Student** students, int studentCount) {
    // Check antisymmetry
    for (int i = 0; i < scCount; i++) {
        for (int j = 0; j < scCount; j++) {
            if (i == j) continue;
            if (sc[i].student->getName() == sc[j].course && sc[i].course == sc[j].student->getName()) {
                if (sc[i].student != sc[j].student) return false;
            }
        }
    }
    // Check reflexive and transitive properties
    return isReflexive(sc, scCount, students, studentCount) && isTransitive(sc, scCount);
}

