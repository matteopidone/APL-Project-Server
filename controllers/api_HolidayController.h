#pragma once

#include <drogon/HttpController.h>
#include "../models/Holiday.h"

using namespace drogon;
using namespace std;

namespace api {
	class HolidayController : public drogon::HttpController<HolidayController> {
		public:
			METHOD_LIST_BEGIN
			ADD_METHOD_TO(HolidayController::getHolidays, "/api/getHolidays", Post);
			METHOD_LIST_END

		void getHolidays(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
	};
}
