#ifndef SOURCE_GROUP_SETTINGS_WITH_CPP_STANDARD_H
#define SOURCE_GROUP_SETTINGS_WITH_CPP_STANDARD_H

#include <vector>

#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithCppStandard: public SourceGroupSettingsComponent
{
public:
	static std::wstring getDefaultCppStandardStatic();

	~SourceGroupSettingsWithCppStandard() override = default;

	std::wstring getCppStandard() const;
	void setCppStandard(const std::wstring& standard);

	std::vector<std::wstring> getAvailableCppStandards() const;

protected:
	bool equals(const SourceGroupSettingsBase* other) const override;

	void load(const ConfigManager* config, const std::string& key) override;
	void save(ConfigManager* config, const std::string& key) override;

private:
	std::wstring getDefaultCppStandard() const;

	std::wstring m_cppStandard;
};

#endif	  // SOURCE_GROUP_SETTINGS_WITH_CPP_STANDARD_H
