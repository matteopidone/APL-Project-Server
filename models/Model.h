#pragma once

#include <drogon/drogon.h>

using namespace drogon;

namespace models {
	class Model {
		private:
			static orm::DbClientPtr database;

		public:
			// Constructor
			Model();

			// Getters
			orm::DbClientPtr getDatabase() const;
	};
}
