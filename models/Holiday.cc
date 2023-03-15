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

Holiday * Holiday::getUserHolidays(const string email, int * size) {
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
		for (const drogon::orm::Row row : result) {
			strptime(row[0].as<string>().c_str(), "%Y-%m-%d", &date);
			date.tm_year += 1900;
			date.tm_mon += 1;
			values[i++] = Holiday(email, date, row[1].as<int>(), row[2].as<string>());
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
