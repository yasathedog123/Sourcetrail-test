#include "TextCodec.h"

#include <array>

using namespace std;

namespace
{

constexpr array AVAILABLE_ENCODINGS = {
	QStringConverter::Encoding::Utf8,
	QStringConverter::Encoding::Utf16,
	QStringConverter::Encoding::Utf16LE,
	QStringConverter::Encoding::Utf16BE,
	QStringConverter::Encoding::Utf32,
	QStringConverter::Encoding::Utf32LE,
	QStringConverter::Encoding::Utf32BE,
	QStringConverter::Encoding::Latin1,
	QStringConverter::Encoding::System
};
static_assert(AVAILABLE_ENCODINGS.size() == QStringConverter::Encoding::LastEncoding + 1, "Encoding missing");

}

QStringList TextCodec::availableCodecs()
{
	QStringList availableCodecs;

	for (const QStringConverter::Encoding encoding : AVAILABLE_ENCODINGS)
		availableCodecs += QStringConverter::nameForEncoding(encoding);

	return availableCodecs;
}

TextCodec::TextCodec(const string &name)
	: m_name(name)
	, m_decoder(m_name.c_str())
	, m_encoder(m_name.c_str())
{
}

wstring TextCodec::decode(const string &str)
{
	if (m_decoder.isValid())
		return static_cast<QString>(m_decoder.decode(str.c_str())).toStdWString();
	else
		return QString::fromStdString(str).toStdWString();
}

string TextCodec::encode(const wstring &str)
{
	if (m_encoder.isValid())
		return static_cast<QByteArray>(m_encoder.encode(QString::fromStdWString(str))).toStdString();
	else
		return QString::fromStdWString(str).toStdString();
}

int TextCodec::encodedSize(const QString &str)
{
	if (m_encoder.isValid())
		return static_cast<QByteArray>(m_encoder.encode(str)).size();
	else
		return str.toUtf8().size();
}

bool TextCodec::isValid() const
{
	return m_decoder.isValid() && m_encoder.isValid();
}

string TextCodec::getName() const
{
	return m_name;
}
