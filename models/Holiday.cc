#include <drogon/drogon.h>

using namespace drogon;

class Holiday {
   private:
	std::string id_user;
	std::tm date;
	std::string type;

   public:
	// Constructor
	Holiday(std::string id_user, std::tm date, std::string type) {
		this->id_user = id_user;
		this->date = date;
		this->type = type;
	}

	// Getters
	std::string getId_user() const { return this->id_user; }
	std::tm getDate() const { return this->date; }
	std::string getType() const { return this->type; }
};
