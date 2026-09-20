#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

// Check whether username already exists
bool usernameExists(string username) {
    ifstream file("users.txt");

    string storedUsername, storedPassword;

    while (file >> storedUsername >> storedPassword) {
        if (storedUsername == username) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Validate username
bool validUsername(string username) {

    if (username.length() < 3) {
        return false;
    }

    for (char ch : username) {
        if (!isalnum(ch) && ch != '_') {
            return false;
        }
    }

    return true;
}

// Validate password
bool validPassword(string password) {

    if (password.length() < 6) {
        return false;
    }

    return true;
}

// Registration function
void registerUser() {

    string username, password;

    cout << "\n===== REGISTRATION =====\n";

    cout << "Enter username: ";
    cin >> username;

    // Validate username
    if (!validUsername(username)) {
        cout << "Error: Username must contain at least 3 characters.\n";
        cout << "Only letters, numbers and '_' are allowed.\n";
        return;
    }

    // Check duplicate username
    if (usernameExists(username)) {
        cout << "Error: Username already exists!\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Validate password
    if (!validPassword(password)) {
        cout << "Error: Password must contain at least 6 characters.\n";
        return;
    }

    // Store credentials in file
    ofstream file("users.txt", ios::app);

    if (!file) {
        cout << "Error: Unable to open file.\n";
        return;
    }

    file << username << " " << password << endl;

    file.close();

    cout << "Registration successful!\n";
}

// Login function
void loginUser() {

    string username, password;
    string storedUsername, storedPassword;

    cout << "\n===== LOGIN =====\n";

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");

    if (!file) {
        cout << "Error: No registered users found.\n";
        return;
    }

    bool loginSuccess = false;

    // Read credentials from file
    while (file >> storedUsername >> storedPassword) {

        if (storedUsername == username &&
            storedPassword == password) {

            loginSuccess = true;
            break;
        }
    }

    file.close();

    if (loginSuccess) {
        cout << "\nLogin successful!\n";
        cout << "Welcome, " << username << "!\n";
    }
    else {
        cout << "\nLogin failed!\n";
        cout << "Invalid username or password.\n";
    }
}

// Main function
int main() {

    int choice;

    do {
        cout << "\n==============================\n";
        cout << "   LOGIN & REGISTRATION SYSTEM\n";
        cout << "==============================\n";

        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                cout << "\nThank you for using the system!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}