#ifndef SETTINGS_MIGRATION_DELETE_KEY_H
#define SETTINGS_MIGRATION_DELETE_KEY_H

#include <string>

#include "SettingsMigration.h"

class SettingsMigrationDeleteKey: public SettingsMigration
{
public:
	SettingsMigrationDeleteKey(const std::string& key);
	~SettingsMigrationDeleteKey() override;
	void apply(Settings* migratable) const override;

private:
	const std::string m_key;
};

#endif	  // SETTINGS_MIGRATION_DELETE_KEY_H
