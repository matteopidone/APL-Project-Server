#include <drogon/drogon.h>
#include "models/Model.h"

int main() {
	// Set HTTP listener address and port
	// drogon::app().addListener("0.0.0.0",5000);

	// Load config file
	drogon::app().loadConfigFile("../config.json");

	// Run HTTP framework,the method will block in the internal event loop
	drogon::app().run();

	drogon::orm::DbClientPtr ptr = drogon::app().getDbClient("Matteo");
	models::Model::setDatabase(ptr);

	return 0;
}
