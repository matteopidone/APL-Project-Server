#include "Holiday.h"

// Constructors
Holiday::Holiday(std::string id_user, std::tm date, std::string type) {
	this->id_user = id_user;
	this->date = date;
	this->type = type;
}

// Getters
std::string Holiday::getId_user() const { return this->id_user; }
std::tm Holiday::getDate() const { return this->date; }
std::string Holiday::getType() const { return this->type; }
