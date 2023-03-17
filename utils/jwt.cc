#include "jwt.h"


using namespace aplutils;

string JWT::base64_encode(const std::string &in) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    bio = BIO_new(BIO_s_mem());
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    BIO_write(bio, in.c_str(), in.length());
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bufferPtr);
    std::string encoded(bufferPtr->data, bufferPtr->length);

    BIO_free_all(bio);
    return encoded;
}

//Funzione per la decodifica Base64
string JWT::base64_decode(const std::string &in) {
    BIO *bio, *b64;
    char *buffer = (char *)calloc(in.length(), sizeof(char));

    bio = BIO_new_mem_buf(in.c_str(), -1);
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    BIO_read(bio, buffer, in.length());

    BIO_free_all(bio);

    string decoded(buffer);
    free(buffer);
    return decoded;
}

//Funzione per generare il JWT
string JWT::generate_jwt(const std::string &header, const std::string &payload, const std::string &secret) {
    std::string encoded_header = base64_encode(header);
    std::string encoded_payload = base64_encode(payload);

    std::string data = encoded_header + "." + encoded_payload;

    unsigned char* hmac = HMAC(EVP_sha256(), secret.c_str(), secret.size(), (const unsigned char*)data.c_str(), data.size(), NULL, NULL);
    std::string signature((char*)hmac, 32);
    std::string encoded_signature = base64_encode(signature);

    std::string jwt = data + "." + encoded_signature;

    return jwt;
}

//Funzione per verificare il JWT
bool JWT::verify_jwt(const std::string &jwt, const std::string &secret) {
    size_t pos1 = jwt.find(".");
    if (pos1 == std::string::npos) return false;
    std::string encoded_header = jwt.substr(0, pos1);

    size_t pos2 = jwt.find(".", pos1+1);
    if (pos2 == std::string::npos) return false;
    std::string encoded_payload = jwt.substr(pos1+1, pos2-pos1-1);

    std::string encoded_signature = jwt.substr(pos2+1);

    std::string data = encoded_header + "." + encoded_payload;

    unsigned char* hmac = HMAC(EVP_sha256(), secret.c_str(), secret.size(), (const unsigned char*)data.c_str(), data.size(), NULL, NULL);
    std::string signature((char*)hmac, 32);
    std::string expected_signature = base64_encode(signature);

    return expected_signature == encoded_signature;
}