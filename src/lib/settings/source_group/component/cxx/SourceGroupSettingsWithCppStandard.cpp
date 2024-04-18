#include "SourceGroupSettingsWithCppStandard.h"

#include "ConfigManager.h"

#include <ToolVersionData.h>

std::wstring SourceGroupSettingsWithCppStandard::getDefaultCppStandard()
{
	return ClangVersionData::getLatestCppStandard();
}

std::vector<std::wstring> SourceGroupSettingsWithCppStandard::getAvailableCppStandards()
{
	return ClangVersionData::getAvailableCppStandards();
}

std::wstring SourceGroupSettingsWithCppStandard::getCppStandard() const
{
	if (m_cppStandard.empty())
	{
		return getDefaultCppStandard();
	}
	return m_cppStandard;
}

void SourceGroupSettingsWithCppStandard::setCppStandard(const std::wstring& standard)
{
	m_cppStandard = standard;
}

bool SourceGroupSettingsWithCppStandard::equals(const SourceGroupSettingsBase* other) const
{
	const SourceGroupSettingsWithCppStandard* otherPtr =
		dynamic_cast<const SourceGroupSettingsWithCppStandard*>(other);

	return (otherPtr && m_cppStandard == otherPtr->m_cppStandard);
}

void SourceGroupSettingsWithCppStandard::load(const ConfigManager* config, const std::string& key)
{
	setCppStandard(config->getValueOrDefault<std::wstring>(key + "/cpp_standard", L""));
}

void SourceGroupSettingsWithCppStandard::save(ConfigManager* config, const std::string& key)
{
	config->setValue(key + "/cpp_standard", getCppStandard());
}
