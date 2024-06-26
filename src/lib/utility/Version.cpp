#include "Version.h"

Version Version::s_version;

void Version::setApplicationVersion(const Version& version)
{
	s_version = version;
}

const Version& Version::getApplicationVersion()
{
	return s_version;
}

Version::Version(int major, int minor, int patch, int tweak)
	: m_majorNumber(major), m_minorNumber(minor), m_patchNumber(patch), m_tweakNumber(tweak)
{
}

std::string Version::toDisplayString() const
{
	return std::to_string(m_majorNumber) + '.' + std::to_string(m_minorNumber) + '.' +
		std::to_string(m_patchNumber) + '.' + std::to_string(m_tweakNumber);
}

std::wstring Version::toDisplayWString() const
{
	return std::to_wstring(m_majorNumber) + L'.' + std::to_wstring(m_minorNumber) + L'.' +
		std::to_wstring(m_patchNumber) + L'.' + std::to_wstring(m_tweakNumber);
}
