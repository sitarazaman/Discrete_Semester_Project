#pragma once
#pragma once
#ifndef PROOF_ENGINE_H
#define PROOF_ENGINE_H

#include <string>
#include <iostream>
#include "course.h"   
using namespace std;

class ProofEngine {
public:
    ProofEngine();
    ~ProofEngine();

    bool provePrerequisiteChain(const string& course, const string courses[], const string prereqs[], int courseCount);

    bool proveStudentPrereqsForCourse(const string& studentName, string* completedCourses, int completedCount, const string& targetCourse, CourseSchedule& cs);

    void proveTransitivity(const string& A, const string& B, const string& C);

    void proveCompositionStudentToRoom(const string students[], const string studentCourse[], int studentCount,
        const string courses[], const string courseFaculty[], int courseCount,
        const string faculties[], const string facultyRoom[], int facultyCount);
};

#endif
