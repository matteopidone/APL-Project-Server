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
		int type;
		string message;

	public:
		// Constructor
		Holiday();
		Holiday(const string id_user, const tm date, const int type, const string message);

		// Getters
		string getId_user() const;
		tm getDate() const;
		int getType() const;
		string getMessage() const;

		// Functions
		static Holiday * getUserHolidays(const string email, int * size);
		static bool insertUserHoliday(const string email, const tm date, const string message = "");
	};
}
