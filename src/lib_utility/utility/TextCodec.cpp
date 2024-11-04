#include "TextCodec.h"

#include <array>
#include <optional>

using namespace std;

namespace
{

const array s_encodings = {
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

}

TextCodec::TextCodec(const string &name)
	: m_name(name)
{
	optional<QStringConverter::Encoding> encoding = QStringConverter::encodingForName(m_name.c_str());
	if (encoding) {
		m_decoder = make_unique<QStringDecoder>(*encoding);
		m_encoder = make_unique<QStringEncoder>(*encoding);
	}
}

string TextCodec::getName() const
{
	return m_name;
}

wstring TextCodec::decode(const string &str) const
{
	if (m_decoder)
		static_cast<QString>(m_decoder->decode(str.c_str())).toStdWString();

	return QString::fromStdString(str).toStdWString();
}

string TextCodec::encode(const wstring &str) const
{
	if (m_encoder)
		static_cast<QByteArray>(m_encoder->encode(QString::fromStdWString(str))).toStdString();

	return QString::fromStdWString(str).toStdString();
}

QStringList TextCodec::availableCodecs()
{
	QStringList availableCodecs;
	
	for (const QStringConverter::Encoding encoding : s_encodings)
		availableCodecs += QStringConverter::nameForEncoding(encoding);

	return availableCodecs;
}
