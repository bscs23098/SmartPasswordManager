#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
#include <cstdlib>
#include "Credential.h"
#include "functions.h"

using namespace std;

int main() {
    string password;
    cout << "Enter Master Password: ";
    getline(cin, password);

    if (AuthorizedUSer(password)) {
        logActivity("Verified", "Master User");

        unordered_map<string, Credential> CredentialManager;
        int choice;
        loadFromFile(CredentialManager);

        while (true) {
            system("cls");
            cout << "=== Password Manager Menu ===\n";
            cout << "0. Update Master Password\n";
            cout << "1. Insert Credential(s)\n";
            cout << "2. View All Credentials\n";
            cout << "3. Search by Site Name\n";
            cout << "4. Update Credential\n";
            cout << "5. Save to File\n";
            cout << "6. Delete Credential\n";
            cout << "7. Exit\n";
            cout << "=============================\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "Invalid input. Please enter a number between 0-7.\n";
                logActivity("Invalid Input", "Non-numeric choice");
                system("pause");
                continue;
            }
            cin.ignore(); 
            system("cls");

            switch (choice) {
                case 0:
                    writeMasterPassword();
                    break;

                case 1:
                    insertCredential(CredentialManager);
                    break;

                case 2:
                    print(CredentialManager);
                    logActivity("Displaying", "All Credentials");
                    break;

                case 3:
                    findCredential(CredentialManager);
                    break;

                case 4:
                    updateCredential(CredentialManager);
                    break;

                case 5:
                    saveAll(CredentialManager);
                    cout << "Credentials saved to file.\n";
                    logActivity("Saving", "All Credentials");
                    break;

                case 6:
                    deleteCredential(CredentialManager);
                    break;

                case 7:
                    cout << "Exiting...\n";
                    logActivity("Exiting", "");
                    return 0;

                default:
                    cout << "Invalid option! Try again.\n";
                    logActivity("Invalid Option", "Out-of-range choice");
            }

            cout << "\nPress Enter to continue...";
            cin.get(); 
        }

    } else {
        cout << "Invalid Password. Try Again.\n";
        logActivity("Verification Failed", "Master User");
    }

    return 0;
}
