#pragma once

#include <string>
#include <ctime>

using namespace std;

class Holiday {
   private:
	string id_user;
	tm date;
	string type;

   public:
	// Constructor
	Holiday(string id_user, tm date, string type);

	// Getters
	string getId_user() const;
	tm getDate() const;
	string getType() const;
};
