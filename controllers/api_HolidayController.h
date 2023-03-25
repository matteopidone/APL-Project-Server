#pragma once

#include <drogon/HttpController.h>
#include "../models/Holiday.h"
#include "../plugins/utility.h"

using namespace drogon;
using namespace std;
using namespace aplutils;

namespace api {
	class HolidayController : public drogon::HttpController<HolidayController>, public Utility {
		public:
			METHOD_LIST_BEGIN
			ADD_METHOD_TO(HolidayController::getHolidays, PATH_GET_HOLIDAYS, Get);
			ADD_METHOD_TO(HolidayController::insertHoliday, PATH_INSERT_HOLIDAYS, Post);
			METHOD_LIST_END

			void getHolidays(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const string email);
			void insertHoliday(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);			
	};
}
