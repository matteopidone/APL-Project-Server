#pragma once

#include <drogon/HttpController.h>
#include "../models/Holiday.h"
#include "../plugins/jwt.h"

using namespace drogon;
using namespace std;
using namespace aplutils;

namespace api {
	class HolidayController : public drogon::HttpController<HolidayController> {
		public:
			METHOD_LIST_BEGIN
			ADD_METHOD_TO(HolidayController::getHolidays, "/api/getHolidays?email={1}", Get);
			ADD_METHOD_TO(HolidayController::insertHoliday, "/api/insertHoliday", Post);
			METHOD_LIST_END

		void getHolidays(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const string email);
		void insertHoliday(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
	};
}
