#include "api_v1_Controller_User.h"

using namespace api::v1;

void Controller_User::login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
	std::shared_ptr postArgs = req->getJsonObject();
	Json::Value parameters = *postArgs;

	std::string email = parameters["email"].asString();
	std::string password = parameters["password"].asString();

	// Check if the user exist into the database

	// Check the correctness of the password related

	// Get data and retrieve it to the user

	Json::Value result;
	result["username"] = "Jack";
	HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(result);
	resp->setStatusCode(k200OK);
	resp->addCookie("session", "1234567890");
	callback(resp);
}
