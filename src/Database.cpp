#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <cmath>

#include "Database.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// GLOBAL VECTOR
vector<Student> students;

/*
===============================
 FUNCTION DECLARATIONS
===============================
*/
void addStudent();
void viewStudents();
void searchStudent();
void deleteStudent();
void saveToFile();
void loadFromFile();
void modifyStudent();
void showStatistics();
/*
===============================
 ADD STUDENT
===============================
*/

bool isNumber(string s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return !s.empty();
}

bool isValidName(string s) {
    for (char c : s) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return !s.empty();
}

bool isFloat(string s) {
    if (s.empty()) return false;

    bool dotSeen = false;
    int start = 0;

    if (s[0] == '-') {
        if (s.length() == 1) return false;
        start = 1;
    }

    for (int i = start; i < s.length(); i++) {
        if (s[i] == '.') {
            if (dotSeen) return false;
            dotSeen = true;
        }
        else if (!isdigit(s[i])) {
            return false;
        }
    }

    return true;
}

void addStudent() {
    string idStr, name, ageStr, marksStr;
    int id, age;
    float marks;

    // ---- ID ----
    while (true) {
        cout << "\nEnter ID (numbers only): ";
        cin >> idStr;

        if (isNumber(idStr)) {
            id = stoi(idStr);

            bool exists = false;
            for (auto &s : students) {
                if (s.id == id) {
                    exists = true;
                    break;
                }
            }

            if (exists) {
                cout << "ID already exists!\n";
            } else {
                break;
            }

        } else {
            cout << "Invalid ID!\n";
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // ---- NAME ----
    while (true) {
        cout << "Enter Name: ";
        getline(cin, name);

        if (isValidName(name)) break;
        else cout << "Invalid Name! Letters only.\n";
    }

    // ---- AGE ----
    while (true) {
        cout << "Enter Age: ";
        cin >> ageStr;

        if (isNumber(ageStr)) {
            age = stoi(ageStr);

            if (age >= 1 && age <= 120) break;
            else cout << "Age must be between 1 & 120\n";

        } else {
            cout << "Invalid Age!\n";
        }
    }

    // ---- MARKS ----
    while (true) {
        cout << "Enter Marks: ";
        cin >> marksStr;

        if (isFloat(marksStr)) {
            marks = stof(marksStr);

            if (marks >= 0 && marks <= 100) break;
            else cout << "Marks must be 0 - 100\n";

        } else {
            cout << "Invalid Marks!\n";
        }
    }


    Student s(id, name, age, marks);
    students.push_back(s);

    cout << "Student added successfully!\n";

    saveToFile();  // ✅ persist to JSON
}

void showStatistics() {
    if (students.empty()) {
        cout << "No data available.\n";
        return;
    }

    float sum = 0;

    for (auto &s : students) {
        sum += s.marks;
    }

    float mean = sum / students.size();

    float variance = 0;

    for (auto &s : students) {
        variance += (s.marks - mean) * (s.marks - mean);
    }

    variance /= students.size();

    float stdDev = sqrt(variance);

    cout << "\n===== Statistics =====\n";
    cout << "Mean: " << mean << endl;
    cout << "Variance: " << variance << endl;
    cout << "Standard Deviation: " << stdDev << endl;
}

/*
===============================
 VIEW ALL STUDENTS
===============================
*/
bool compareByName(Student a, Student b) {
    return a.name < b.name;
}

bool compareByID(Student a, Student b) {
    return a.id < b.id;
}

bool compareByMark(Student a, Student b) {
    return a.marks < b.marks;
}


bool compareByAge(Student a, Student b) {
    return a.age < b.age;
}

void display(vector<Student> list){

    // Header row
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "Age"
         << setw(10) << "Marks" << endl;

    cout << "------------------------------------------------\n";

    // Data rows
    for (auto &s : list){
        cout << left << setw(10) << s.id
             << setw(20) << s.name
             << setw(10) << s.age
             << setw(10) << s.marks << endl;
    }
}

void viewStudents() {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }

    int choice;
    cout << "\nView Options:\n";
    cout << "1. Original Order\n";
    cout << "2. Sort by Name\n";
    cout << "3. Sort by ID\n";
    cout << "4. Sort by Marks\n";
    cout << "5. Sort by Age\n";
    cout << "Enter choice: ";
    cin >> choice; 
    cout<< endl;

    vector<Student> temp = students; // copy

    switch (choice) {
        case 1:
            display(temp);
            break;

        case 2:
            sort(temp.begin(), temp.end(), compareByName);
            display(temp);
            break;

        case 3:
            sort(temp.begin(), temp.end(), compareByID);
            display(temp);
            break;

        case 4:
            sort(temp.begin(), temp.end(), compareByMark);
            display(temp);
            break;

        case 5:
            sort(temp.begin(), temp.end(), compareByAge);
            display(temp);
            break;

        default:
            cout << "Invalid choice!\n";
    }
}

/*
===============================
 SEARCH STUDENT BY ID
===============================
*/
void searchStudent() {
    int id;
    cout << "\nEnter ID to search: ";
    cin >> id;

    bool found = false;

    for (auto &s : students) {
        if (s.id == id) {
            cout << "\nStudent Found:\n";
            cout << "ID: " << s.id << endl;
            cout << "Name: " << s.name << endl;
            cout << "Age: " << s.age << endl;
            cout << "Marks: " << s.marks << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student not found.\n";
    }
}

/*
===============================
 DELETE STUDENT BY ID
===============================
*/
void deleteStudent() {
    int id;
    cout << "\nEnter ID to delete: ";
    cin >> id;

    bool found = false;

    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            students.erase(students.begin() + i);
            cout << "Student deleted successfully.\n";
            saveToFile();
            found = true;
            break;
            
        }
    }

    if (!found) {
        cout << "Student not found.\n";
    }


}

