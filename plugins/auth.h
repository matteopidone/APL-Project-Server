#include <json/json.h>
#include <string>
#include "jwt.h"
#include "constants.h"

using namespace std;

namespace aplutils
{
class Auth
{
  private:
    JWT jwtobj = JWT("HS256");

  protected:
    bool validate_token(string &auth_header, const string &secret);
    string generate_token(const Json::Value &json, const string &secret );
};
}