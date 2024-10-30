#include "TextCodec.h"

#include <QTextCodec>

TextCodec::TextCodec(const std::string &name)
	: m_name(name)
{
	if (QTextCodec *codec = QTextCodec::codecForName(m_name.c_str()); codec != nullptr) {
		m_decoder = std::make_unique<QTextDecoder>(codec);
		m_encoder = std::make_unique<QTextEncoder>(codec);
	}
}

std::string TextCodec::getName() const
{
	return m_name;
}

std::wstring TextCodec::decode(const std::string& unicodeString) const
{
	if (m_decoder)
		return m_decoder->toUnicode(unicodeString.c_str()).toStdWString();

	return QString::fromStdString(unicodeString).toStdWString();
}

std::string TextCodec::encode(const std::wstring& string) const
{
	if (m_encoder)
		return m_encoder->fromUnicode(QString::fromStdWString(string)).toStdString();

	return QString::fromStdWString(string).toStdString();
}

QStringList TextCodec::availableMibCodecs()
{
	QStringList availableMibCodecs;

	for (int mib: QTextCodec::availableMibs()) {
		if (QTextCodec *codec = QTextCodec::codecForMib(mib); codec != nullptr)
			availableMibCodecs.append(codec->name());
	}
	return availableMibCodecs;
}
