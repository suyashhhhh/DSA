#include <iostream>
#include <vector>

// Define the structure for dictionary entry
struct Entry {
    int key;
    int value;
    Entry* next;
};

// Define the Dictionary class
class Dictionary {
private:
    std::vector<Entry*> table;
    int size;

public:
    // Constructor
    Dictionary(int capacity) {
        table.resize(capacity, nullptr);
        size = capacity;
    }

    // Destructor
    ~Dictionary() {
        for (int i = 0; i < size; i++) {
            Entry* entry = table[i];
            while (entry != nullptr) {
                Entry* temp = entry;
                entry = entry->next;
                delete temp;
            }
        }
    }

    // Hash function
    int hashFunction(int key) {
        return key % size;
    }

    // Insert an entry into the dictionary
    void insert(int key, int value) {
        int index = hashFunction(key);

        Entry* newEntry = new Entry;
        newEntry->key = key;
        newEntry->value = value;
        newEntry->next = nullptr;

        if (table[index] == nullptr) {
            table[index] = newEntry;
        } else {
            Entry* entry = table[index];
            while (entry->next != nullptr) {
                entry = entry->next;
            }
            entry->next = newEntry;
        }
    }

    // Find an entry in the dictionary by key
    int find(int key) {
        int index = hashFunction(key);

        Entry* entry = table[index];
        while (entry != nullptr) {
            if (entry->key == key) {
                return entry->value;
            }
            entry = entry->next;
        }

        // Return -1 if key is not found
        return -1;
    }

    // Delete an entry from the dictionary by key
    void remove(int key) {
        int index = hashFunction(key);

        Entry* entry = table[index];
        Entry* prev = nullptr;

        while (entry != nullptr) {
            if (entry->key == key) {
                if (prev == nullptr) {
                    table[index] = entry->next;
                } else {
                    prev->next = entry->next;
                }
                delete entry;
                return;
            }
            prev = entry;
            entry = entry->next;
        }
    }
};

// Test the Dictionary implementation
int main() {
    int capacity;
    std::cout << "Enter the capacity of the dictionary: ";
    std::cin >> capacity;

    Dictionary dict(capacity);

    while (true) {
        std::cout << "\nDictionary Operations:\n";
        std::cout << "1. Insert\n";
        std::cout << "2. Find\n";
        std::cout << "3. Delete\n";
        std::cout << "4. Exit\n";

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            int key, value;
            std::cout << "Enter the key and value to insert: ";
            std::cin >> key >> value;
            dict.insert(key, value);
            std::cout << "Entry inserted successfully.\n";
        } else if (choice == 2) {
            int key;
            std::cout << "Enter the key to find: ";
            std::cin >> key;
            int value = dict.find(key);
            if (value != -1) {
                std::cout << "Value found:" << value << std::endl;
} else {
std::cout << "Value not found.\n";
}
} else if (choice == 3) {
int key;
std::cout << "Enter the key to delete: ";
std::cin >> key;
dict.remove(key);
std::cout << "Entry deleted successfully.\n";
} else if (choice == 4) {
break;
} else {
std::cout << "Invalid choice. Please try again.\n";
}
}
return 0;
}
