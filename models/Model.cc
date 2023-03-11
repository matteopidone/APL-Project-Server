#include "Model.h"

using namespace models;

// Constructor
Model::Model() {
	// The name is specified inside config.json
	this->database = app().getDbClient("Matteo");
}

// Getters
orm::DbClientPtr Model::getDatabase() const { return this->database; }
