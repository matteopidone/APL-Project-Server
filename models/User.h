#pragma once

#include <string>

using namespace std;

class User {
   private:
	string email;
	string password;
	string name;
	string surname;
	string role;

   public:
	// Constructor
	User(string email, string password, string name, string surname, string role);

	// Getters
	string getEmail() const;
	string getPassword() const;
	string getName() const;
	string getSurname() const;
	string getRole() const;
};
