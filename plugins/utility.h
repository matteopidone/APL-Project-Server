#include <json/json.h>
#include <string>
#include "jwt.h"
#include "constants.h"

using namespace std;

namespace aplutils {
	/**
	 * Questa classe definisce vari metodi di utility:
	 * - Generazione di un json web token
	 * - Validazione del token
	 * - Validazione email
	 * - Validazione giorno (per richiesta ferie)
	 * - Conversione giorno, mese, anno a tipo std::tm
	*/
	class Utility {
		private:
			JWT jwtobj = JWT("HS256");

		protected:
			// Functions
			string generate_token(const Json::Value &json, const string secret);
			bool validate_token(string auth_header, const string secret);
			bool validate_email(const string mail);
			bool is_valid_day(tm time);
			void parse_tm(const int day, const int month, const int year, tm &time);
	};
}
