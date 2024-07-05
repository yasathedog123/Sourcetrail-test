#ifndef SQLITE_STORAGE_MIGRATION_H
#define SQLITE_STORAGE_MIGRATION_H

#include <string>

#include "Migration.h"
#include "SqliteStorage.h"

class SqliteStorageMigration: public Migration<SqliteStorage>
{
public:
	~SqliteStorageMigration() override;

	static bool executeStatementInStorage(SqliteStorage* storage, const std::string& statement);
};

#endif	  // SQLITE_STORAGE_MIGRATION_H
