#include "logic_engine.h"
#include <iostream>
using namespace std;

LogicEngine::LogicEngine() {
    ruleCount = 0;
}

void LogicEngine::addRule(const string& course,
    const string& prof,
    const string& lab) {
    if (ruleCount >= MAX_RULES) {
        cout << "Cannot add more rules." << endl;
        return;
    }

    rules[ruleCount].conditionCourse = course;
    rules[ruleCount].conditionProfessor = prof;
    rules[ruleCount].enforcedLab = lab;
    ruleCount++;
}

bool LogicEngine::checkConsistency(const string& course,
    const string& professor,
    const string& assignedLab)
{
    for (int i = 0; i < ruleCount; i++) {
        bool sameCourse = (rules[i].conditionCourse == course);
        bool sameProf = (rules[i].conditionProfessor == professor);

        if (sameCourse && sameProf) {
            if (rules[i].enforcedLab != assignedLab) {
                cout << "Conflict detected: Lab must be "
                    << rules[i].enforcedLab << " according to rules." << endl;
                return false;
            }
        }
    }

    return true;
}

void LogicEngine::printRules() {
    cout << "--- Logic Rules ---" << endl;
    for (int i = 0; i < ruleCount; i++) {
        cout << "IF Course = " << rules[i].conditionCourse
            << " AND Professor = " << rules[i].conditionProfessor
            << " : Lab = " << rules[i].enforcedLab << endl;
    }
    
}
int LogicEngine::getRuleCount() const {
    return ruleCount;
}

Rule LogicEngine::getRule(int index) const {
    return rules[index];
}
