#pragma once

#include <drogon/HttpController.h>
#include "../models/User.h"
#include "../plugins/jwt.h"
#include <iostream>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>

using namespace drogon;
using namespace std;
using namespace aplutils;

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