/*
===============================
 SAVE DATA TO FILE
===============================
*/
void saveToFile() {
    json j;

    for (auto &s : students) {
        j.push_back({
            {"id", s.id},
            {"name", s.name},
            {"age", s.age},
            {"marks", s.marks}
        });
    }

    ofstream file("data/students.json");
    file << j.dump(4); 
    file.close();
}



/*
===============================
 LOAD DATA FROM FILE
===============================
*/
void loadFromFile() {
    ifstream file("data/students.json");

    if (!file) {
        cout << "No file found.\n";
        return;
    }

    json j;
    file >> j;

    students.clear();

    for (auto &item : j) {
        Student s;
        s.id = item["id"];
        s.name = item["name"];
        s.age = item["age"];
        s.marks = item["marks"];

        students.push_back(s);
    }
}
void modifyStudent() {
    string idStr;
    int id;

    // ---- ID INPUT ----
    cout << "\nEnter ID to update: ";
    cin >> idStr;

    if (!isNumber(idStr)) {
        cout << "Invalid ID!\n";
        return;
    }

    id = stoi(idStr);

    // ---- SEARCH ----
    for (auto &s : students) {
        if (s.id == id) {

            cout << "\nStudent Found:\n";
            cout << "Name: " << s.name << endl;
            cout << "Age: " << s.age << endl;
            cout << "Marks: " << s.marks << endl;

            int choice;

            cout << "\nWhat do you want to update?\n";
            cout << "1. Name\n";
            cout << "2. Age\n";
            cout << "3. Marks\n";
            cout << "Enter choice: ";
            cin >> choice;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // ---- UPDATE NAME ----
            if (choice == 1) {
                string newName;

                while (true) {
                    cout << "Enter new name: ";
                    getline(cin, newName);

                    if (isValidName(newName)) {
                        s.name = newName;
                        break;
                    } else {
                        cout << "Invalid name!\n";
                    }
                }
            }

            // ---- UPDATE AGE ----
            else if (choice == 2) {
                string ageStr;

                while (true) {
                    cout << "Enter new age: ";
                    cin >> ageStr;

                    if (isNumber(ageStr)) {
                        int newAge = stoi(ageStr);

                        if (newAge >= 1 && newAge <= 120) {
                            s.age = newAge;
                            break;
                        } else {
                            cout << "Age must be 1–120\n";
                        }
                    } else {
                        cout << "Invalid age!\n";
                    }
                }
            }

            // ---- UPDATE MARKS ----
            else if (choice == 3) {
                string marksStr;

                while (true) {
                    cout << "Enter new marks: ";
                    cin >> marksStr;

                    if (isFloat(marksStr)) {
                        float newMarks = stof(marksStr);

                        if (newMarks >= 0 && newMarks <= 100) {
                            s.marks = newMarks;
                            break;
                        } else {
                            cout << "Marks must be 0–100\n";
                        }
                    } else {
                        cout << "Invalid marks!\n";
                    }
                }
            }

            else {
                cout << "Invalid choice!\n";
                return;
            }

            cout << "Student updated successfully!\n";
            

            saveToFile();  
            return;


        }
    }

    cout << "Student not found.\n";

}

