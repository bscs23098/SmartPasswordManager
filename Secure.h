#ifndef SECURE_H
#define SECURE_H
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>

using namespace std;

const string SALT = "Xr!9$T7@bQ"; // fixed secret


// Random IV Generator
string generateIV(int length = 8) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static default_random_engine rng(time(0));
    uniform_int_distribution<> dist(0, sizeof(charset) - 2);
    string iv;
    for (int i = 0; i < length; ++i)
        iv += charset[dist(rng)];
    return iv;
}

// XOR with key
string xorEncrypt(const string& text, const string& key) {
    string result = text;
    for (size_t i = 0; i < text.size(); ++i)
        result[i] ^= key[i % key.size()];
    return result;
}

// Base64 encode/decode (same as before)
string base64Encode(const string& in) {
    static const string b64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string out;
    int val = 0, valb = -6;
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(b64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(b64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

string base64Decode(const string& in) {
    static const string b64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[b64_chars[i]] = i;
    string out;
    int val = 0, valb = -8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

// Final encryption using random IV
string encryption(const string& password) {
    string iv = generateIV();                // random
    string salted = iv + password;          // prepend IV to plaintext
    string encrypted = xorEncrypt(salted, SALT);
    return base64Encode(encrypted);         // store base64(iv + encrypted)
}

// Decryption
string decryption(const string& encoded) {
    string decoded = base64Decode(encoded);
    string decrypted = xorEncrypt(decoded, SALT);
    return decrypted.substr(8); // skip the IV
}

void WritePassword(const string str , const string fileName="store.bin"){
    ofstream file(fileName,ios::binary);
    if(!file){
        cout<<"Error while writing file\n";
        return; 
    }
    size_t strLength = str.length();
    file.write(reinterpret_cast<const char*>(&strLength),
        sizeof(strLength));


    file.write(str.c_str(), strLength);

    file.close();
}

string ReadPassword(const string fileName="store.bin"){
    ifstream file (fileName,ios::binary);
    if(!file){
        cout<<"Error While reading file\n";
        return "Error";
    }
    size_t strLength;
    file.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
    string str;
    char* buffer = new char[strLength + 1]; 
    file.read(buffer, strLength);
    buffer[strLength] = '\0';
    str = buffer;
    delete[] buffer;
    file.close();
    return str;
}


#endif
