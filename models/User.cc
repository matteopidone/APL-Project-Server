#include "User.h"

// Constructor
User::User(std::string email, std::string password, std::string name, std::string surname, std::string role) {
	this->email = email;
	this->password = password;
	this->name = name;
	this->surname = surname;
	this->role = role;
}

// Getters
std::string User::getEmail() const { return this->email; }
std::string User::getPassword() const { return this->password; }
std::string User::getName() const { return this->name; }
std::string User::getSurname() const { return this->surname; }
std::string User::getRole() const { return this->role; }
