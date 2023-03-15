#pragma once

#include <drogon/HttpController.h>
#include "../models/User.h"

using namespace drogon;
using namespace std;

namespace api
{
class UserController : public drogon::HttpController<UserController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UserController::login, "/api/login", Post);
    METHOD_LIST_END

    void login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
}
