#include "StudentGroup.h"
#include <iostream>
using namespace std;

StudentGroup::StudentGroup(int cap) {
    if (cap <= 0) cap = 5;
    capacity = cap;
    totalStudents = 0;
    students = new Student * [capacity];
    for (int i = 0; i < capacity; i++)
        students[i] = nullptr; // initialize
}

StudentGroup::~StudentGroup() {
    for (int i = 0; i < totalStudents; i++) {
        if (students[i] != nullptr)
            delete students[i]; // safe delete
    }
    delete[] students;
}

void StudentGroup::addStudent(Student* s) {
    // check duplicate pointers
    for (int i = 0; i < totalStudents; i++)
        if (students[i] == s)
            return; // ignore duplicate

    if (totalStudents == capacity) {
        int newCapacity = capacity * 2;
        Student** newArray = new Student * [newCapacity];
        for (int i = 0; i < totalStudents; i++)
            newArray[i] = students[i];
        for (int i = totalStudents; i < newCapacity; i++)
            newArray[i] = nullptr;
        delete[] students;
        students = newArray;
        capacity = newCapacity;
    }

    students[totalStudents++] = s;
}

void StudentGroup::assignCourse(Student* s, string course, CourseSchedule& cs) {
    if (cs.isPrerequisiteSatisfiedForStudent(course, s->getCompletedCourses(), s->getCompletedCount())) {
        cout << s->getName() << " can take " << course << endl;
        s->completeCourse(course);
    }
    else {
        cout << s->getName() << " cannot take " << course << " yet (prerequisites not completed)." << endl;
    }
}

void StudentGroup::generateGroups(int groupSize) {
    if (groupSize <= 0 || groupSize > totalStudents) {
        cout << "Invalid group size." << endl;
        return;
    }
    Student** group = new Student * [groupSize];
    generateGroupsRecursive(group, 0, 0, groupSize);
    delete[] group;
}

void StudentGroup::generateGroupsRecursive(Student** group, int index, int start, int groupSize) {
    if (index == groupSize) {
        for (int i = 0; i < groupSize; i++)
            cout << group[i]->getName() << " ";
        cout << endl;
        return;
    }
    for (int i = start; i < totalStudents; i++) {
        group[index] = students[i];
        generateGroupsRecursive(group, index + 1, i + 1, groupSize);
    }
}

Student** StudentGroup::getAllStudents() const { return students; }
int StudentGroup::getStudentCount() const { return totalStudents; }

bool StudentGroup::isEnrolledIn(Student* s, const string& courseName) const {
    for (int i = 0; i < s->getCompletedCount(); i++)
        if (s->getCompletedCourses()[i] == courseName)
            return true;
    return false;
}
