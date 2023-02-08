#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace demo
{
namespace v1
{
class other_controller : public drogon::HttpController<other_controller>
{
  public:
    METHOD_LIST_BEGIN
    METHOD_ADD(other_controller::getInfo, "/uno/{1}", Get);
    METHOD_ADD(other_controller::getInfo, "/due/{1}", Post);
    ADD_METHOD_TO(other_controller::getInfo, "/tre/{1}", Get);
    METHOD_LIST_END    
    
    void getInfo(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string param1);
};
}
}
