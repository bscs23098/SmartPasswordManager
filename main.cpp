#include<iostream>
#include<string>
#include"Secure.h"

using namespace std;

int main(){
    string password;
    cout<<"Enter Password : ";
    getline(cin,password);
    string encrypted = encryption(password);
    WritePassword(encrypted);
    cout<<endl<<"Encrypted : "<<encrypted<<endl;
    string decrypted = ReadPassword();
    decrypted = decryption(decrypted);
    cout<<"Decrypted : "<<decrypted<<endl;

    return 0;
}