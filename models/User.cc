#include "User.h"

using namespace models;

// Constructor
User::User() {}
User::User(const string email, const string password, const string name, const string surname, const string description, const string role) {
	this->email = email;
	this->password = password;
	this->name = name;
	this->description = description;
	this->surname = surname;
	this->role = role;
}

// Getters
string User::getEmail() const { return this->email; }
string User::getPassword() const { return this->password; }
string User::getName() const { return this->name; }
string User::getSurname() const { return this->surname; }
string User::getDescription() const { return this->description; }
string User::getRole() const { return this->role; }

// Functions

bool User::create(const string email, const string password, const string name, const string surname, const string description, const string role) {
	try {
		drogon::orm::DbClientPtr database = drogon::app().getDbClient("apl_db_client");

		string query = "INSERT INTO users (email, password, name, surname, description, role) VALUES ('" + email + "', '" + password + "', '" + name + "', '" + surname + "', '" + description + "', '" + role + "')";

		future<drogon::orm::Result> future = database->execSqlAsyncFuture(query);
		drogon::orm::Result result = future.get();

		if ( result.affectedRows() > 0 ) {
			return true;
		}
		return false;

	} catch (const exception &e) {
		cout << "Errore durante l'esecuzione della query: " << e.what() << endl;
		return false;
	}
}

bool User::find(const string email, const string password, const string role) {
	try {
		drogon::orm::DbClientPtr database = drogon::app().getDbClient("apl_db_client");

		string query = "SELECT email FROM users WHERE email='" + email + "' AND password='" + password + "' AND role='" + role + "'";
		future<drogon::orm::Result> future = database->execSqlAsyncFuture(query);
		drogon::orm::Result result = future.get();

		return (bool)result.size();

	} catch (const exception &e) {
		cout << "Errore durante l'esecuzione della query: " << e.what() << endl;
		return false;
	}
}

string * User::getUserInfo(const string email) {
	try {
		drogon::orm::DbClientPtr database = drogon::app().getDbClient("apl_db_client");

		string query = "SELECT name, surname, description FROM users WHERE email='" + email + "'";
		future<drogon::orm::Result> future = database->execSqlAsyncFuture(query);
		drogon::orm::Result result = future.get();

		string * data = new string[3];
		data[0] = result[0]["name"].as<string>();
		data[1] = result[0]["surname"].as<string>();
		data[2] = result[0]["description"].as<string>();

		return data;

	} catch (const exception &e) {
		cout << "Errore durante l'esecuzione della query: " << e.what() << endl;
		return nullptr;
	}
}

bool User::isAdministrator(const string email) {
	try {
		int adminType = AllowedRole::Administrator;
		drogon::orm::DbClientPtr database = drogon::app().getDbClient("apl_db_client");

		string query = "SELECT * FROM users WHERE email='" + email + "' and role =" + to_string(adminType);
		future<drogon::orm::Result> future = database->execSqlAsyncFuture(query);
		drogon::orm::Result result = future.get();

		return (bool)result.size();

	} catch (const exception &e) {
		cout << "Errore durante l'esecuzione della query: " << e.what() << endl;
		return false;
	}
}

User * User::getAllUsers(int &size) {
	try {
		drogon::orm::DbClientPtr database = drogon::app().getDbClient("apl_db_client");

		string query = "SELECT email, password, name, surname, description, role FROM users WHERE role='" + to_string(AllowedRole::Dependent) + "'";

		future<drogon::orm::Result> future = database->execSqlAsyncFuture(query);
		drogon::orm::Result result = future.get();

		size = result.size();
		if (!size) {
			return nullptr;
		}
		User * values = new User[size];

		//Itero la collezione con l'iteratore associato a Result.
		int n = 0;
		for (drogon::orm::Result::iterator it = result.begin(); it != result.end() ; it++){

			values[n++] = User((*it)["email"].as<string>(), (*it)["password"].as<string>(), (*it)["name"].as<string>(), (*it)["surname"].as<string>(), (*it)["description"].as<string>(), (*it)["role"].as<string>());
		}

		return values;

	} catch (const exception &e) {
		cout << "Errore durante l'esecuzione della query: " << e.what() << endl;
		return nullptr;
	}
}
