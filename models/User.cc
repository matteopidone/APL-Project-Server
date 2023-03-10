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
	User(std::string email, std::string password, std::string name, std::string surname, std::string role) {
		this->email = email;
		this->password = password;
		this->name = name;
		this->surname = surname;
		this->role = role;
	}

	// Getters
	std::string getEmail() const { return this->email; }
	std::string getPassword() const { return this->password; }
	std::string getName() const { return this->name; }
	std::string getSurname() const { return this->surname; }
	std::string getRole() const { return this->role; }
};
