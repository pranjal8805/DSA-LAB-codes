#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

// Maximum size of the hash table
#define TABLE_SIZE 10

// Struct for a client (name and telephone number)
struct Client {
    string name;
    string phone;
};

// Hash function to map a string (client name) to an index in the hash table
int hashFunction(const string& key) {
    int hashValue = 0;
    for (char c : key) {
        hashValue += c;  // Adding ASCII values of the characters
    }
    return hashValue % TABLE_SIZE;  // Ensure index stays within the table size
}

// Separate Chaining Hash Table
class SeparateChainingHashTable {
private:
    list<Client>* table;
    int totalComparisons;

public:
    SeparateChainingHashTable() {
        table = new list<Client>[TABLE_SIZE];
        totalComparisons = 0;
    }

    void insert(const string& name, const string& phone) {
        int index = hashFunction(name);
        table[index].push_back({name, phone});
    }

    string search(const string& name) {
        int index = hashFunction(name);
        totalComparisons = 0; // Reset comparison counter
        
        // Traverse the list at the hashed index and compare
        for (Client& client : table[index]) {
            totalComparisons++;
            if (client.name == name) {
                return client.phone;
            }
        }
        return "Not Found";
    }

    int getComparisons() {
        return totalComparisons;
    }

    ~SeparateChainingHashTable() {
        delete[] table;
    }
};

// Linear Probing Hash Table
class LinearProbingHashTable {
private:
    Client* table;
    int* status;  // Array to track the status of each slot (0: empty, 1: filled)
    int totalComparisons;

public:
    LinearProbingHashTable() {
        table = new Client[TABLE_SIZE];
        status = new int[TABLE_SIZE]{0};  // Initialize all to 0 (empty)
        totalComparisons = 0;
    }

    void insert(const string& name, const string& phone) {
        int index = hashFunction(name);
        int originalIndex = index;

        // Linear probing to find an empty slot
        while (status[index] == 1) {  // If slot is filled, move to next
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) return;  // Avoid infinite loop
        }

        // Insert the client into the empty slot
        table[index] = {name, phone};
        status[index] = 1;
    }

    string search(const string& name) {
        int index = hashFunction(name);
        int originalIndex = index;
        totalComparisons = 0;  // Reset comparison counter

        while (status[index] != 0) {  // While slot is not empty
            totalComparisons++;
            if (status[index] == 1 && table[index].name == name) {
                return table[index].phone;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) break;  // Avoid infinite loop
        }

        return "Not Found";
    }

    int getComparisons() {
        return totalComparisons;
    }

    ~LinearProbingHashTable() {
        delete[] table;
        delete[] status;
    }
};

int main() {
    // Sample telephone book database
    string names[] = {"Alice", "Bob", "Charlie", "David", "Eve"};
    string phones[] = {"1234", "5678", "91011", "1213", "1415"};

    // Create hash tables for separate chaining and linear probing
    SeparateChainingHashTable sct;
    LinearProbingHashTable lpt;

    // Insert clients into both hash tables
    for (int i = 0; i < 5; ++i) {
        sct.insert(names[i], phones[i]);
        lpt.insert(names[i], phones[i]);
    }

    // Test search and compare number of comparisons
    string searchName = "Charlie";

    cout << "Search using Separate Chaining:" << endl;
    string phone = sct.search(searchName);
    cout << "Phone: " << phone << endl;
    cout << "Comparisons made: " << sct.getComparisons() << endl;

    cout << "\nSearch using Linear Probing:" << endl;
    phone = lpt.search(searchName);
    cout << "Phone: " << phone << endl;
    cout << "Comparisons made: " << lpt.getComparisons() << endl;

    return 0;
}

