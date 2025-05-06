#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Employee {
    string name;
    string address;
    int empID;
    int loc;

public:
    Employee() {
        name = address = "";
        loc = empID = 0;
    }

    bool isEmpty() {
        return empID == 0;
    }

    void display() {
        cout << "Name: " << name << ", Address: " << address << ", ID: " << empID << ", Location: " << loc << endl;
    }

    friend class Hashtable;
    friend class MyFile;
};

class Hashtable {
    Employee* employees;
    int tableSize;

    int hash(int empID) {
        return empID % tableSize;
    }

public:
    Hashtable(int size = 20) {
        tableSize = size;
        employees = new Employee[tableSize];
    }

    void insertHT(Employee emp) {
        int index = hash(emp.empID);
        int curr = index;
        while (!employees[curr].isEmpty()) {
            curr = (curr + 1) % tableSize;
        }
        employees[curr] = emp;
    }

    void showHT() {
        for (int i = 0; i < tableSize; i++) {
            cout.width(7);
            cout << employees[i].empID;
            cout << "\t";
            cout.width(5);
            cout << employees[i].loc << endl;
        }
    }

    void deleteHT(int empID) {
        int index = hash(empID);
        int curr = index, passes = 0;
        while (employees[curr].empID != empID && passes < tableSize) {
            curr = (curr + 1) % tableSize;
            passes++;
        }
        if (employees[curr].empID == empID)
            employees[curr] = Employee();
    }

    int searchHT(int empID) {
        int index = hash(empID);
        int curr = index, passes = 0;
        while (employees[curr].empID != empID && passes < tableSize) {
            curr = (curr + 1) % tableSize;
            passes++;
        }
        if (employees[curr].empID == empID)
            return employees[curr].loc;
        else
            return -1;
    }

    void updateEntry(int empID, int newLoc) {
        int index = hash(empID);
        int curr = index;
        while (employees[curr].empID != empID) {
            curr = (curr + 1) % tableSize;
        }
        employees[curr].loc = newLoc;
    }
};

class MyFile {
    char filename[20];
    fstream file;
    Hashtable table;
    Employee E;

public:
    MyFile() {
        cout << "Enter file name: ";
        cin >> filename;

        file.open(filename, ios::out | ios::binary);
        if (file)
            cout << "File created successfully.\n";
        file.close();
    }

    void addRecord(string n, int id, string a) {
        file.open(filename, ios::out | ios::in | ios::binary);
        if (!file) {
            
            file.open(filename, ios::out | ios::binary);
            file.close();
            file.open(filename, ios::out | ios::in | ios::binary);
        }
    
        file.seekp(0, ios::end);  
        streampos loc = file.tellp();  
    
        E.name = n;
        E.empID = id;
        E.address = a;
        E.loc = loc;
    
        cout << "Location: " << E.loc << endl;
    
        table.insertHT(E);
        file.write((char*)&E, sizeof(E));
        file.close();
    }
    

    void readRecord(int empID) {
        file.open(filename, ios::in | ios::binary);
        if (!file)
            cout << "Error opening file\n";
        else {
            int loc = table.searchHT(empID);
            if (loc == -1)
                cout << "No such record exists.\n";
            else {
                file.seekg(loc, ios::beg);
                file.read((char*)&E, sizeof(E));
                E.display();
            }
        }
        file.close();
    }

    void deleteRecord(int empID) {
        int loc = table.searchHT(empID);
        if (loc == -1) {
            cout << "No such record exists to delete\n";
            return;
        }

        fstream temp;
        temp.open("temp", ios::out | ios::binary);
        file.open(filename, ios::in | ios::binary);

        while (file.read((char*)&E, sizeof(E))) {
            if (E.empID == empID) {
                cout << "Deleting Record: " << empID << endl;
                continue;
            } else {
                E.loc = temp.tellp();
                table.updateEntry(E.empID, E.loc);
                temp.write((char*)&E, sizeof(E));
            }
        }

        file.close();
        temp.close();
        remove(filename);
        rename("temp", filename);
        table.deleteHT(empID);
        cout << "Record deleted!\n";
    }
};

int main() {
    MyFile File;
    File.addRecord("Durvesh", 21381, "Mumbai");
    File.addRecord("Shantanu", 21382, "Pune");
    File.addRecord("Riya", 21383, "Nasik");
    File.addRecord("Atharva", 21384, "Baner");
    File.addRecord("Aarti", 21385, "Balewadi");
    File.addRecord("Riddhi", 21467, "Hadapsar");

    cout << "\nReading Record with ID 21383:\n";
    File.readRecord(21383);

    cout << "\nDeleting Record with ID 21384:\n";
    File.deleteRecord(21384);

    cout << "\nReading Record with ID 21467:\n";
    File.readRecord(21467);

    cout << "\nReading Deleted Record (21384):\n";
    File.readRecord(21384);

    return 0;
}
