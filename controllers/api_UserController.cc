#include "api_UserController.h"

using namespace api;

void UserController::insertUser(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback){
    HttpResponsePtr resp;
    Json::Value result;
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
    string description = parameters["description"].asString();
    string role = parameters["role"].asString();

    if( !validate_email(email) ){
        //Se la mail non è valida rispondo con status code 400.
		result["error"] = "Invalid email.";
		resp = HttpResponse::newHttpJsonResponse(result);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;

    }

    try {
        bool inserted = models::User::create(email, psw, name, surname, description, role);

        //Se l'utente non è stato inserito rispondo con status code 400.
        if( !inserted ){
            result["error"] = "User not inserted.";
		    resp = HttpResponse::newHttpJsonResponse(result);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }

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
    Json::Value result;

    try {
        // Prendo i parametri della richiesta.
        Json::Value parameters = *(req->getJsonObject());
        string email = parameters["email"].asString();

        if( !validate_email(email) ){
            //Se la mail non è valida rispondo con status code 400.
		    result["error"] = "Invalid email.";
		    resp = HttpResponse::newHttpJsonResponse(result);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;

        }

        string password = parameters["password"].asString();

        bool found = models::User::find(email, password);

        if( ! found ) {
            //Se non trovo l'utente rispondo con status code 400.
            result["error"] = "User not found.";
		    resp = HttpResponse::newHttpJsonResponse(result);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }

        result["found"] = found;

        string * user_info = models::User::getUserInfo(email);

        result["name"] = user_info[0];
        result["surname"] = user_info[1];
        result["email"] = email;
        result["description"] = user_info[2];

        // Genero un JWT.
        string jwt = generate_token(parameters, JWT_SECRET);
        result["token"] = jwt;

        // Elimino la memoria allocata.
        delete[] user_info;
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

void UserController::updateRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    HttpResponsePtr resp;
    Json::Value result;
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
        result["error"] = "Invalid email.";
        resp = HttpResponse::newHttpJsonResponse(result);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    tm date = {};
    // Metodo implementato per tornare la data in formato struct tm.
    parse_tm(day, month, year, date);

    try {
        if( models::Holiday::isAlreadyRequested(email, date) && models::Holiday::isValidTypeHoliday(type) ){
            bool updated = models::Holiday::updateUserHoliday(email, date, type);

            //Se la richiesta non viene aggiornata rispondo con status code 400.
            if( !updated ){
                result["error"] = "Request has not been updated.";
                resp = HttpResponse::newHttpJsonResponse(result);
                resp->setStatusCode(k400BadRequest);
                callback(resp);
                return;
            }

            result["updated"] = updated;
            resp = HttpResponse::newHttpJsonResponse(result);
            resp->setStatusCode(k200OK);
            callback(resp);
            return;
        }

        //Se la richiesta non è consistente rispondo con status code 400.
        result["error"] = "Holidays is already requested or is not a valid type.";
        resp = HttpResponse::newHttpJsonResponse(result);
        resp->setStatusCode(k400BadRequest);
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

void UserController::getAllUserHolidays(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const string email) {
    HttpResponsePtr resp;
    Json::Value result;
    try {
        string auth_field = req->getHeader("Authorization");

        // Metodo ereditato da Utility.
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
            result["error"] = "Invalid mail or email is not from an administrator.";
            resp = HttpResponse::newHttpJsonResponse(result);
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
            result[i]["description"] = arrayUsers[i].getDescription();

            int size_holiday;
            //Prendo tutte le richieste dell'utente.
            models::Holiday * arrayHoliday = models::Holiday::getAllUserHolidays(mail, size_holiday);
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

        resp = HttpResponse::newHttpJsonResponse(result);
        resp->setStatusCode(k200OK);
        callback(resp);
        return;

    } catch ( const exception &exception ) {
        //Rispondo con status code 500.
        std::cout << exception.what() << endl;
        resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
        return;
    }

}
