#ifndef LOGIC_ENGINE_H
#define LOGIC_ENGINE_H

#include <string>

using namespace std;   

#define MAX_RULES 50

struct Rule {
    string conditionCourse;
    string conditionProfessor;
    string enforcedLab;
};

class LogicEngine {
private:
    Rule rules[MAX_RULES];
    int ruleCount;

public:
    LogicEngine();

    void addRule(const string& course,
        const string& prof,
        const string& lab);

    bool checkConsistency(const string& course,
        const string& professor,
        const string& assignedLab);

    void printRules();
    int getRuleCount();      
    Rule getRule(int index);
};

#endif
