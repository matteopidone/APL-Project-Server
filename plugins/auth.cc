#include "auth.h"
#include <regex>

using namespace aplutils;

bool Auth::validate_token( string &auth_header, const string &secret ) {

    if (auth_header.empty()) {
		return false;
    }

	const string bearerPrefix = "Bearer ";
	if (auth_header.find(bearerPrefix) == 0) {
		auth_header = auth_header.substr(bearerPrefix.length());
	}

	if( !jwtobj.verify_jwt(auth_header, secret) ){
		return false;
	}

	return true;
}

string Auth::generate_token(const Json::Value &json, const string &secret ){
    //StreamWriterBuilder per convertire da json a stringa
    Json::StreamWriterBuilder builder;
    
    string payload = Json::writeString(builder, json);
    string encoded_payload = jwtobj.encode(payload);
    string jwt = jwtobj.generate_jwt(encoded_payload, secret);
    return jwt;
}

bool Auth::validate_email( const string &email ){
    const regex email_regex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return regex_match(email, email_regex);
}
//Funzione che dato un tempo, ritorna un booleano che indica se la data è valida per una richiesta, in particolare
//è valida se: è successiva alla data di oggi e non è sabato e domenica.
bool Auth::is_valid_day(tm time){
    time_t now = std::time(nullptr);
    tm* now_tm = localtime(&now);
    
    char weekday[3];
    strftime(weekday, 3, "%w", &time);
    
    if (difftime(mktime(&time), mktime(now_tm)) > 0 && weekday[0] != '0' && weekday[0] != '6') {
        return true;
    } else {
        return false;
    }
}

void Auth::parse_tm(const int &day, const int &month, const int &year, tm &time){
    string string_date = to_string(year) + "-" + to_string(month) + "-" + to_string(day);
	strptime(string_date.c_str(), "%Y-%m-%d", &time);
}