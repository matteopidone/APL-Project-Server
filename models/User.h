#pragma once

#include <drogon/drogon.h>
#include <string>

using namespace std;

namespace models {
	class User {
		private:
			string email;
			string password;
			string name;
			string surname;
			string role;
			enum AllowedRole {
  				Dependent = 0,
  				Amdministrator = 1,
			};

		public:
			// Constructor
			User();
			User(string email, string password, string name, string surname, string role);

			// Getters
			string getEmail() const;
			string getPassword() const;
			string getName() const;
			string getSurname() const;
			string getRole() const;

			// Functions
			static bool create(const string &email, const string &password, const string &name, const string &surname, const string &role);
			static bool find(const string &email, const string &password);
			static bool isAdministrator(const string &email);
			static User * getAllUsers(int &size);
			static string * get(const string &email);
	};
}
