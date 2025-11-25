#include "course.h"
#include <iostream>
using namespace std;

// Constructor
CourseSchedule::CourseSchedule(int cap) {
    capacity = cap;
    courses = new string[capacity];
    prereq = new string[capacity];
    total = 0;
}

// Destructor
CourseSchedule::~CourseSchedule() {
    delete[] courses;
    delete[] prereq;
}

// Add course
void CourseSchedule::addCourse(string courseName, string prerequisite) {
    if (total < capacity) {
        courses[total] = courseName;
        prereq[total] = prerequisite;
        total++;
    }
    else {
        cout << "Course capacity full!" << endl;
    }
}

// Generate all valid orderings of courses
void CourseSchedule::generateOrder() {
    string* done = new string[total];
    generateOrderRecursive(done, 0);
    delete[] done;
}

// Recursive helper function
void CourseSchedule::generateOrderRecursive(string* done, int doneCount) {
    if (doneCount == total) {
        for (int i = 0; i < doneCount; i++)
            cout << done[i] << " ";
        cout << endl;
        return;
    }

    for (int i = 0; i < total; i++) {
        bool alreadyDone = false;
        for (int j = 0; j < doneCount; j++)
            if (done[j] == courses[i])
                alreadyDone = true;

        if (alreadyDone) continue;

        if (prereq[i] == "" || isPrerequisiteChainSatisfied(prereq[i])) {
            done[doneCount] = courses[i];
            generateOrderRecursive(done, doneCount + 1);
        }
    }
}

// Check if a prerequisite chain is satisfied (simplified)
bool CourseSchedule::isPrerequisiteChainSatisfied(string course) {
    for (int i = 0; i < total; i++)
        if (courses[i] == course)
            return true;
    return false;
}

// Check if prerequisite satisfied for student
bool CourseSchedule::isPrerequisiteSatisfiedForStudent(string course, string* completedCourses, int completedCount) {
    string pre = "";
    for (int i = 0; i < total; i++)
        if (courses[i] == course)
            pre = prereq[i];

    if (pre == "") return true;

    for (int i = 0; i < completedCount; i++)
        if (completedCourses[i] == pre)
            return true;

    return false;
}

// ✅ Getter functions
string CourseSchedule::getCourseName(int index) const {
    if (index >= 0 && index < total)
        return courses[index];
    return "";
}

string CourseSchedule::getCoursePrerequisite(int index) const {
    if (index >= 0 && index < total)
        return prereq[index];
    return "";
}

int CourseSchedule::getCourseCount() const {
    return total;
}
