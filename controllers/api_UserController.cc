#include "api_UserController.h"

using namespace api;

void UserController::login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    try {
        Json::Value parameters = *(req->getJsonObject());
        string email = parameters["email"].asString();
        string password = parameters["password"].asString();
        Json::Value result;

        bool found = models::User::find(email, password);
        result["found"] = found;
        if( found ) {
            string * user = models::User::get(email);
            result["name"] = user[0];
            result["surname"] = user[1];
            result["email"] = email;

            //Genero un JWT
            string jwt = generate_token(parameters, JWT_SECRET);
            result["token"] = jwt;
        }
        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(result);
        resp->setStatusCode(k200OK);
        callback(resp);
        //Delete
        return;
    } catch (string exception) {
        std::cout << "Errore: " << exception << std::endl;
    }
}
