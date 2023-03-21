#include "api_UserController.h"

using namespace api;

void UserController::login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    HttpResponsePtr resp;
    try {
        // Prendo i parametri della richiesta.
        Json::Value parameters = *(req->getJsonObject());
        string email = parameters["email"].asString();
        if( !validate_email(email) ){
            //Se la mail non è valida rispondo con status code 400.
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

                // Genero un JWT.
                string jwt = generate_token(parameters, JWT_SECRET);
                result["token"] = jwt;

                // Elimino la memoria allocata.
                delete[] user;
            }
            resp = HttpResponse::newHttpJsonResponse(result);
            resp->setStatusCode(k200OK);
        }

    } catch (const exception &exception) {
        //Rispondo con status code 500.
        resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
    }
    
    callback(resp);
    return;
}

void UserController::updateRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    HttpResponsePtr resp;
    string auth_field = req->getHeader("Authorization");

    if (!validate_token(auth_field, JWT_SECRET)) {
		// Se non è valido rispondo con codice 401.
		resp = HttpResponse::newHttpResponse();
		resp->setStatusCode(HttpStatusCode::k401Unauthorized);
		callback(resp);
		return;
    }

    // Prendo i parametri della richiesta.
    Json::Value parameters = *(req->getJsonObject());
    string email = parameters["email"].asString();
    int year = parameters["year"].asInt();
    int month = parameters["month"].asInt();
    int day = parameters["day"].asInt();
    int type = parameters["type"].asInt();
    
    if( !validate_email(email) ){
        //Se la mail non è valida rispondo con status code 400.
        resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);     
        callback(resp);
        return;

    }
    tm date = {};
    // Metodo implementato per tornare la data in formato struct tm.
    parse_tm(day, month, year, date);

    Json::Value result;

    try {

        if( models::Holiday::isAlreadyRequested(email, date) && models::Holiday::isValidTypeHoliday(type) ){
            bool updated = models::Holiday::updateUserHoliday(email, date, type);
            result["updated"] = updated;
            resp = HttpResponse::newHttpJsonResponse(result);
            resp->setStatusCode(k200OK);
            callback(resp);
            return;
        }
    } catch (const exception &exception) {
        //Rispondo con status code 500.
        resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
        return;
    }

    //Se la richiesta non è consistente rispondo con status code 400.
    resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k400BadRequest);
    callback(resp);
    return;
}