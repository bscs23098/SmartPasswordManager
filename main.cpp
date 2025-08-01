#include<iostream>
#include<string>
#include <unordered_map>
#include "Credential.h"
#include "functions.h"

using namespace std;

int main(){
    unordered_map<string,Credential> CredentialManager;

    // int number ;
    // cout<<"Enter Number : ";
    // cin>>number;
    // cin.ignore();
    // for (int i=0;i<number;i++){
    //     insertCredential(CredentialManager);
    // }

    
   

    // // SaveAll
    // saveAll(CredentialManager);

    // load from file 
    loadFromFile(CredentialManager);


   // print
   print(CredentialManager);


   cout<<endl;

   // search
//    findCredential(CredentialManager);


   //update
//    updateCredential(CredentialManager);

//    cout<<endl;
//    cout<<endl;
   
//    print(CredentialManager);


   cout<<endl;



   deleteCredential(CredentialManager);



   cout<<endl;
   cout<<endl;
   print(CredentialManager);

    return 0;
}


