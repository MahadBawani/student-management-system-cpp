#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    float marks;

    Student(int i, string n, int a, float m);
    Student();
};

#endif