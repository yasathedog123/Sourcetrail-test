#ifndef TEXT_CODEC_H
#define TEXT_CODEC_H

#include <memory>
#include <string>

#include <QByteArray>
#include <QStringList>
#include <QTextDecoder>
#include <QTextEncoder>

class TextCodec
{
public:
	TextCodec(const std::string& name);

	std::string getName() const;

	std::wstring decode(const std::string& unicodeString) const;
	std::string encode(const std::wstring& string) const;

	static QStringList availableMibCodecs();

private:
	std::string m_name;
	std::unique_ptr<QTextDecoder> m_decoder;
	std::unique_ptr<QTextEncoder> m_encoder;
};

#endif	  // TEXT_CODEC_H
