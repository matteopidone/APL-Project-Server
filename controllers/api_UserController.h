#pragma once

#include <drogon/HttpController.h>
#include "../models/User.h"
#include "../models/Holiday.h"
#include "../plugins/utility.h"

using namespace drogon;
using namespace std;
using namespace aplutils;

namespace api {
	class UserController : public drogon::HttpController<UserController>, public Utility {
		public:
			METHOD_LIST_BEGIN
			ADD_METHOD_TO(UserController::login, PATH_LOGIN, Post);
			ADD_METHOD_TO(UserController::insertUser, PATH_INSERT_USER, Post);
			ADD_METHOD_TO(UserController::updateRequest, PATH_UPDATE_REQUEST, Post);
			ADD_METHOD_TO(UserController::getAllUserHolidays, PATH_GET_ALL_USER_HOLIDAYS, Get);
			METHOD_LIST_END

			void login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
			void insertUser(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
			void updateRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
			void getAllUserHolidays(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const string email);
	};
}
