#include "SourceGroupSettingsWithJavaStandard.h"

#include "ConfigManager.h"
#include "ToolVersionSupport.h"

std::wstring SourceGroupSettingsWithJavaStandard::getJavaStandard() const
{
	if (m_javaStandard.empty())
	{
		return EclipseVersionSupport::getLatestJavaStandard();
	}
	return m_javaStandard;
}

void SourceGroupSettingsWithJavaStandard::setJavaStandard(const std::wstring& standard)
{
	m_javaStandard = standard;
}

bool SourceGroupSettingsWithJavaStandard::equals(const SourceGroupSettingsBase* other) const
{
	const SourceGroupSettingsWithJavaStandard* otherPtr =
		dynamic_cast<const SourceGroupSettingsWithJavaStandard*>(other);

	return (otherPtr && m_javaStandard == otherPtr->m_javaStandard);
}

void SourceGroupSettingsWithJavaStandard::load(const ConfigManager* config, const std::string& key)
{
	setJavaStandard(config->getValueOrDefault<std::wstring>(key + "/java_standard", L""));
}

void SourceGroupSettingsWithJavaStandard::save(ConfigManager* config, const std::string& key)
{
	config->setValue(key + "/java_standard", getJavaStandard());
}

