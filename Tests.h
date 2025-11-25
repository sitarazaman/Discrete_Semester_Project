#ifndef TESTS_H
#define TESTS_H

#include"course.h"
#include"Student.h"
#include"StudentGroup.h"
#include"logic_engine.h"
#include"ConsistencyChecker.h"
using namespace std;

class Tests {
public:
    Tests();

    bool testCoursePrerequisite();
    bool testStudentAdd();
    bool testAssignCourse();
    bool testLogicRule();
    bool testGroupDuplicateCheck();

    void runAllTests();
};

#endif
