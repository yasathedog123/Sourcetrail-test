#ifndef SETTINGS_MIGRATION_LAMBDA_H
#define SETTINGS_MIGRATION_LAMBDA_H

#include <functional>

#include "SettingsMigration.h"

class SettingsMigrationLambda: public SettingsMigration
{
public:
	SettingsMigrationLambda(std::function<void(const SettingsMigration*, Settings*)> m_lambda);
	~SettingsMigrationLambda() override;
	void apply(Settings* migratable) const override;

private:
	std::function<void(const SettingsMigration*, Settings*)> m_lambda;
};

#endif	  // SETTINGS_MIGRATION_LAMBDA_H
