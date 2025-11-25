#ifndef BENCHMARK_H
#define BENCHMARK_H

#include"StudentGroup.h"
#include"course.h"
#include"logic_engine.h"
using namespace std;

class Benchmark {
private:
    StudentGroup* sg;
    CourseSchedule* cs;
    LogicEngine* le;

public:
    Benchmark(StudentGroup* group,
              CourseSchedule* schedule,
              LogicEngine* engine);

    long long measureCourseOrdering();
    long long measureStudentChecking();
    long long measureLogicRules();
    long long measureGroupValidation();

    void runAllBenchmarks();
};

#endif
