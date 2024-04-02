#ifndef SOURCE_GROUP_SETTINGS_WITH_CPP_STANDARD_H
#define SOURCE_GROUP_SETTINGS_WITH_CPP_STANDARD_H

#include <vector>

#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithCppStandard: public SourceGroupSettingsComponent
{
public:
	static std::wstring getDefaultCppStandard();
	static std::vector<std::wstring> getAvailableCppStandards();

	~SourceGroupSettingsWithCppStandard() override = default;

	std::wstring getCppStandard() const;
	void setCppStandard(const std::wstring& standard);

protected:
	bool equals(const SourceGroupSettingsBase* other) const override;

	void load(const ConfigManager* config, const std::string& key) override;
	void save(ConfigManager* config, const std::string& key) override;

private:
	std::wstring m_cppStandard;
};

#endif	  // SOURCE_GROUP_SETTINGS_WITH_CPP_STANDARD_H
