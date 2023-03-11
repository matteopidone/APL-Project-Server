#pragma once

#include <drogon/drogon.h>

using namespace drogon;

class User {
   private:
	std::string email;
	std::string password;
	std::string name;
	std::string surname;
	std::string role;

   public:
	// Constructor
	User(std::string email, std::string password, std::string name, std::string surname, std::string role);

	// Getters
	std::string getEmail() const;
	std::string getPassword() const;
	std::string getName() const;
	std::string getSurname() const;
	std::string getRole() const;
};
