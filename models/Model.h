#pragma once

#include <drogon/drogon.h>

using namespace drogon;

namespace models {
	class Model {
		private:
			static orm::DbClientPtr database;

		public:
			// Getters
			static orm::DbClientPtr getDatabase();
			static void setDatabase(orm::DbClientPtr & db);
	};
}
