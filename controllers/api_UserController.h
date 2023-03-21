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
    ADD_METHOD_TO(UserController::updateHoliday, "/api/updateHoliday", Post);
    METHOD_LIST_END

    void login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateHoliday(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
}
