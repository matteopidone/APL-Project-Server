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
			static string * get(const string &email);
	};
}
