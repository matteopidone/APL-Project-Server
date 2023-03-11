#include "Holiday.h"

// Constructors
Holiday::Holiday(string id_user, tm date, string type) {
	this->id_user = id_user;
	this->date = date;
	this->type = type;
}

// Getters
string Holiday::getId_user() const { return this->id_user; }
tm Holiday::getDate() const { return this->date; }
string Holiday::getType() const { return this->type; }
