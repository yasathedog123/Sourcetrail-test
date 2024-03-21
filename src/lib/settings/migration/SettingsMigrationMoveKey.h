#ifndef SETTINGS_MIGRATION_MOVE_KEY_H
#define SETTINGS_MIGRATION_MOVE_KEY_H

#include "SettingsMigration.h"

class SettingsMigrationMoveKey: public SettingsMigration
{
public:
	SettingsMigrationMoveKey(const std::string& oldKey, const std::string& newKey);
	~SettingsMigrationMoveKey() override;
	void apply(Settings* migratable) const override;

private:
	const std::string m_oldKey;
	const std::string m_newKey;
};

#endif	  // SETTINGS_MIGRATION_MOVE_KEY_H
