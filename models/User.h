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
			int role;
			enum AllowedRole {
  				User = 0,
  				Amdministrator = 1,
			};

		public:
			// Constructor
			User(string email, string password, string name, string surname, int role);

			// Getters
			string getEmail() const;
			string getPassword() const;
			string getName() const;
			string getSurname() const;
			string getRole() const;

			// Functions
			static void create(string email, string password, string name, string surname, int role);
			static bool find(const string &email, const string &password);
			static bool isAdministrator(const string &email);
			static string * get(const string &email);
	};
}
