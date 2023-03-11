#include "User.h"

// Constructor
User::User(string email, string password, string name, string surname, string role) {
	this->email = email;
	this->password = password;
	this->name = name;
	this->surname = surname;
	this->role = role;
}

// Getters
string User::getEmail() const { return this->email; }
string User::getPassword() const { return this->password; }
string User::getName() const { return this->name; }
string User::getSurname() const { return this->surname; }
string User::getRole() const { return this->role; }
