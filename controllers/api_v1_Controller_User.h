#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace api {
namespace v1 {
class Controller_User : public drogon::HttpController<Controller_User> {
   public:
	METHOD_LIST_BEGIN
	METHOD_ADD(Controller_User::login, "login", Post);
	METHOD_LIST_END

	void login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
}  // namespace v1
}  // namespace api
