#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include "Student.h"

using namespace std;

extern vector<Student> students;

void addStudent();
void viewStudents();
void searchStudent();
void deleteStudent();
void modifyStudent();
void saveToFile();
void loadFromFile();
void showStatistics();
void searchByName();
void filterByMarks();
void filterByAge();
void showTopStudents();
void exportToCSV();

int levenshtein(string a, string b);

#endif