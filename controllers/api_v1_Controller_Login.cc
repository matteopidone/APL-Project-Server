#include "api_v1_Controller_Login.h"

using namespace api::v1;

void Controller_Login::login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
	std::shared_ptr postArgs = req->getJsonObject();
	Json::Value parameters = *postArgs;

	std::string email = parameters["email"].asString();
	std::string password = parameters["password"].asString();

	Json::Value ret;
	ret["result"] = "ok";
	HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(ret);
	callback(resp);
}
