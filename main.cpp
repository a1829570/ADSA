#include <iostream>
#include <string>
using namespace std;

class HashTable {
    private:
    // Array to hold up to 26 words
        string table[26];  // Array to hold up to 26 words
        enum Status { NEVER_USED, OCCUPIED, TOMBSTONE } status[26];

        // Hash function: returns the index based on the last character of the key
        int hashFunction(const string& key) {
            return key.back() - 'a';  // Using the last character of the key
        }

        // Linear probing search function to find a key
        int search(const string& key) {
            int index = hashFunction(key);
            int originalIndex = index;

            while (status[index] != NEVER_USED) {
                if (status[index] == OCCUPIED && table[index] == key) {
                    return index;  // Found the key
                }
                index = (index + 1) % 26;  // Move to the next slot (with wrap-around)
                if (index == originalIndex) break;  // Full loop, key not found
            }
            return -1;  // Key not found
        }

    public:
        HashTable() {
            for (int i = 0; i < 26; i++) {
                status[i] = NEVER_USED;  // Initialize all slots as never used
            }
        }

        // Insert a key using linear probing
        void insert(const string& key) {
            if (search(key) != -1) return;  // If the key already exists, do nothing
            int index = hashFunction(key);
            while (status[index] == OCCUPIED) {
                index = (index + 1) % 26;  // Linear probing
            }
            table[index] = key;
            status[index] = OCCUPIED;
        }

        // Delete a key by marking it as a tombstone
        void remove(const string& key) {
            int index = search(key);
            if (index != -1) {
                status[index] = TOMBSTONE;  // Mark as tombstone
            }
        }

        // Display all the keys in the table
        void display() {
            for (int i = 0; i < 26; i++) {
                if (status[i] == OCCUPIED) {
                    cout << table[i] << " ";
                }
            }
            cout << endl;
        }
    };

int main() {
    HashTable h;
    string input;
    
    getline(cin, input);  // Get the input line of modification moves

    // Process each modification move
    size_t pos = 0;
    while ((pos = input.find(' ')) != string::npos) {

        string move = input.substr(0, pos);
        input.erase(0, pos + 1);

        if (move[0] == 'A') {
            h.insert(move.substr(1));  // Insert the key
        } 
        
        else if (move[0] == 'D') {
            h.remove(move.substr(1));  // Delete the key
        }
    }

    // Process the last move
    if (input[0] == 'A') {
        h.insert(input.substr(1));
    } 
    
    else if (input[0] == 'D') {
        h.remove(input.substr(1));
    }

    h.display();  // Output the final hash table state

    return 0;
}
