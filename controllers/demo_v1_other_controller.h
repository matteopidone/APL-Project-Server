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
    METHOD_ADD(other_controller::getInfo, "/{1}", Get);
    METHOD_LIST_END    
    
    void getInfo(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string param1);
};
}
}
