#include "main_controller.h"

void main_controller::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    Json::Value json;
    json["key1.1"] = "value1";
    json["key1.2"] = 15;
    
    Json::Value body;
    body["key0"] = "You are using main_controller";
    body["key1"] = "Hello World !";
    body["key2"] = json;

    auto resp=HttpResponse::newHttpJsonResponse(body);
    callback(resp);
}