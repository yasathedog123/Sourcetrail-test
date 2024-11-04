#ifndef TEXT_CODEC_H
#define TEXT_CODEC_H

#include <memory>
#include <string>

#include <QStringDecoder>
#include <QStringEncoder>
#include <QStringList>

class TextCodec
{
public:
	TextCodec(const std::string& name);

	std::string getName() const;

	std::wstring decode(const std::string& unicodeString) const;
	std::string encode(const std::wstring& string) const;

	static QStringList availableCodecs();

private:
	std::string m_name;
	std::unique_ptr<QStringDecoder> m_decoder;
	std::unique_ptr<QStringEncoder> m_encoder;
};

#endif	  // TEXT_CODEC_H
