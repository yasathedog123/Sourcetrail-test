#ifndef TEXT_CODEC_H
#define TEXT_CODEC_H

#include <string>

#include <QStringDecoder>
#include <QStringEncoder>
#include <QStringList>

class TextCodec
{
public:
	static QStringList availableCodecs();

	TextCodec(const std::string& name);

	std::wstring decode(const std::string &str);
	std::string encode(const std::wstring &str);

	int encodedSize(const QString &str);

	bool isValid() const;
	std::string getName() const;

private:
	std::string m_name;
	QStringDecoder m_decoder;
	QStringEncoder m_encoder;
};

#endif	  // TEXT_CODEC_H
