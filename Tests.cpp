#include"Tests.h"
#include<iostream>
using namespace std;

Tests::Tests() {
}

bool Tests::testCoursePrerequisite() {
    CourseSchedule cs;
    cs.addCourse("A", "");
    cs.addCourse("B", "A");

    bool ok1 = cs.isPrerequisiteChainSatisfied("B");
    bool ok2 = cs.isPrerequisiteChainSatisfied("A");

    if (!ok1) {
        return false;
    }
    if (!ok2) {
        return false;
    }
    return true;
}

bool Tests::testStudentAdd() {
    StudentGroup sg;
    Student* s1 = new Student("Ali", 1);
    sg.addStudent(s1);

    if (sg.getStudentCount() != 1) {
        return false;
    }

    Student** list = sg.getAllStudents();
    if (list[0] != s1) {
        return false;
    }

    return true;
}

bool Tests::testAssignCourse() {
    CourseSchedule cs;
    cs.addCourse("C1", "");
    cs.addCourse("C2", "C1");

    Student* s = new Student("Sara", 2);
    StudentGroup sg;

    sg.addStudent(s);
    sg.assignCourse(s, "C1", cs);
    sg.assignCourse(s, "C2", cs);

    if (s->getCompletedCount() != 2) {
        return false;
    }
    return true;
}

bool Tests::testLogicRule() {
    LogicEngine le;
    le.addRule("CS101", "Adeel", "LabA");

    bool ok = le.checkConsistency("CS101", "Adeel", "LabA");

    if (!ok) {
        return false;
    }
    return true;
}

bool Tests::testGroupDuplicateCheck() {
    StudentGroup sg;

    Student* s1 = new Student("A", 1);
    Student* s2 = new Student("B", 2);  // ? new object, alag pointer

    sg.addStudent(s1);
    sg.addStudent(s2);

    if (sg.getStudentCount() != 2) {
        return false;
    }
    return true;
}


void Tests::runAllTests() {
    cout << endl;
    cout << "===== UNIT TEST RESULTS =====" << endl;

    cout << "Course Prerequisite Test: ";
    if (testCoursePrerequisite()) {
        cout << "PASS" << endl;
    } 
    else {
        cout << "FAIL" << endl;
    }

    cout << "Student Add Test: ";
    if (testStudentAdd()) {
        cout << "PASS" << endl;
    } 
    else {
        cout << "FAIL" << endl;
    }

    cout << "Course Assignment Test: ";
    if (testAssignCourse()) {
        cout << "PASS" << endl;
    } 
    else {
        cout << "FAIL" << endl;
    }

    cout << "Logic Rule Test: ";
    if (testLogicRule()) {
        cout << "PASS" << endl;
    } 
    else {
        cout << "FAIL" << endl;
    }

    cout << "Group Duplicate Test: ";
    if (testGroupDuplicateCheck()) {
        cout << "PASS" << endl;
    } 
    else {
        cout << "FAIL" << endl;
    }

    cout << "===== END OF UNIT TESTS =====" << endl;
    cout << endl;
}
