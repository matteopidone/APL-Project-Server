#pragma once

#include <drogon/drogon.h>

using namespace drogon;

class Holiday {
   private:
	std::string id_user;
	std::tm date;
	std::string type;

   public:
	// Constructor
	Holiday(std::string id_user, std::tm date, std::string type);

	// Getters
	std::string getId_user() const;
	std::tm getDate() const;
	std::string getType() const;
};
