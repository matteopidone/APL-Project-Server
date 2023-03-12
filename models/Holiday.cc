#include "Holiday.h"

using namespace models;

// Constructors
Holiday::Holiday() {}
Holiday::Holiday(string id_user, tm date, string type, string message) {
	this->id_user = id_user;
	this->date = date;
	this->type = type;
	this->message = message;
}

// Getters
string Holiday::getId_user() const { return this->id_user; }
tm Holiday::getDate() const { return this->date; }
string Holiday::getType() const { return this->type; }
string Holiday::getMessage() const { return this->message; }

// Functions
Holiday * Holiday::getUserHolidays(const string &email, int * size) {
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
		strptime(row[0].as<std::string>().c_str(), "%Y-%m-%d", &date);
		date.tm_year += 1900;
		date.tm_mon += 1;
		values[i++] = Holiday(email, date, row[1].as<std::string>(), row[2].as<std::string>());
	}

	return values;
}
