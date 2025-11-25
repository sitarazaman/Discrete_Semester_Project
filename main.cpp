

#include "course.h"
#include "student.h"
#include "StudentGroup.h"
#include "logic_engine.h"
#include "setOperations.h"
#include "setOperationsH.h"
#include "RelationModule.h"
#include "ConsistencyChecker.h"
#include "Benchmark.h"
#include "CLI.h"
#include "Tests.h"
#include "function.h"
#include "proof_engine.h"
#include <iostream>
using namespace std;

int main() {
    CourseSchedule cs;
    cs.addCourse("CS101", "");
    cs.addCourse("CS102", "CS101");
    cs.addCourse("CS103", "CS102");
    cs.addCourse("Math101", "");

    StudentGroup sg;
    LogicEngine engine;
    ConsistencyChecker checker(&sg, &cs, &engine);
    Benchmark bench(&sg, &cs, &engine);
    CLI cli(&sg, &cs, &engine, &checker, &bench);
    Tests tests;

    engine.addRule("CS101", "Adeel", "LabA");
    engine.addRule("CS102", "DrKhan", "LabC");

    int choice = 0;
    int nextId = 0;

    do {
        cout << "\n===== MAIN MENU =====" << endl;
        cout << "1. Show Course Schedule" << endl;
        cout << "2. Add Students & Assign Courses" << endl;
        cout << "3. Generate Student Groups" << endl;
        cout << "4. Logic Engine Operations" << endl;
        cout << "5. Set Operations Demo" << endl;
        cout << "6. Relations & Functions Modules" << endl;
        cout << "7. Run Consistency, Benchmark & Tests" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "All valid course sequences:" << endl;
            cs.generateOrder();
            break;
        }

        case 2: {
            int n;
            cout << "Enter number of students: ";
            cin >> n;

            for (int i = 0; i < n; i++) {
                string name;
                cout << "Enter name of student " << i + 1 << ": ";
                cin >> name;

                Student* s = new Student(name, nextId++);
                sg.addStudent(s);

                int m;
                cout << "How many courses " << name << " wants to take? ";
                cin >> m;

                for (int j = 0; j < m; j++) {
                    string course;
                    cout << "Enter course " << j + 1 << ": ";
                    cin >> course;
                    sg.assignCourse(s, course, cs);
                }
            }
            break;
        }

        case 3: {
            int groupSize;
            cout << "Enter group size to generate: ";
            cin >> groupSize;
            cout << "Student groups of size " << groupSize << ":" << endl;
            sg.generateGroups(groupSize);
            break;
        }

        case 4: {
            cout << "Logic Engine Rules:" << endl;
            engine.printRules();

            string course, prof, lab;
            cout << "Enter course to check: ";
            cin >> course;
            cout << "Enter professor: ";
            cin >> prof;
            cout << "Enter lab: ";
            cin >> lab;

            if (engine.checkConsistency(course, prof, lab))
                cout << "Allocation valid." << endl;
            else
                cout << "Allocation rejected." << endl;
            break;
        }

        case 5: {
            SetOperationsStudent csStudents, mathStudents;
            Student** list = sg.getAllStudents();
            int count = sg.getStudentCount();

            for (int i = 0; i < count; i++) {
                Student* s = list[i];
                if (sg.isEnrolledIn(s, "CS101"))
                    csStudents.add(s);
                if (sg.isEnrolledIn(s, "Math101"))
                    mathStudents.add(s);
            }

            cout << "CS Students: "; csStudents.print();
            cout << "Math Students: "; mathStudents.print();

            cout << "Union: "; csStudents.unionWith(mathStudents).print();
            cout << "Intersection: "; csStudents.intersectionWith(mathStudents).print();
            cout << "Difference: "; csStudents.differenceWith(mathStudents).print();

            cout << "\nPower Set of CS Students:" << endl;
            csStudents.printPowerSet();

            cout << "\nIs CS Students subset of Math Students? ";
            cout << (csStudents.isSubsetOf(mathStudents) ? "Yes" : "No") << endl;

            break;
        }

        case 6: {
            // ---------------- MODULE 6: RELATIONS & FUNCTIONS ----------------
            Student** list = sg.getAllStudents();
            int count = sg.getStudentCount();

            StudentCourse sc[50];
            int scCount = 0;
            for (int i = 0; i < count; i++) {
                Student* s = list[i];
                for (int j = 0; j < s->getCompletedCount(); j++) {
                    sc[scCount].student = s;
                    sc[scCount].course = s->getCompletedCourses()[j];
                    scCount++;
                }
            }

            FacultyCourse fc[50];
            int fcCount = 0;
            for (int i = 0; i < engine.getRuleCount(); i++) {
                fc[fcCount].faculty = engine.getRule(i).conditionProfessor;
                fc[fcCount].course = engine.getRule(i).conditionCourse;
                fcCount++;
            }

            CourseRoom cr[50];
            int crCount = 0;
            for (int i = 0; i < engine.getRuleCount(); i++) {
                cr[crCount].course = engine.getRule(i).conditionCourse;
                cr[crCount].room = engine.getRule(i).enforcedLab;
                crCount++;
            }

            RelationsModule relModule;
            StudentRoom sr[50];
            int srCount;
            relModule.composeStudentCourseRoom(sc, scCount, cr, crCount, sr, srCount, 50);

            // Faculty-Course-Room composition
            FacultyRoom fr[50];
            int frCount;
            relModule.composeFacultyCourseRoom(fc, fcCount, cr, crCount, fr, frCount, 50);

            relModule.detectStudentConflict(sr, srCount);
            relModule.detectFacultyConflict(fr, frCount);

            cout << "\nRelation checks:" << endl;
            if (relModule.isReflexive(sc, scCount, list, count))
                cout << "Student-Course is reflexive\n";
            if (relModule.isSymmetric(sc, scCount))
                cout << "Student-Course is symmetric\n";
            if (relModule.isTransitive(sc, scCount))
                cout << "Student-Course is transitive\n";
            if (relModule.isEquivalence(sc, scCount, list, count))
                cout << "Student-Course is equivalence\n";
            if (relModule.isPartialOrder(sc, scCount, list, count))
                cout << "Student-Course is partial order\n";

            // Functions Module
            const int MAX_C = 50;
            string allCourses[MAX_C], allPrereqs[MAX_C];
            int allCourseCount = 0;

            for (int i = 0; i < cs.getCourseCount(); i++) {
                allCourses[allCourseCount] = cs.getCourseName(i);
                allPrereqs[allCourseCount] = cs.getCoursePrerequisite(i);
                allCourseCount++;
            }

            FunctionsModule fm;
            for (int i = 0; i < count; i++) {
                string courseForStudent;
                cout << "Assign a course to student " << list[i]->getName() << ": ";
                cin >> courseForStudent;
                fm.addStudentCourse(list[i]->getName(), courseForStudent);
            }

            fm.addCourseFaculty("CS101", "Adeel");
            fm.addCourseFaculty("CS102", "DrKhan");
            fm.addCourseFaculty("CS103", "DrKhan");
            fm.addCourseFaculty("Math101", "Zara");

            fm.addFacultyRoom("Adeel", "LabA");
            fm.addFacultyRoom("DrKhan", "LabC");
            fm.addFacultyRoom("Zara", "LabB");

            cout << "\n=== Functions Module Reports ===" << endl;
            fm.printStudentCourseMappings();
            fm.printCourseFacultyMappings();
            fm.printFacultyRoomMappings();
            cout << "Dry-run: Every course assigned to exactly one faculty? "
                << (fm.isInjectiveCourseToFaculty() ? "Yes" : "No") << endl;

            const int MAX_OUT = 200;
            string outStudents[MAX_OUT], outRooms[MAX_OUT];
            int outCount = fm.composeStudentToRoom(outStudents, outRooms, MAX_OUT);

            cout << "--- Composition Student -> Room ---" << endl;
            for (int i = 0; i < outCount; i++) {
                cout << outStudents[i] << " -> ";
                if (outRooms[i] == "") cout << "[no room assigned]" << endl;
                else cout << outRooms[i] << endl;
            }

            fm.printInverseCourseToStudents();
            fm.printInverseFacultyToCourses();

            ProofEngine prover;
            prover.provePrerequisiteChain("CS103", allCourses, allPrereqs, allCourseCount);

            if (count > 0) {
                Student* first = list[0];
                prover.proveStudentPrereqsForCourse(first->getName(),
                    first->getCompletedCourses(),
                    first->getCompletedCount(),
                    "CS102", cs);
            }

            prover.proveTransitivity("CS103", "CS102", "CS101");
            prover.proveCompositionStudentToRoom(outStudents, outRooms, outCount,
                allCourses, allPrereqs, allCourseCount,
                allCourses, allPrereqs, allCourseCount);

            cout << "Relations & Functions demo completed.\n";
            break;
        }

        case 7: {
            checker.runAllChecks();
            bench.runAllBenchmarks();
            tests.runAllTests();
            break;
        }

        case 0: {
            cout << "Exiting program.\n";
            break;
        }

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}

