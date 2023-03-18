#include "jwt.h"


using namespace aplutils;

string JWT::encode(const string &in) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    bio = BIO_new(BIO_s_mem());
    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_push(b64, bio);

    BIO_write(bio, in.c_str(), in.length());
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bufferPtr);
    string encoded(bufferPtr->data, bufferPtr->length);

    BIO_free_all(bio);
    return encoded;
}

//Funzione per la decodifica Base64
string JWT::decode(const string &in) {
    BIO *bio, *b64;
    char *buffer = (char *)calloc(in.length(), sizeof(char));

    bio = BIO_new_mem_buf(in.c_str(), -1);
    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_push(b64, bio);

    BIO_read(bio, buffer, in.length());

    BIO_free_all(bio);

    string decoded(buffer);
    free(buffer);
    return decoded;
}

//Funzione per generare il JWT
string JWT::generate_jwt(const string &payload, const string &secret) {
    string encoded_header = this->encode("{\"alg\":\"HS256\",\"typ\":\"" + this->algoritm + "\"}");
    string data = encoded_header + "." + payload;

    unsigned char* hmac = HMAC(EVP_sha256(), secret.c_str(), secret.size(), (const unsigned char*)data.c_str(), data.size(), NULL, NULL);
    string signature((char*)hmac, 32);
    string encoded_signature = this->encode(signature);

    string jwt = data + "." + encoded_signature;

    return jwt;
}

//Funzione per verificare il JWT
bool JWT::verify_jwt(const string &jwt, const string &secret) {
    size_t pos1 = jwt.find(".");
    if (pos1 == std::string::npos) return false;
    string encoded_header = jwt.substr(0, pos1);

    size_t pos2 = jwt.find(".", pos1+1);
    if (pos2 == string::npos) return false;
    string encoded_payload = jwt.substr(pos1+1, pos2-pos1-1);

    string encoded_signature = jwt.substr(pos2+1);

    string data = encoded_header + "." + encoded_payload;

    unsigned char* hmac = HMAC(EVP_sha256(), secret.c_str(), secret.size(), (const unsigned char*)data.c_str(), data.size(), NULL, NULL);
    string signature((char*)hmac, 32);
    string expected_signature = this->encode(signature);

    return expected_signature == encoded_signature;
}