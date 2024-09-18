#include "SourceGroupSettingsWithCStandard.h"

#include "ConfigManager.h"
#include "ToolVersionSupport.h"

std::wstring SourceGroupSettingsWithCStandard::getDefaultCStandard()
{
	return ClangVersionSupport::getLatestCStandard();
}

std::vector<std::wstring> SourceGroupSettingsWithCStandard::getAvailableCStandards()
{
	return ClangVersionSupport::getAvailableCStandards();
}

std::wstring SourceGroupSettingsWithCStandard::getCStandard() const
{
	if (m_cStandard.empty())
	{
		return getDefaultCStandard();
	}
	return m_cStandard;
}

void SourceGroupSettingsWithCStandard::setCStandard(const std::wstring& standard)
{
	m_cStandard = standard;
}


bool SourceGroupSettingsWithCStandard::equals(const SourceGroupSettingsBase* other) const
{
	const SourceGroupSettingsWithCStandard* otherPtr =
		dynamic_cast<const SourceGroupSettingsWithCStandard*>(other);

	return (otherPtr && m_cStandard == otherPtr->m_cStandard);
}

void SourceGroupSettingsWithCStandard::load(const ConfigManager* config, const std::string& key)
{
	setCStandard(config->getValueOrDefault<std::wstring>(key + "/c_standard", L""));
}

void SourceGroupSettingsWithCStandard::save(ConfigManager* config, const std::string& key)
{
	config->setValue(key + "/c_standard", getCStandard());
}
