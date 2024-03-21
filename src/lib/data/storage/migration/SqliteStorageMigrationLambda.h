#ifndef SQLITE_STORAGE_MIGRATION_LAMBDA_H
#define SQLITE_STORAGE_MIGRATION_LAMBDA_H

#include <functional>

#include "SqliteStorageMigration.h"

class SqliteStorageMigrationLambda: public SqliteStorageMigration
{
public:
	SqliteStorageMigrationLambda(
		std::function<void(const SqliteStorageMigration*, SqliteStorage*)> m_lambda);
	~SqliteStorageMigrationLambda() override;
	void apply(SqliteStorage* migratable) const override;

private:
	std::function<void(const SqliteStorageMigration*, SqliteStorage*)> m_lambda;
};

#endif	  // SQLITE_STORAGE_MIGRATION_LAMBDA_H
