#include"ConsistencyChecker.h"
#include<iostream>
using namespace std;

ConsistencyChecker::ConsistencyChecker(StudentGroup* group,
                                       CourseSchedule* schedule,
                                       LogicEngine* engine)
{
    sg = group;
    cs = schedule;
    le = engine;
}

void ConsistencyChecker::runAllChecks() {
    cout << endl;
    cout << "===== CONSISTENCY CHECK REPORT =====" << endl;

    checkCourseStructure();
    checkStudentPrerequisites();
    checkStudentLoad();
    checkLogicConsistency();
    checkGroupValidity();

    cout << "===== END OF REPORT =====" << endl;
    cout << endl;
}

void ConsistencyChecker::checkStudentPrerequisites() {
    cout << endl;
    cout << "--- Checking Student Prerequisite Consistency ---" << endl;

    Student** list = sg->getAllStudents();
    int count = sg->getStudentCount();

    for (int i = 0; i < count; i++) {
        Student* s = list[i];
        string* completed = s->getCompletedCourses();
        int completedCount = s->getCompletedCount();

        for (int j = 0; j < completedCount; j++) {
            string course = completed[j];

            bool ok = cs->isPrerequisiteChainSatisfied(course);

            if (!ok) {
                cout << "[Warning] Student " << s->getName()
                     << " has inconsistency in prerequisite chain for course "
                     << course << endl;
            }
        }
    }
}

void ConsistencyChecker::checkCourseStructure() {
    cout << endl;
    cout << "--- Checking Course Structure Consistency ---" << endl;

    cs->generateOrder();
}

void ConsistencyChecker::checkStudentLoad(int maxCourses) {
    cout << endl;
    cout << "--- Checking Student Load ---" << endl;

    Student** list = sg->getAllStudents();
    int count = sg->getStudentCount();

    for (int i = 0; i < count; i++) {
        Student* s = list[i];
        int c = s->getCompletedCount();

        if (c > maxCourses) {
            cout << "[Alert] " << s->getName()
                 << " is taking " << c
                 << " courses (limit = " << maxCourses << ")" << endl;
        }
    }
}

void ConsistencyChecker::checkLogicConsistency() {
    cout << endl;
    cout << "--- Checking Logic Engine Rule Consistency ---" << endl;

    string testCourse = "CS101";
    string testProf = "Adeel";
    string testLab = "LabA";

    bool ok = le->checkConsistency(testCourse, testProf, testLab);

    if (!ok) {
        cout << "[Conflict] Logic rule violated for test allocation." << endl;
    }
    else {
        cout << "Logic rules OK for the tested allocation." << endl;
    }
}

void ConsistencyChecker::checkGroupValidity() {
    cout << endl;
    cout << "--- Checking Group Integrity ---" << endl;

    Student** list = sg->getAllStudents();
    int count = sg->getStudentCount();

    if (count == 0) {
        cout << "[Error] No students found in StudentGroup." << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (list[i] == list[j]) {
                cout << "[Error] Duplicate student object detected." << endl;
            }
        }
    }

    cout << "Group integrity OK." << endl;
}
