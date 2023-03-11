#include "Model.h"

using namespace models;

// Setters
void Model::setDatabase(orm::DbClientPtr & db) {
	database = db;
}

// Getters
orm::DbClientPtr Model::getDatabase() {
	return database;
}
