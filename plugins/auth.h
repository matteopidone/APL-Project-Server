//#include <iostream>
#include <json/json.h>
#include <string>
#include "jwt.h"

using namespace std;

namespace aplutils
{
class Auth
{

  protected:
	bool validate_token(string &auth_header, const string &secret);
    string generate_token(const Json::Value &json, const string &secret );
};
}