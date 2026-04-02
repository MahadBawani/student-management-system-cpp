#include <iostream>
#include "Database.h"

using namespace std;

int main() {
    loadFromFile();

    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Update Student\n";
        cout << "6. Statistics\n";
        cout << "7. Search by Name\n";
        cout << "8. Filter by Marks\n";
        cout << "9. Filter by Age\n";
        cout << "10. Show Top Students\n";
        cout << "11. Export to Excel (CSV)\n";
        cout << "12. Save & Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: modifyStudent(); break;
            case 6: showStatistics(); break;
            case 7: searchByName(); break;
            case 8: filterByMarks(); break;
            case 9: filterByAge(); break;
            case 10: showTopStudents(); break;
            case 11: exportToCSV(); break;
            case 12: saveToFile(); break;

            default: cout << "Invalid choice!\n";
        }
    } while (choice != 12);

    return 0;
}