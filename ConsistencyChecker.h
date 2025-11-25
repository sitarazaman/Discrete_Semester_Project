#ifndef CONSISTENCY_CHECKER_H
#define CONSISTENCY_CHECKER_H

#include"StudentGroup.h"
#include"course.h"
#include"logic_engine.h"
#include<string>
using namespace std;

class ConsistencyChecker {
private:
    StudentGroup* sg;
    CourseSchedule* cs;
    LogicEngine* le;

public:
    ConsistencyChecker(StudentGroup* group,
                       CourseSchedule* schedule,
                       LogicEngine* engine);

    void runAllChecks();

    void checkStudentPrerequisites();
    void checkCourseStructure();
    void checkStudentLoad(int maxCourses = 6);
    void checkLogicConsistency();
    void checkGroupValidity();
};

#endif
