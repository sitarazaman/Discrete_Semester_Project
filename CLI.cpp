#include "CLI.h"
#include <iostream>
using namespace std;

CLI::CLI(StudentGroup* group,
         CourseSchedule* schedule,
         LogicEngine* engine,
         ConsistencyChecker* checker,
         Benchmark* bench)
{
    sg = group;
    cs = schedule;
    le = engine;
    cc = checker;
    bm = bench;
}

void CLI::showMenu() {
    cout << endl;
    cout << "===== MAIN MENU =====" << endl;
    cout << "1. Add New Student" << endl;
    cout << "2. Assign Course To Student" << endl;
    cout << "3. Show All Valid Course Orders" << endl;
    cout << "4. Run Consistency Checker" << endl;
    cout << "5. Run Benchmark Tests" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter choice: ";
}

void CLI::run() {
    int ch = -1;

    while (ch != 0) {
        showMenu();
        cin >> ch;

        if (ch == 1) {
            addStudent();
        }
        else if (ch == 2) {
            assignCourseToStudent();
        }
        else if (ch == 3) {
            printCourseOrder();
        }
        else if (ch == 4) {
            runConsistencyChecks();
        }
        else if (ch == 5) {
            runBenchmarks();
        }
        else if (ch == 0) {
            cout << "Exiting program." << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
}

void CLI::addStudent() {
    cout << endl;

    string name;
    cout << "Enter student name: ";
    cin >> name;

    static int nextId = 0;
    Student* s = new Student(name, nextId);
    nextId++;

    sg->addStudent(s);

    cout << "Student added." << endl;
}

void CLI::assignCourseToStudent() {
    cout << endl;

    int count = sg->getStudentCount();
    if (count == 0) {
        cout << "No students available." << endl;
        return;
    }

    cout << "Select student index (0 to " << count - 1 << "): ";
    int idx;
    cin >> idx;

    if (idx < 0 || idx >= count) {
        cout << "Invalid index." << endl;
        return;
    }

    Student** list = sg->getAllStudents();
    Student* s = list[idx];

    string course;
    cout << "Enter course name: ";
    cin >> course;

    sg->assignCourse(s, course, *cs);
}

void CLI::printCourseOrder() {
    cout << endl;
    cs->generateOrder();
}

void CLI::runConsistencyChecks() {
    cout << endl;
    cc->runAllChecks();
}

void CLI::runBenchmarks() {
    cout << endl;
    bm->runAllBenchmarks();
}
