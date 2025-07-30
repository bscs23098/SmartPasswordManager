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

    Credential(string site, string user, string pass, time_t time)
        : siteName(site), userName(user), password(pass), timestamp(time) {}

    Credential(const Credential& obj):siteName(obj.siteName),userName(obj.userName)
                                      ,password(obj.password),timestamp(obj.timestamp){}
                                      
 
    Credential operator =(const Credential& obj){
        return Credential(obj);
    }


    friend ostream& operator<<(ostream& os, const Credential& c) {
        os << "Site: " << c.siteName << "\n"
           << "User: " << c.userName << "\n"
           << "Password: " << c.password << "\n"
           << "Time: " << c.getTimestampStr() << "\n";

        return os;
    }

    void writeCredential(const string fileName = "store.txt") {
        ofstream file(fileName, ios::app); 
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
