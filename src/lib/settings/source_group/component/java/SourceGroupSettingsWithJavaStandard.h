#ifndef SOURCE_GROUP_SETTINGS_WITH_JAVA_STANDARD_H
#define SOURCE_GROUP_SETTINGS_WITH_JAVA_STANDARD_H

#include <vector>

#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithJavaStandard: public SourceGroupSettingsComponent
{
public:
	static std::wstring getDefaultJavaStandardStatic();

	~SourceGroupSettingsWithJavaStandard() override = default;

	std::wstring getJavaStandard() const;
	void setJavaStandard(const std::wstring& standard);

	static std::vector<std::wstring> getAvailableJavaStandards();

protected:
	bool equals(const SourceGroupSettingsBase* other) const override;

	void load(const ConfigManager* config, const std::string& key) override;
	void save(ConfigManager* config, const std::string& key) override;

private:
	static std::wstring getDefaultJavaStandard();

	std::wstring m_javaStandard;
};

#endif	  // SOURCE_GROUP_SETTINGS_WITH_JAVA_STANDARD_H
