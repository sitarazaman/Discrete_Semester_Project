#include"Benchmark.h"
#include<iostream>
using namespace std;

Benchmark::Benchmark(StudentGroup* group,
                     CourseSchedule* schedule,
                     LogicEngine* engine)
{
    sg = group;
    cs = schedule;
    le = engine;
}

long long Benchmark::measureCourseOrdering() {
    long long ops = 0;

    cs->generateOrder();
    ops += 1000;

    return ops;
}

long long Benchmark::measureStudentChecking() {
    long long ops = 0;

    Student** list = sg->getAllStudents();
    int count = sg->getStudentCount();

    for (int i = 0; i < count; i++) {
        ops++;

        Student* s = list[i];
        string* done = s->getCompletedCourses();
        int dc = s->getCompletedCount();

        for (int j = 0; j < dc; j++) {
            ops++;
            cs->isPrerequisiteChainSatisfied(done[j]);
        }
    }

    return ops;
}

long long Benchmark::measureLogicRules() {
    long long ops = 0;

    string c = "CS101";
    string p = "Adeel";
    string lab = "LabA";

    bool ok = le->checkConsistency(c, p, lab);
    ops++;

    return ops;
}

long long Benchmark::measureGroupValidation() {
    long long ops = 0;

    Student** list = sg->getAllStudents();
    int count = sg->getStudentCount();

    for (int i = 0; i < count; i++) {
        ops++;

        for (int j = i + 1; j < count; j++) {
            ops++;

            if (list[i] == list[j]) {
                ops++;
            }
        }
    }

    return ops;
}

void Benchmark::runAllBenchmarks() {
    cout << endl;
    cout << "===== BENCHMARK RESULTS =====" << endl;

    long long t1 = measureCourseOrdering();
    cout << "Course Ordering Operations: " << t1 << endl;

    long long t2 = measureStudentChecking();
    cout << "Student Check Operations: " << t2 << endl;

    long long t3 = measureLogicRules();
    cout << "Logic Rule Operations: " << t3 << endl;

    long long t4 = measureGroupValidation();
    cout << "Group Validation Operations: " << t4 << endl;

    cout << "===== END OF BENCHMARK =====" << endl;
    cout << endl;
}
