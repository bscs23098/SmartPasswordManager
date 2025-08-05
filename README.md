# Smart Powered Password Manager

A C++ console application for securely managing your credentials with a master password. This project provides a simple, menu-driven interface to store, update, search, and manage your passwords efficiently.

## Features

- 🔒 Master password authentication for secure access
- 📝 Insert, view, update, and delete credentials (site, username, password)
- 🔍 Search credentials by site name
- 💾 Save and load credentials from a file
- 🛡️ Update master password functionality
- 📜 Activity logging for important actions and invalid attempts
- 🖥️ User-friendly, menu-driven console interface
- 🚫 Handles invalid input and out-of-range menu choices gracefully

## Getting Started

1. Build the project using g++ or your preferred C++ compiler.
2. Run the executable.
3. Enter your master password to access the password manager.

## File Structure

- `main.cpp` - Main application logic and menu
- `Credential.h` - Credential data structure
- `functions.h` - Function declarations for core features
- `Secure.h` - Security-related functions
- `store.txt` - Stores saved credentials
- `masterPassword.txt` - Stores the master password (encrypted/hashed)
- `activity_log.txt` - Logs user activities

## Usage

Follow the on-screen menu to manage your credentials securely.

---
