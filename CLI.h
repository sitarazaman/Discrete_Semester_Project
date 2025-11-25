#ifndef CLI_H
#define CLI_H

#include"StudentGroup.h"
#include"course.h"
#include"logic_engine.h"
#include"ConsistencyChecker.h"
#include"Benchmark.h"
using namespace std;

class CLI {
private:
    StudentGroup* sg;
    CourseSchedule* cs;
    LogicEngine* le;
    ConsistencyChecker* cc;
    Benchmark* bm;

public:
    CLI(StudentGroup* group,
        CourseSchedule* schedule,
        LogicEngine* engine,
        ConsistencyChecker* checker,
        Benchmark* bench);

    void showMenu();
    void run();

    void addStudent();
    void assignCourseToStudent();
    void printCourseOrder();
    void runConsistencyChecks();
    void runBenchmarks();
};

#endif
