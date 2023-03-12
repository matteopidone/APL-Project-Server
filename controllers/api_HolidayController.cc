#include "api_HolidayController.h"

using namespace api;

void HolidayController::getHolidays(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const string email) {
	Json::Value result;

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
