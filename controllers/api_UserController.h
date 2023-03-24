#pragma once

#include <drogon/HttpController.h>
#include "../models/User.h"
#include "../models/Holiday.h"
#include "../plugins/auth.h"

using namespace drogon;
using namespace std;
using namespace aplutils;

namespace api
{
class UserController : public drogon::HttpController<UserController>, public Auth
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UserController::login, "/api/login", Post);
    ADD_METHOD_TO(UserController::insertUser, "/api/insertUser", Post);
    ADD_METHOD_TO(UserController::updateRequest, "/api/updateRequest", Post);
    ADD_METHOD_TO(UserController::getAllUserHolidays, "/api/getAllUserHolidays?email={1}", Get);
    METHOD_LIST_END

    void login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getAllUserHolidays(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const string &email);
    void insertUser(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
}
