#include "api_HolidayController.h"

using namespace api;

void HolidayController::getHolidays(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const string email) {
	Json::Value result;
	JWT jwtobj("HS256");
	const string secret = "mysecret";
	
	string token = req->getHeader("Authorization");
    if (token.empty()) {
		// Se non è vlaorizzato restituisco una risposta di errore.
		HttpResponsePtr resp = HttpResponse::newHttpResponse();
		resp->setStatusCode(HttpStatusCode::k401Unauthorized);
		callback(resp);
		return;
    }

	const string bearerPrefix = "Bearer ";
	if (token.find(bearerPrefix) == 0) {
		token = token.substr(bearerPrefix.length());
	}

	if( !jwtobj.verify_jwt(token, secret) ){
		// Se non è valido restituisco una risposta di errore.
		HttpResponsePtr resp = HttpResponse::newHttpResponse();
		resp->setStatusCode(HttpStatusCode::k401Unauthorized);
		callback(resp);
		return;
	}	

	int size;
	models::Holiday * values = models::Holiday::getUserHolidays(email, &size);

	if (!size) {
		result["response"] = "Nessuna ferie presente";
		HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(result);
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

	HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(result);
	resp->setStatusCode(k200OK);
	callback(resp);
	delete[] values;
}

void HolidayController::insertHoliday(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
	// Verifica del token di autenticazione.
	JWT jwtobj("HS256");
	const string secret = "mysecret";
	
	string token = req->getHeader("Authorization");
    if (token.empty()) {
		// Se non è valorizzato restituisco una risposta di errore.
		HttpResponsePtr resp = HttpResponse::newHttpResponse();
		resp->setStatusCode(HttpStatusCode::k401Unauthorized);
		callback(resp);
		return;
    }

	const string bearerPrefix = "Bearer ";
	if (token.find(bearerPrefix) == 0) {
		token = token.substr(bearerPrefix.length());
	}

	if( !jwtobj.verify_jwt(token, secret) ){
		// Se non è valido restituisco una risposta di errore.
		HttpResponsePtr resp = HttpResponse::newHttpResponse();
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

	tm date = {};
	string string_date = to_string(year) + "-" + to_string(month) + "-" + to_string(day);
	strptime(string_date.c_str(), "%Y-%m-%d", &date);

	bool res = models::Holiday::insertUserHoliday(email, date, message);

	Json::Value result;
	result["result"] = res;

	if (!res) {
		result["response"] = "Non è possibile creare la richiesta di ferie";
		HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(result);
		resp->setStatusCode(k500InternalServerError);
		callback(resp);
		return;
	}

	HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(result);
	resp->setStatusCode(k200OK);
	callback(resp);
}
