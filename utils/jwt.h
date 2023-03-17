#include <iostream>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>
#include <string>

namespace aplutils
{
class JWT
{
  public:
    string base64_decode(const std::string &in);
    string base64_encode(const std::string &in);
    bool verify_jwt(const std::string &jwt, const std::string &secret);
    string generate_jwt(const std::string &header, const std::string &payload, const std::string &secret);
};
}
