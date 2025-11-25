#pragma once
#ifndef FUNCTIONS_MODULE_H
#define FUNCTIONS_MODULE_H

#include <string>
#include <iostream>
using namespace std;

#define MAX_ENTRIES 200
#define MAX_NAME_LEN 128

class FunctionsModule {
private:
    
    string students[MAX_ENTRIES];
    string studentCourse[MAX_ENTRIES];
    int studentCount;

    string courses[MAX_ENTRIES];
    string courseFaculty[MAX_ENTRIES];
    int courseCount;

    string faculties[MAX_ENTRIES];
    string facultyRoom[MAX_ENTRIES];
    int facultyCount;

public:
    FunctionsModule();
    ~FunctionsModule();

    void addStudentCourse(const string& student, const string& course);
    void addCourseFaculty(const string& course, const string& faculty);
    void addFacultyRoom(const string& faculty, const string& room);

    bool isInjectiveStudentToCourse() const;
    bool isInjectiveCourseToFaculty() const;
    bool isInjectiveFacultyToRoom() const;

    bool isSurjectiveStudentToCourse(const string allCourses[], int allCourseCount) const;
    bool isBijectiveStudentToCourse(const string allStudents[], int allStudentCount, const string allCourses[], int allCourseCount) const;

    int composeStudentToRoom(string outStudents[], string outRooms[], int maxOut) const;

    void printInverseCourseToStudents() const;
    void printInverseFacultyToCourses() const;

    void printStudentCourseMappings() const;
    void printCourseFacultyMappings() const;
    void printFacultyRoomMappings() const;

    int getStudentCount() const { return studentCount; }
    int getCourseCount() const { return courseCount; }
    int getFacultyCount() const { return facultyCount; }
};

#endif
