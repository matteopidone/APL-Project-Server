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