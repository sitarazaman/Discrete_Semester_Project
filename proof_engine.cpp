#include "proof_engine.h"

ProofEngine::ProofEngine() {}
ProofEngine::~ProofEngine() {}

static int findCourseIndex(const string arr[], int n, const string& key) {
    for (int i = 0; i < n; i++) if (arr[i] == key) return i;
    return -1;
}

bool ProofEngine::provePrerequisiteChain(const string& course, const string courses[], const string prereqs[], int courseCount) {
    cout << "-----------------------------" << endl;
    cout << "Proof: Prerequisite chain for course \"" << course << "\"" << endl;

    int idx = findCourseIndex(courses, courseCount, course);
    if (idx == -1) {
        cout << "Step 1: Course \"" << course << "\" not found in course list." << endl;
        cout << "Conclusion: Chain cannot be proven." << endl;
        cout << "-----------------------------" << endl;
        return false;
    }

    cout << "Step 1: Locate \"" << course << "\" at index " << idx << "." << endl;
    string current = course;
    int safety = 0;
    while (true) {
        if (safety++ > courseCount + 5) {
            cout << "Aborting: possible cycle detected in prerequisites." << endl;
            cout << "Conclusion: invalid chain." << endl;
            cout << "-----------------------------" << endl;
            return false;
        }

        int ci = findCourseIndex(courses, courseCount, current);
        if (ci == -1) {
            cout << "Error: \"" << current << "\" lost from list during traversal." << endl;
            cout << "Conclusion: chain broken." << endl;
            cout << "-----------------------------" << endl;
            return false;
        }

        string pre = prereqs[ci];
        if (pre == "") {
            cout << "Step: \"" << current << "\" has no prerequisite. Reached base course." << endl;
            cout << "Conclusion: Chain valid up to base course." << endl;
            cout << "-----------------------------" << endl;
            return true;
        }
        else {
            cout << "Step: \"" << current << "\" requires \"" << pre << "\"." << endl;
            
            int pi = findCourseIndex(courses, courseCount, pre);
            if (pi == -1) {
                cout << "Failure: prerequisite \"" << pre << "\" not found in course list." << endl;
                cout << "Conclusion: Chain invalid." << endl;
                cout << "-----------------------------" << endl;
                return false;
            }
            
            current = pre;
        }
    }
}

bool ProofEngine::proveStudentPrereqsForCourse(const string& studentName, string* completedCourses, int completedCount, const string& targetCourse, CourseSchedule& cs) {
    cout << "-----------------------------" << endl;
    cout << "Proof: Does student '" << studentName << "' satisfy prerequisites for '" << targetCourse << "'?" << endl;

    if (!cs.isPrerequisiteChainSatisfied(targetCourse)) {
        cout << "Step 1: CourseSchedule reports missing prerequisite in chain for '" << targetCourse << "'." << endl;
        cout << "Conclusion: Cannot prove student meets prerequisites because schedule is inconsistent." << endl;
        cout << "-----------------------------" << endl;
        return false;
    }
    cout << "Step 1: CourseSchedule shows prerequisite chain is present for '" << targetCourse << "'." << endl;

    if (cs.isPrerequisiteSatisfiedForStudent(targetCourse, completedCourses, completedCount)) {
        cout << "Step 2: Student has completed the direct prerequisite(s) required for '" << targetCourse << "'." << endl;
        cout << "Conclusion: Student satisfies prerequisites for '" << targetCourse << "'." << endl;
        cout << "-----------------------------" << endl;
        return true;
    }
    else {
        cout << "Step 2: Student has NOT completed the direct prerequisite(s) for '" << targetCourse << "'." << endl;
        cout << "Step 3: To complete proof, student must complete the missing prerequisite(s)." << endl;
        cout << "Conclusion: Student does NOT currently satisfy prerequisites." << endl;
        cout << "-----------------------------" << endl;
        return false;
    }
}

void ProofEngine::proveTransitivity(const string& A, const string& B, const string& C) {
    cout << "-----------------------------" << endl;
    cout << "Formal Proof: If " << A << " -> " << B << " and " << B << " -> " << C << " then " << A << " -> " << C << endl;
    cout << "1) Assume A implies B (A -> B)." << endl;
    cout << "2) Assume B implies C (B -> C)." << endl;
    cout << "3) Therefore, if A holds then B holds, and if B holds then C holds." << endl;
    cout << "4) By composition of implications, A implies C (A -> C)." << endl;
    cout << "Conclusion: transitivity proven." << endl;
    cout << "-----------------------------" << endl;
}

void ProofEngine::proveCompositionStudentToRoom(const string students[], const string studentCourse[], int studentCount,
    const string courses[], const string courseFaculty[], int courseCount,
    const string faculties[], const string facultyRoom[], int facultyCount) {
    cout << "-----------------------------" << endl;
    cout << "Formal Computational Proof: (Student -> Course) ∘ (Course -> Faculty) ∘ (Faculty -> Room)" << endl;
    for (int i = 0; i < studentCount; i++) {
        string s = students[i];
        string c = studentCourse[i];
        cout << "Student: " << s << endl;
        cout << " Step 1: f(s) = course = " << c << endl;

        string fac = "";
        for (int j = 0; j < courseCount; j++) {
            if (courses[j] == c) { fac = courseFaculty[j]; break; }
        }
        if (fac == "") {
            cout << " Step 2: No faculty found for course " << c << ". Composition breaks here." << endl;
            cout << " Conclusion: (h∘g∘f)(" << s << ") undefined." << endl;
            cout << endl;
            continue;
        }
        else {
            cout << " Step 2: g(c) = faculty = " << fac << endl;
        }

        string room = "";
        for (int k = 0; k < facultyCount; k++) {
            if (faculties[k] == fac) { room = facultyRoom[k]; break; }
        }
        if (room == "") {
            cout << " Step 3: No room assigned for faculty " << fac << ". Composition incomplete." << endl;
            cout << " Conclusion: (h∘g∘f)(" << s << ") undefined." << endl;
            cout << endl;
            continue;
        }
        else {
            cout << " Step 3: h(faculty) = room = " << room << endl;
        }

        cout << " Therefore (h∘g∘f)(" << s << ") = " << room << endl;
        cout << endl;
    }
    cout << "-----------------------------" << endl;
}