void searchByName() {
    cin.ignore();
    string query;

    cout << "\nEnter name to search: ";
    getline(cin, query);

    bool found = false;

    for (auto &s : students) {

        int dist = levenshtein(query, s.name);

        if (dist <= 2) { // 🔥 tolerance (you can tweak)
            cout << "\nMatch Found:\n";
            cout << "ID: " << s.id << endl;
            cout << "Name: " << s.name << endl;
            cout << "Age: " << s.age << endl;
            cout << "Marks: " << s.marks << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "No close matches found.\n";
    }
}
void filterByMarks() {
    float minM, maxM;

    cout << "\nEnter min marks: ";
    cin >> minM;

    cout << "Enter max marks: ";
    cin >> maxM;

    bool found = false;

    for (auto &s : students) {
        if (s.marks >= minM && s.marks <= maxM) {
            cout << "\nID: " << s.id
                 << " Name: " << s.name
                 << " Marks: " << s.marks << endl;
            found = true;
        }
    }

    if (!found) cout << "No students in this range.\n";
}

void filterByAge() {
    int minA, maxA;

    cout << "\nEnter min age: ";
    cin >> minA;

    cout << "Enter max age: ";
    cin >> maxA;

    bool found = false;

    for (auto &s : students) {
        if (s.age >= minA && s.age <= maxA) {
            cout << "\nID: " << s.id
                 << " Name: " << s.name
                 << " Age: " << s.age << endl;
            found = true;
        }
    }

    if (!found) cout << "No students in this range.\n";
}

#include <algorithm>

void showTopStudents() {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }

    // Create a copy so we don't modify original data
    vector<Student> sorted = students;

    // Sort by marks (descending)
   stable_sort(sorted.begin(), sorted.end(), [](Student a, Student b) {
    return a.marks > b.marks;
});

    int count;
    cout << "\nEnter how many top students to display: ";
    cin >> count;

    if (count > sorted.size()) count = sorted.size();

    cout << "\n===== TOP STUDENTS =====\n";

int rank = 1;

for (int i = 0; i < count; i++) {

    if (i > 0 && sorted[i].marks != sorted[i - 1].marks) {
        rank = i + 1; // update rank only when marks change
    }

    cout << "\nRank #" << rank << endl;
    cout << "ID: " << sorted[i].id << endl;
    cout << "Name: " << sorted[i].name << endl;
    cout << "Age: " << sorted[i].age << endl;
    cout << "Marks: " << sorted[i].marks << endl;
}
}

void exportToCSV() {
    if (students.empty()) {
        cout << "No data to export.\n";
        return;
    }

    ofstream file("students_export.csv");

    if (!file) {
        cout << "Error creating file!\n";
        return;
    }

    // Header row
    file << "ID,Name,Age,Marks\n";

    // Data
    for (auto &s : students) {
        file << s.id << ","
             << s.name << ","
             << s.age << ","
             << s.marks << "\n";
    }

    file.close();

    cout << "Data exported successfully to students_export.csv\n";
}

int levenshtein(string a, string b) {
    int n = a.size();
    int m = b.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            if (tolower(a[i - 1]) == tolower(b[j - 1]))
                dp[i][j] = dp[i - 1][j - 1];
            else {
                dp[i][j] = 1 + min({
                    dp[i - 1][j],     // delete
                    dp[i][j - 1],     // insert
                    dp[i - 1][j - 1]  // replace
                });
            }
        }
    }

    return dp[n][m];
}