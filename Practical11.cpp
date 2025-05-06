#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    int rollNumber;
    string name;
    string division;
    string address;
};

// Function to add student record
void addStudent(const string& filename) {
    ofstream outFile(filename, ios::app);  // Open file in append mode

    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Student student;
    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cin.ignore();  // Ignore newline character left by cin
    cout << "Enter Name: ";
    getline(cin, student.name);
    cout << "Enter Division: ";
    getline(cin, student.division);
    cout << "Enter Address: ";
    getline(cin, student.address);

    outFile << student.rollNumber << endl;
    outFile << student.name << endl;
    outFile << student.division << endl;
    outFile << student.address << endl;

    outFile.close();
    cout << "Student added successfully!" << endl;
}

// Function to display student record by roll number
void displayStudent(const string& filename, int rollNumber) {
    ifstream inFile(filename);

    if (!inFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Student student;
    bool found = false;

    while (inFile >> student.rollNumber) {
        inFile.ignore();  // Ignore newline after roll number
        getline(inFile, student.name);
        getline(inFile, student.division);
        getline(inFile, student.address);

        if (student.rollNumber == rollNumber) {
            cout << "Student found!" << endl;
            cout << "Roll Number: " << student.rollNumber << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student record not found!" << endl;
    }

    inFile.close();
}

// Function to delete student record by roll number
void deleteStudent(const string& filename, int rollNumber) {
    ifstream inFile(filename);
    ofstream outFile("temp.txt");

    if (!inFile || !outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Student student;
    bool found = false;

    while (inFile >> student.rollNumber) {
        inFile.ignore();  // Ignore newline after roll number
        getline(inFile, student.name);
        getline(inFile, student.division);
        getline(inFile, student.address);

        if (student.rollNumber == rollNumber) {
            found = true;
            cout << "Student record deleted!" << endl;
        } else {
            outFile << student.rollNumber << endl;
            outFile << student.name << endl;
            outFile << student.division << endl;
            outFile << student.address << endl;
        }
    }

    if (!found) {
        cout << "Student record not found!" << endl;
    }

    inFile.close();
    outFile.close();

    // Remove original file and rename temp file to original file name
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}

// Main Menu function
void menu() {
    string filename = "students.txt";
    int choice, rollNumber;

    do {
        cout << "\nStudent Information System\n";
        cout << "1. Add Student\n";
        cout << "2. Display Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(filename);
                break;
            case 2:
                cout << "Enter Roll Number to display: ";
                cin >> rollNumber;
                displayStudent(filename, rollNumber);
                break;
            case 3:
                cout << "Enter Roll Number to delete: ";
                cin >> rollNumber;
                deleteStudent(filename, rollNumber);
                break;
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }

    } while (choice != 4);
}

int main() {
    menu();  // Display the menu and handle user operations
    return 0;
}

