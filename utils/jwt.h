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
  private:
    string algoritm;
  public:
    string decode(const std::string &in);
    string encode(const std::string &in);
    bool verify_jwt(const std::string &jwt, const std::string &secret);
    string generate_jwt(const std::string &payload, const std::string &secret);
    JWT(const string &a){
      this->algoritm = a;
    };
};
}
