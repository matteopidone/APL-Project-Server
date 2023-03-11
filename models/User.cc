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

bool User::find(const string &email, const string &password) {
	drogon::orm::DbClientPtr database = drogon::app().getDbClient("Matteo");

	string query = "SELECT 'name', 'surname' FROM 'users' WHERE email='" + email + "'";

	auto f = database->execSqlAsyncFuture(query);
	return true;
}

string * User::get(const string &email) {
	drogon::orm::DbClientPtr database = drogon::app().getDbClient("Matteo");

	string query = "SELECT 'name', 'surname' FROM 'users' WHERE email='" + email + "'";

	auto f = database->execSqlAsyncFuture(query);
	auto result = f.get();

	string * strArray = new string[2];
	string data[2] = {"matteo", "pidone"};
	strArray = data;
	return strArray;
}
