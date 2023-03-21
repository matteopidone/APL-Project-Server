#include "api_HolidayController.h"

using namespace api;

void HolidayController::getHolidays(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const string email) {
	//Ma sta nello stack?
	Json::Value result;
	HttpResponsePtr resp;
	
	string auth_field = req->getHeader("Authorization");

	// Metodo ereditato da Auth.
    if ( !validate_token(auth_field, JWT_SECRET) ) {
		// Se non è valido restituisco una risposta di errore.
		resp = HttpResponse::newHttpResponse();
		resp->setStatusCode(HttpStatusCode::k401Unauthorized);
		callback(resp);
		return;
    }
	
	if( !validate_email(email) ){
		//Se la mail non è valida rispondo con status code 400.
		resp = HttpResponse::newHttpResponse();
		resp->setStatusCode(k400BadRequest);
		callback(resp);
		return;
	}

	int size;
	models::Holiday * values = models::Holiday::getAllUserHolidays(email, &size);

	if (!size) {
		resp = HttpResponse::newHttpJsonResponse(result);
		resp->setStatusCode(k200OK);
		callback(resp);
		return;
	}

	tm date;
	for (int i = 0; i < size; i++) {
		date = values[i].getDate();
		result[i]["year"] = date.tm_year;
		result[i]["month"] = date.tm_mon;
		result[i]["day"] = date.tm_mday;
		result[i]["type"] = values[i].getType();
		result[i]["message"] = values[i].getMessage();
	}

	delete[] values;
	resp = HttpResponse::newHttpJsonResponse(result);
	resp->setStatusCode(k200OK);
	callback(resp);
}

void HolidayController::insertHoliday(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
	HttpResponsePtr resp;
	string auth_field = req->getHeader("Authorization");

    if (!validate_token(auth_field, JWT_SECRET)) {
		// Se non è valido restituisco una risposta di errore.
		resp = HttpResponse::newHttpResponse();
		resp->setStatusCode(HttpStatusCode::k401Unauthorized);
		callback(resp);
		return;
    }

	Json::Value parameters = *(req->getJsonObject());
	string email = parameters["email"].asString();
	int year = parameters["year"].asInt();
	int month = parameters["month"].asInt();
	int day = parameters["day"].asInt();
	string message = parameters["message"].asString();

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

	if( models::Holiday::isAlreadyRequested(email, date) || !is_valid_day(date) ){
		//Se è stata già inoltrata una richiesta per questa data, ritorno risposta con codice 400.
		resp = HttpResponse::newHttpResponse();
		resp->setStatusCode(k400BadRequest);
		callback(resp);
		return;
	}

	bool res = models::Holiday::insertUserHoliday(email, date, message);

	Json::Value result;
	result["result"] = res;

	if (!res) {
		result["response"] = "Non è possibile creare la richiesta di ferie";
		resp = HttpResponse::newHttpJsonResponse(result);
		resp->setStatusCode(k500InternalServerError);
		callback(resp);
		return;
	}

	resp = HttpResponse::newHttpJsonResponse(result);
	resp->setStatusCode(k200OK);
	callback(resp);
}
