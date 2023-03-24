#include "User.h"

using namespace models;

// Constructor
User::User() {}
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

bool User::create(const string &email, const string &password, const string &name, const string &surname, const string &role) {
	try {
		drogon::orm::DbClientPtr database = drogon::app().getDbClient("Matteo");

		string query = "INSERT INTO users (email, password, name, surname, role) VALUES ('" + email + "', '" + password + "', '" + name + "', '" + surname + "', '" + role + "')";

		future<drogon::orm::Result> future = database->execSqlAsyncFuture(query);
		drogon::orm::Result result = future.get();
		return true;

	} catch (const exception &e) {
		cout << "Errore durante l'esecuzione della query: " << e.what() << endl;
		return false;
	}
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

bool User::isAdministrator(const string &email) {
	int adminType = AllowedRole::Administrator;
	drogon::orm::DbClientPtr database = drogon::app().getDbClient("Matteo");

	string query = "SELECT * FROM users WHERE email='" + email + "' and role =" + to_string(adminType);
	future<drogon::orm::Result> future = database->execSqlAsyncFuture(query);
	drogon::orm::Result result = future.get();

	return (bool)result.size();
}

User * User::getAllUsers(int &size) {
	try {
		drogon::orm::DbClientPtr database = drogon::app().getDbClient("Matteo");

		string query = "SELECT email, password, name, surname, role FROM users WHERE role='" + to_string(AllowedRole::Dependent) + "'";

		future<drogon::orm::Result> future = database->execSqlAsyncFuture(query);
		drogon::orm::Result result = future.get();

		size = result.size();
		if (!size) {
			return nullptr;
		}
		User * values = new User[size];

		int i = 0;
		tm date = {};
		for (const drogon::orm::Row row : result) {
			values[i++] = User(row[0].as<string>(), row[1].as<string>(), row[2].as<string>(), row[3].as<string>(), row[4].as<string>());
		}

		return values;

	} catch (const exception &e) {
		cout << "Errore durante l'esecuzione della query: " << e.what() << endl;
		return nullptr;
	}
}
