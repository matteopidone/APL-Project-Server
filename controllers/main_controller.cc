#include "main_controller.h"

void main_controller::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto resp=HttpResponse::newHttpResponse();
    auto clientPtr = drogon::app().getDbClient("Matteo");
    auto f = clientPtr->execSqlAsyncFuture("select * from users");
    auto result = f.get(); // Block until we get the result or catch the exception;
    int i = 0;
    for (auto row : result)
    {
     i++;;
    };
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_HTML);
    resp->setBody("value is " + i);
    callback(resp);
}
