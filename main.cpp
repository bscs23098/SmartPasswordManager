#include<iostream>
#include<string>
#include <unordered_map>
#include "Credential.h"
#include "functions.h"
#include <cstdlib>

using namespace std;

int main(){

   string password;
   cout << "Enter Password : ";
   getline(cin,password);
   if(AuthorizedUSer(password)){

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
        cin >> choice;
        cin.ignore();  

        system("cls");

        switch (choice) {
            case 1: {
                int n;
                cout << "How many credentials to insert? ";
                cin >> n;
                cin.ignore();
                for (int i = 0; i < n; i++) {
                    insertCredential(CredentialManager);
                }
                break;
            }

            case 2:
                print(CredentialManager);
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
                break;
             case 6:
                deleteCredential(CredentialManager);
                break;

            case 7: {
                cout << "Exiting...\n";
                return 0;
            }
           
            default:
                cout << "Invalid option! Try again.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    }
  }
    else {
        cout <<" Invalid Password Try Again\n";
    }

    return 0;
}


