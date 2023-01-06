#include "demo_v1_other_controller.h"

using namespace demo::v1;

void other_controller::getInfo(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string param1)
{
    Json::Value body;
    body["key0"] = "You are using other_controller";
    body["key1"] = "Hello World !";
    body["key2"] = param1;

    auto resp=HttpResponse::newHttpJsonResponse(body);
    callback(resp);
}