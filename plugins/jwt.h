#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>
#include <string>

using namespace std;

namespace aplutils {
	/*
	* Questa classe implementa metodi per la costruzione e validazione di un Json Web Token.
	*/
	class JWT {
		private:
			string algorithm;

		public:
			// Constructor
			JWT(const string a) {
				this->algorithm = a;
			};

			// Functions
			string decode(const string in);
			string encode(const string in);
			bool verify_jwt(const string jwt, const string secret);
			string generate_jwt(const string payload, const string secret);
	};
}
