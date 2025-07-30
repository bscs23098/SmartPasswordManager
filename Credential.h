#ifndef CREDENTIAL_H
#define CREDENTIAL_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "Secure.h"

using namespace std;

class Credential {
    string siteName;
    string userName;
    string password;
    time_t timestamp;  

public:
    Credential() : siteName(""), userName(""), password(""), timestamp(time(nullptr)) {}

    Credential(string site, string user, string pass)
        : siteName(site), userName(user), password(pass), timestamp(time(nullptr)) {}

    Credential(const string fileName) {
        ifstream file(fileName);
        if (!file) {
            cout << "Error while reading Credentials\n";
            return;
        }
    
        string line;
    
        getline(file, line);
        siteName = decryption(line);
    
        getline(file, line);
        userName = decryption(line);
    
        getline(file, line);
        password = decryption(line);
    
        getline(file, line);
        timestamp = static_cast<time_t>(stoll(line));
    
        file.close();
    }
 


    friend ostream& operator<<(ostream& os, const Credential& c) {
        os << "Site: " << c.siteName << "\n"
           << "User: " << c.userName << "\n"
           << "Password: " << c.password << "\n"
           << "Time: " << c.getTimestampStr() << "\n";
        return os;
    }

    void writeCredential(const string fileName = "store.txt") {
    ofstream file(fileName, ios::app);  // no ios::binary
    if (!file) {
        cout << "Error while writing credentials\n";
        return;
    }

    file << encryption(siteName) << '\n';
    file << encryption(userName) << '\n';
    file << encryption(password) << '\n';
    file << timestamp << '\n';  // write raw time_t as string

    file.close();
    }




private :
    string getTimestampStr() const {
        char buffer[80];
        struct tm* timeInfo = localtime(&timestamp);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
        return string(buffer);
    }
    
};

#endif
