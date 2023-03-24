#include "Holiday.h"

using namespace models;

// Constructors
Holiday::Holiday() {}
Holiday::Holiday(const string id_user, const tm date, const int type, const string message) {
	this->id_user = id_user;
	this->date = date;
	this->type = type;
	this->message = message;
}

// Getters
string Holiday::getId_user() const { return this->id_user; }
tm Holiday::getDate() const { return this->date; }
int Holiday::getType() const { return this->type; }
string Holiday::getMessage() const { return this->message; }

// Functions
bool Holiday::isValidTypeHoliday(const int &value){
	if (value != AllowedHolidayType::Pending && value != AllowedHolidayType::Accepted && value != AllowedHolidayType::Refused ) {
    	return false;
    }

    return true;
}

Holiday * Holiday::getAllUserHolidays(const string email, int * size) {
	try {
		drogon::orm::DbClientPtr database = drogon::app().getDbClient("Matteo");

		string query = "SELECT date, type, message FROM holidays WHERE id_user='" + email + "'";

		future<drogon::orm::Result> future = database->execSqlAsyncFuture(query);
		drogon::orm::Result result = future.get();

		*size = result.size();
		if (!*size) {
			return nullptr;
		}
		Holiday * values = new Holiday[*size];

		int i = 0;
		tm date = {};
		for (drogon::orm::Result::iterator it = result.begin(); it != result.end() ; it++){
			strptime((*it)[0].as<char*>(), "%Y-%m-%d", &date);
			date.tm_year += 1900;
			date.tm_mon += 1;
			values[i++] = Holiday(email, date, (*it)[1].as<int>(), (*it)[2].as<string>());
		}

		return values;

	} catch (const exception &e) {
		cout << "Errore durante l'esecuzione della query: " << e.what() << endl;
		return nullptr;
	}
}

bool Holiday::insertUserHoliday(const string email, const tm date, const string message) {
	try {
		drogon::orm::DbClientPtr database = drogon::app().getDbClient("Matteo");

		string new_date = to_string(date.tm_year + 1900) + "-" + to_string(date.tm_mon + 1) + "-" + to_string(date.tm_mday);
		string query = "INSERT INTO holidays(id_user, date, type, message) VALUES ('" + email + "','" + new_date + "',0,'" + message + "') ON DUPLICATE KEY UPDATE type=0";

		future<drogon::orm::Result> future = database->execSqlAsyncFuture(query);
		drogon::orm::Result result = future.get();
		return true;

	} catch (const exception &e) {
		cout << "Errore durante l'esecuzione della query: " << e.what() << endl;
		return false;
	}
}

bool Holiday::isAlreadyRequested(const string &email, const tm &date){
	try {
		drogon::orm::DbClientPtr database = drogon::app().getDbClient("Matteo");

		string str_date = to_string(date.tm_year + 1900) + "-" + to_string(date.tm_mon + 1) + "-" + to_string(date.tm_mday);
		string query = "SELECT * FROM holidays WHERE id_user='" + email + "' AND date ='" + str_date + "'";

		future<drogon::orm::Result> future = database->execSqlAsyncFuture(query);
		drogon::orm::Result result = future.get();

		int size = result.size();
		if (!size) {
			return false;
		} else {
			return true;
		}

	} catch (const exception &e) {
		cout << "Errore durante l'esecuzione della query: " << e.what() << endl;
		return false;
	}
}

bool Holiday::updateUserHoliday(const string &email, const tm &date, const int &type) {
	try {
		drogon::orm::DbClientPtr database = drogon::app().getDbClient("Matteo");

		string date_string = to_string(date.tm_year + 1900) + "-" + to_string(date.tm_mon + 1) + "-" + to_string(date.tm_mday);
		string query = "UPDATE holidays SET type = " + to_string(type) + " WHERE id_user = '" + email + "' AND date = '" + date_string + "'";
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