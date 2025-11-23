#include "StudentGroup.h"
#include "student.h"
#include <iostream>
using namespace std;

#include "studentgroup.h"
#include <iostream>
using namespace std;


StudentGroup::StudentGroup(int cap) {
    capacity = cap;
    totalStudents = 0;
    students = new Student * [capacity];
}

StudentGroup::~StudentGroup() {
    for (int i = 0; i < totalStudents; i++)
        delete students[i];
    delete[] students;
}
void StudentGroup::addStudent(Student* s) {
    if (totalStudents == capacity) {
        capacity *= 2;
        Student** newArray = new Student * [capacity];
        for (int i = 0; i < totalStudents; i++)
            newArray[i] = students[i];
        delete[] students;
        students = newArray;
    }
    students[totalStudents] = s;
    totalStudents++;
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

Student** StudentGroup::getAllStudents() const {
    return students;
}

int StudentGroup::getStudentCount() const {
    return totalStudents;
}

bool StudentGroup::isEnrolledIn(Student* s, const string& courseName) const {
    int count = s->getCompletedCount();
    string* arr = s->getCompletedCourses();

    for (int i = 0; i < count; i++) {
        if (arr[i] == courseName)
            return true;
    }
    return false;
}
