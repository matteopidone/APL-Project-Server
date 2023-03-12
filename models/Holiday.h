#pragma once

#include <drogon/drogon.h>
#include <string>
#include <ctime>

using namespace std;

namespace models {
	class Holiday {
	private:
		string id_user;
		tm date;
		string type;
		string message;

	public:
		// Constructor
		Holiday();
		Holiday(string id_user, tm date, string type, string message);

		// Getters
		string getId_user() const;
		tm getDate() const;
		string getType() const;
		string getMessage() const;

		// Functions
		static Holiday * getUserHolidays(const string &email, int * size);
	};
}
