#pragma once

#include <string>
#include "Model.h"

using namespace std;

namespace models {
	class User : public Model {
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

			// Functions
			static void create(string email, string password, string name, string surname, string role);
			static bool find(const string &email, const string &password);
			static string * get(const string &email);
	};
}
