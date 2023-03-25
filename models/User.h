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
			string description;
			string role;
			enum AllowedRole {
  				Dependent = 0,
  				Administrator = 1,
			};

		public:
			// Constructor
			User();
			User(const string email, const string password, const string name, const string surname, const string description, const string role);

			// Getters
			string getEmail() const;
			string getPassword() const;
			string getName() const;
			string getSurname() const;
			string getDescription() const;
			string getRole() const;

			// Functions
			static bool create(const string email, const string password, const string name, const string surname, const string description, const string role);
			static bool find(const string email, const string password);
			static bool isAdministrator(const string email);
			static User * getAllUsers(int &size);
			static string * getUserInfo(const string email);
	};
}
