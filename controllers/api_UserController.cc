#include "api_UserController.h"

using namespace api;

void UserController::login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    try {
        JWT jwtobj;
        Json::Value parameters = *(req->getJsonObject());
        string email = parameters["email"].asString();
        string password = parameters["password"].asString();
        Json::Value result;
        string payload = "{\"sub\":\"1234567890\",\"name\":\"John Doe\",\"iat\":1516239022}";
        string secret = "mysecret";

        string encoded_header = jwtobj.base64_encode("{\"alg\":\"HS256\",\"typ\":\"JWT\"}");
        string encoded_payload = jwtobj.base64_encode(payload);

        string jwt = jwtobj.generate_jwt(encoded_header, encoded_payload, "mysecret");

        std::cout << "Token JWT: " << jwt << std::endl;

        bool found = models::User::find(email, password);
        result["found"] = found;
        if( found ) {
            string * user = models::User::get(email);
            result["found"] = "true";
            result["name"] = user[0];
            result["surname"] = user[1];
            result["email"] = email;
        }
        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(result);
        resp->setStatusCode(k200OK);
        resp->addCookie("session", "1234567890");
        callback(resp);
        //Delete
        return;
    } catch (string exception) {
        std::cout << "Errore: " << exception << std::endl;
    }
}
