#include "functions.h"

FunctionsModule::FunctionsModule() {
    studentCount = 0;
    courseCount = 0;
    facultyCount = 0;
}

FunctionsModule::~FunctionsModule() {
    // nothing dynamic allocated here, so nothing to free
}

void FunctionsModule::addStudentCourse(const string& student, const string& course) {
    if (studentCount >= MAX_ENTRIES) {
        cout << "Cannot add more students, capacity reached." << endl;
        return;
    }
    students[studentCount] = student;
    studentCourse[studentCount] = course;
    studentCount++;
}

void FunctionsModule::addCourseFaculty(const string& course, const string& faculty) {
    
    for (int i = 0; i < courseCount; i++) {
        if (courses[i] == course) {
            courseFaculty[i] = faculty;
            return;
        }
    }
    if (courseCount >= MAX_ENTRIES) {
        cout << "Cannot add more courses, capacity reached." << endl;
        return;
    }
    courses[courseCount] = course;
    courseFaculty[courseCount] = faculty;
    courseCount++;
}

void FunctionsModule::addFacultyRoom(const string& faculty, const string& room) {
    
    for (int i = 0; i < facultyCount; i++) {
        if (faculties[i] == faculty) {
            facultyRoom[i] = room;
            return;
        }
    }
    if (facultyCount >= MAX_ENTRIES) {
        cout << "Cannot add more faculties, capacity reached." << endl;
        return;
    }
    faculties[facultyCount] = faculty;
    facultyRoom[facultyCount] = room;
    facultyCount++;
}

void FunctionsModule::printStudentCourseMappings() const {
    cout << "--- Student -> Course ---" << endl;
    for (int i = 0; i < studentCount; i++) {
        cout << students[i] << " -> " << studentCourse[i] << endl;
    }
}

void FunctionsModule::printCourseFacultyMappings() const {
    cout << "--- Course -> Faculty ---" << endl;
    for (int i = 0; i < courseCount; i++) {
        cout << courses[i] << " -> " << courseFaculty[i] << endl;
    }
}

void FunctionsModule::printFacultyRoomMappings() const {
    cout << "--- Faculty -> Room ---" << endl;
    for (int i = 0; i < facultyCount; i++) {
        cout << faculties[i] << " -> " << facultyRoom[i] << endl;
    }
}

bool FunctionsModule::isInjectiveStudentToCourse() const {
    for (int i = 0; i < studentCount; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (studentCourse[i] == studentCourse[j]) return false;
        }
    }
    return true;
}

bool FunctionsModule::isInjectiveCourseToFaculty() const {
    for (int i = 0; i < courseCount; i++) {
        for (int j = i + 1; j < courseCount; j++) {
            if (courseFaculty[i] == courseFaculty[j]) return false;
        }
    }
    return true;
}

bool FunctionsModule::isInjectiveFacultyToRoom() const {
    for (int i = 0; i < facultyCount; i++) {
        for (int j = i + 1; j < facultyCount; j++) {
            if (facultyRoom[i] == facultyRoom[j]) return false;
        }
    }
    return true;
}

bool FunctionsModule::isSurjectiveStudentToCourse(const string allCourses[], int allCourseCount) const {
    for (int i = 0; i < allCourseCount; i++) {
        bool found = false;
        for (int j = 0; j < studentCount; j++) {
            if (studentCourse[j] == allCourses[i]) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

bool FunctionsModule::isBijectiveStudentToCourse(const string allStudents[], int allStudentCount, const string allCourses[], int allCourseCount) const {
    if (allStudentCount != allCourseCount) return false;
    if (!isInjectiveStudentToCourse()) return false;
    if (!isSurjectiveStudentToCourse(allCourses, allCourseCount)) return false;
    return true;
}

int FunctionsModule::composeStudentToRoom(string outStudents[], string outRooms[], int maxOut) const {
    int outCount = 0;
    for (int i = 0; i < studentCount && outCount < maxOut; i++) {
        string stud = students[i];
        string course = studentCourse[i];

        string faculty = "";
        for (int j = 0; j < courseCount; j++) {
            if (courses[j] == course) {
                faculty = courseFaculty[j];
                break;
            }
        }

        string room = "";
        if (faculty != "") {
            for (int k = 0; k < facultyCount; k++) {
                if (faculties[k] == faculty) {
                    room = facultyRoom[k];
                    break;
                }
            }
        }

        outStudents[outCount] = stud;
        outRooms[outCount] = room;
        outCount++;
    }
    return outCount;
}

void FunctionsModule::printInverseCourseToStudents() const {
    cout << "--- Inverse: Course -> { Students } ---" << endl;
    for (int i = 0; i < courseCount; i++) {
        cout << courses[i] << " <- { ";
        for (int j = 0; j < studentCount; j++) {
            if (studentCourse[j] == courses[i]) cout << students[j] << " ";
        }
        cout << "}" << endl;
    }
}

void FunctionsModule::printInverseFacultyToCourses() const {
    cout << "--- Inverse: Faculty -> { Courses } ---" << endl;
    for (int i = 0; i < facultyCount; i++) {
        cout << faculties[i] << " <- { ";
        for (int j = 0; j < courseCount; j++) {
            if (courseFaculty[j] == faculties[i]) cout << courses[j] << " ";
        }
        cout << "}" << endl;
    }
}
