#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class main_controller : public drogon::HttpSimpleController<main_controller>
{
  public:
    void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    PATH_ADD("/",Get,Post);
    PATH_ADD("/test",Get);
    PATH_LIST_END
};
