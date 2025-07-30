#include<iostream>
#include<string>
#include"Secure.h"
#include "Credential.h"

using namespace std;
const string fileName="store.txt";

int main(){
    // string password;
    // cout<<"Enter Password : ";
    // getline(cin,password);
    // string encrypted = encryption(password);
    // WritePassword(encrypted);
    // cout<<endl<<"Encrypted : "<<encrypted<<endl;
    // string decrypted = ReadPassword();
    // decrypted = decryption(decrypted);
    // cout<<"Decrypted : "<<decrypted<<endl;

    Credential writeObj("facebook.com", "zohaib123", "Zohaib@facbook");
    writeObj.writeCredential(fileName);
    cout<<writeObj<<endl;
    // Step 2: Read back the written data
    Credential readObj(fileName);
    cout << readObj;

    return 0;
}