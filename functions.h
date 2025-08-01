#ifndef FUNCTIONS_H
#define FUNTIONS_H
#include<iostream>
#include<string>
#include <unordered_map>
#include "Credential.h"

using namespace std;
const string fileName="store.txt";

void print(const unordered_map<string,Credential>& CredentialManager){
   for(auto i : CredentialManager){
      cout<<"--------------\n"<<i.second;
   }
   cout<<"--------------\n";
}


void insertCredential(unordered_map<string,Credential>& CredentialManager){
    cout<<"---------------"<<endl;
        // insert 
    string siteName;
    string userName;
    string password;

    cout<<"Site Name : ";
    getline(cin,siteName);
    cout<<"User Name : ";
    getline(cin,userName);
    cout<<"Password : ";
    getline(cin,password);
    CredentialManager.insert({siteName, Credential(siteName, userName, password)});
}

void saveAll(unordered_map<string,Credential>& CredentialManager){
    for(auto i : CredentialManager){
        i.second.writeCredential(fileName);
    }
}

void loadFromFile(unordered_map<string, Credential>& CredentialManager) {
    ifstream file(fileName);
    if (!file) {
        cout << "No existing credentials found.\n";
        return;
    }

    string site, user, pass;
    time_t timestamp;

    while (getline(file, site) && getline(file, user) && getline(file, pass)) {
        file >> timestamp;
        file.ignore();
        CredentialManager.insert({decryption(site), 
            Credential(decryption(site), decryption(user), decryption(pass), timestamp)});
    }

    file.close();
}


void findCredential(const unordered_map<string, Credential>& CredentialManager){
    string site;
    cout <<"Enter site name to update : ";
    getline(cin,site);
    auto it = CredentialManager.find(site);
    if (it != CredentialManager.end()) {
        cout << it->second << endl;
    } else {
        cout << site << " not found 404\n";
    }
}
void updateCredential(unordered_map<string, Credential>& CredentialManager){
    string site;
    cout <<"Enter site name to update : ";
    getline(cin,site);
    auto it = CredentialManager.find(site);
    if (it != CredentialManager.end()) {
        CredentialManager.erase(it); 
        cout << "Enter new credentials for " << site << ":\n"; 
        insertCredential(CredentialManager);
        ofstream file(fileName, ios::app); 
        if(!file){
            cout<<"Updated Cannot be Saved in file\n";

        }
        file.close();
        saveAll(CredentialManager);
        cout<<"Updated Saved into file\n";
    } else {
        cout << site << " not found 404\n";
    }

}

#endif