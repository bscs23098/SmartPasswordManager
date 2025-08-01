#ifndef FUNCTIONS_H
#define FUNTIONS_H
#include<iostream>
#include<string>
#include <unordered_map>
#include "Credential.h"
#include <chrono>
#include <ctime>

using namespace std;
const string fileName="store.txt";


string getCurrentTime() {
    time_t now = time(nullptr);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

void logActivity(const string& action, const string& siteName) {
    ofstream logFile("activity_log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << "[" << getCurrentTime() << "] "
                << action << " - " << siteName << "\n";
        logFile.close();
    }
}

void print(const unordered_map<string,Credential>& CredentialManager){
   for(auto i : CredentialManager){
      cout<<"--------------\n"<<i.second;
   }
   cout<<"--------------\n";
}


void insertCredential(unordered_map<string,Credential>& CredentialManager){
    cout<<"---------------"<<endl;
    string siteName;
    cout << "Enter site name: ";
    getline(cin, siteName);
    if (CredentialManager.find(siteName) != CredentialManager.end()) {
        cout << "Credential for '" << siteName << "' already exists.\n";
        cout << "Use update option from main menu to change it.\n";
        return;
    }
    logActivity("Inserting",siteName);    
    string userName;
    string password;
    cout<<"Enter User Name : ";
    getline(cin,userName);
    cout<<"Enter Password : ";
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
        logActivity("Finding",site);
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
        logActivity("Updating",site);
        CredentialManager.erase(it); 
        cout << "Enter new credentials for " << site << ":\n"; 
        insertCredential(CredentialManager);
        ofstream file(fileName); 
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

void deleteCredential(unordered_map<string, Credential>& CredentialManager) {
    string site;
    cout << "Enter site name to delete: ";
    getline(cin, site);

    auto it = CredentialManager.find(site);
    if (it != CredentialManager.end()) {
        logActivity("Deletion",site);        
        CredentialManager.erase(it);
        cout << "Credential for '" << site << "' deleted.\n";
        ofstream file(fileName); 
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

void writeMasterPassword(const string& masterPassfile = "masterPassword.txt"){
    ofstream file(masterPassfile);
     if(!file){
        cout<<"Error while writing master password\n";
        return;
    }
    string pass;
    cout<<"Enter Master Password : ";
    getline(cin,pass);
    file << encryption(pass);
    file.close();    
}

string loadMasterPassword(const string& masterPassfile = "masterPassword.txt"){
    ifstream file(masterPassfile);
    if(!file){
        cout<<"Error while reading master password\n";
        return "Error 404";
    }
    string pass;
    getline(file,pass);
    file.close();
    return decryption(pass);
}
bool AuthorizedUSer(const string& pass){
    return loadMasterPassword() == pass;
}



#endif