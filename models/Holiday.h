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
		enum AllowedHolidayType {
  			Pending = 0,
  			Accepted = 1,
  			Refused = 2
		};

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
		static Holiday * getAllUserHolidays(const string email, int &size);
		static bool insertUserHoliday(const string email, const tm date, const string message = "");
		static bool isAlreadyRequested(const string email, const tm date);
		static bool updateUserHoliday(const string email, const tm date, const int type);
		static bool isValidTypeHoliday(const int value);
	};
}
