#include "api_UserController.h"

using namespace api;

void UserController::insertUser(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback){
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
    string psw = parameters["password"].asString();
    string name = parameters["name"].asString();
    string surname = parameters["surname"].asString();
    string role = parameters["role"].asString();
    
    if( !validate_email(email) ){
        //Se la mail non è valida rispondo con status code 400.
        resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);     
        callback(resp);
        return;

    }

    Json::Value result;
    try {
        bool inserted = models::User::create(email, psw, name, surname, role);
        result["inserted"] = inserted;
        resp = HttpResponse::newHttpJsonResponse(result);
        resp->setStatusCode(k200OK);
        callback(resp);
        return;
    } catch (const exception &exception) {
        //Rispondo con status code 500.
        resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
        return;
    }    
}

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

void UserController::getAllUserHolidays(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const string &email) {
    HttpResponsePtr resp;
    Json::Value result;
    try {
        string auth_field = req->getHeader("Authorization");

        // Metodo ereditato da Auth.
        if ( !validate_token(auth_field, JWT_SECRET) ) {
            // Se non è valido restituisco una risposta di errore.
            resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(HttpStatusCode::k401Unauthorized);
            callback(resp);
            return;
        }
        // Controllo che la mail sia valida e che l'utente sia un amministratore;
        if( !validate_email(email) || !models::User::isAdministrator(email) ){
            //Rispondo con status code 400.
            resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }

        int size_user;
        models::User * arrayUsers = models::User::getAllUsers(size_user);
        if (!size_user) {
            resp = HttpResponse::newHttpJsonResponse(result);
            resp->setStatusCode(k200OK);
            callback(resp);
            return;
        }

        tm date;
        for (int i = 0; i < size_user; i++) {
            string mail = arrayUsers[i].getEmail();
            result[i]["email"] = mail;
            result[i]["name"] = arrayUsers[i].getName();
            result[i]["surname"] = arrayUsers[i].getSurname();

            int size_holiday;
            //Prendo tutte le richieste dell'utente.
            models::Holiday * arrayHoliday = models::Holiday::getAllUserHolidays(mail, &size_holiday);
            if( !size_holiday ) {
                //Se l'utente non ha fatto nessuna richiesta inserisco un'array di richieste vuoto.
                result[i]["holidays"] = Json::arrayValue;
                continue;
            }
            for( int j = 0; j < size_holiday; j++ ) {
                date = arrayHoliday[j].getDate();
                result[i]["holidays"][j]["year"] = date.tm_year;
                result[i]["holidays"][j]["month"] = date.tm_mon;
                result[i]["holidays"][j]["day"] = date.tm_mday;
                result[i]["holidays"][j]["type"] = arrayHoliday[j].getType();
                result[i]["holidays"][j]["message"] = arrayHoliday[j].getMessage();

            }
            delete[] arrayHoliday;
        }
        delete[] arrayUsers;
    } catch ( const exception &exception ) {
        //Rispondo con status code 500.
        std::cout << exception.what() << endl;
        resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
        return;
    }

	resp = HttpResponse::newHttpJsonResponse(result);
	resp->setStatusCode(k200OK);
	callback(resp);
    return;
}