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

// Functions

void User::create(string email, string password, string name, string surname, string role) {

}

bool User::find(const string &email, const string &password) {
	drogon::orm::DbClientPtr database = drogon::app().getDbClient("Matteo");

	string query = "SELECT email FROM users WHERE email='" + email + "' AND password='" + password + "'";
	future<drogon::orm::Result> future = database->execSqlAsyncFuture(query);
	drogon::orm::Result result = future.get();

	return (bool)result.size();
}

string * User::get(const string &email) {
	drogon::orm::DbClientPtr database = drogon::app().getDbClient("Matteo");

	string query = "SELECT name, surname FROM users WHERE email='" + email + "'";
	future<drogon::orm::Result> future = database->execSqlAsyncFuture(query);
	drogon::orm::Result result = future.get();

	string * data = new string[2];
	data[0] = result[0]["name"].as<string>();
	data[1] = result[0]["surname"].as<string>();

	return data;
}
