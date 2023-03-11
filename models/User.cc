#include "User.h"

using namespace models;

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

string * User::get(const string &email) {





	string query = "SELECT 'name', 'surname' FROM 'users' WHERE email='" + email + "'";

	auto f = User::getDatabase()->execSqlAsyncFuture(query);
	auto result = f.get();

	return nullptr;
}
