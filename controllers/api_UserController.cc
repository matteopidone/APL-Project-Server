#include "api_UserController.h"

using namespace api;

void UserController::login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    HttpResponsePtr resp;
    try {
        // Prendo i parametri della richiesta.
        Json::Value parameters = *(req->getJsonObject());
        string email = parameters["email"].asString();
        if( !validate_email(email) ){
            resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k400BadRequest);

        } else {

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
                delete[] user;
            }
            resp = HttpResponse::newHttpJsonResponse(result);
            resp->setStatusCode(k200OK);
        }

    } catch (const exception &exception) {
        resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
    }
    
    callback(resp);
    return;
}
