#include <string>

using namespace std;

//Costanti

//Costante secret jwt.
const string JWT_SECRET = "tokensecret";

//Costanti path url endpoint.
const string PATH_GET_HOLIDAYS = "/api/getHolidays?email={1}";
const string PATH_INSERT_HOLIDAYS = "/api/insertHoliday";
const string PATH_LOGIN = "/api/login";
const string PATH_INSERT_USER = "/api/insertUser";
const string PATH_UPDATE_REQUEST = "/api/updateRequest";
const string PATH_GET_ALL_USER_HOLIDAYS = "/api/getAllUserHolidays?email={1}";
