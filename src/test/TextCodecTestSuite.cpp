#include "Catch2.hpp"

#include <TextCodec.h>

#include <string>

using namespace std;

//     UTF-16 | UTF-8     | ISO-8859-1 (Latin-1)
// ---------------------------------------------
// ä | 0x00E4 | 0xC3 0xA4 | 0xE4
// ö | 0x00F6 | 0xC3 0xB6 | 0xF6
// ü | 0x00FC | 0xC3 0xBC | 0xFC
// Ä | 0x00C4 | 0xC3 0xC4 | 0xC4
// Ö | 0x00D6 | 0xC3 0x96 | 0xD6
// Ü | 0x00DC | 0xC3 0x9C | 0xDC
// ß | 0x00DF | 0xC3 0x9F | 0xDF
// € | 0x0080 | 0xC2 0x80 | 0x80 (Officially not defined)
// =============================================

const wstring UTF16_LOWER_AE(L"\x00E4");
const wstring UTF16_LOWER_OE(L"\x00F6");
const wstring UTF16_LOWER_UE(L"\x00FC");
const wstring UTF16_UPPER_AE(L"\x00C4");
const wstring UTF16_UPPER_OE(L"\x00D6");
const wstring UTF16_UPPER_UE(L"\x00DC");
const wstring UTF16_SHARP_SS(L"\x00DF");
const wstring UTF16_EURO(L"\x0080");

const wstring UTF16_CHARACTERS =
	UTF16_LOWER_AE + UTF16_LOWER_OE + UTF16_LOWER_UE +
	UTF16_UPPER_AE + UTF16_UPPER_OE + UTF16_UPPER_UE +
	UTF16_SHARP_SS + UTF16_EURO;

const string UTF8_LOWER_AE("\xC3\xA4");
const string UTF8_LOWER_OE("\xC3\xB6");
const string UTF8_LOWER_UE("\xC3\xBC");
const string UTF8_UPPER_AE("\xC3\x84");
const string UTF8_UPPER_OE("\xC3\x96");
const string UTF8_UPPER_UE("\xC3\x9C");
const string UTF8_SHARP_SS("\xC3\x9F");
const string UTF8_EURO("\xC2\x80");

const string UTF8_CHARACTERS =
	UTF8_LOWER_AE + UTF8_LOWER_OE + UTF8_LOWER_UE +
	UTF8_UPPER_AE + UTF8_UPPER_OE + UTF8_UPPER_UE +
	UTF8_SHARP_SS + UTF8_EURO;

const wstring ISO_8859_1_WIDE_LOWER_AE(L"\x00E4");
const wstring ISO_8859_1_WIDE_LOWER_OE(L"\x00F6");
const wstring ISO_8859_1_WIDE_LOWER_UE(L"\x00FC");
const wstring ISO_8859_1_WIDE_UPPER_AE(L"\x00C4");
const wstring ISO_8859_1_WIDE_UPPER_OE(L"\x00D6");
const wstring ISO_8859_1_WIDE_UPPER_UE(L"\x00DC");
const wstring ISO_8859_1_WIDE_SHARP_SS(L"\x00DF");

const wstring ISO_8859_1_WIDE_CHARACTERS =
	ISO_8859_1_WIDE_LOWER_AE + ISO_8859_1_WIDE_LOWER_OE + ISO_8859_1_WIDE_LOWER_UE +
	ISO_8859_1_WIDE_UPPER_AE + ISO_8859_1_WIDE_UPPER_OE + ISO_8859_1_WIDE_UPPER_UE +
	ISO_8859_1_WIDE_SHARP_SS;

const string ISO_8859_1_NARROW_LOWER_AE("\xE4");
const string ISO_8859_1_NARROW_LOWER_OE("\xF6");
const string ISO_8859_1_NARROW_LOWER_UE("\xFC");
const string ISO_8859_1_NARROW_UPPER_AE("\xC4");
const string ISO_8859_1_NARROW_UPPER_OE("\xD6");
const string ISO_8859_1_NARROW_UPPER_UE("\xDC");
const string ISO_8859_1_NARROW_SHARP_SS("\xDF");

const string ISO_8859_1_NARROW_CHARACTERS =
	ISO_8859_1_NARROW_LOWER_AE + ISO_8859_1_NARROW_LOWER_OE + ISO_8859_1_NARROW_LOWER_UE +
	ISO_8859_1_NARROW_UPPER_AE + ISO_8859_1_NARROW_UPPER_OE + ISO_8859_1_NARROW_UPPER_UE +
	ISO_8859_1_NARROW_SHARP_SS;

using Encoding = QStringConverter::Encoding;

static TextCodec makeCodec(Encoding encoding)
{
	return TextCodec(QStringConverter::nameForEncoding(encoding));
}

//=================================================================================================

TEST_CASE("TextCodec empty decoding")
{
	TextCodec codec = makeCodec(Encoding::System);

	string narrowString("");
	wstring wideString = codec.decode(narrowString);

	REQUIRE(wideString == L""s);
}

TEST_CASE("TextCodec empty encoding")
{
	TextCodec codec = makeCodec(Encoding::System);

	wstring wideString(L"");
	string narrowString = codec.encode(wideString);

	REQUIRE(narrowString == ""s);
}

//=================================================================================================

TEST_CASE("TextCodec ascii decoding")
{
	TextCodec codec = makeCodec(Encoding::System);

	string narrowString("abcdef");
	wstring wideString = codec.decode(narrowString);

	REQUIRE(wideString == L"abcdef"s);
}

TEST_CASE("TextCodec ascii encoding")
{
	TextCodec codec = makeCodec(Encoding::System);

	wstring wideString(L"12345");
	string narrowString = codec.encode(wideString);

	REQUIRE(narrowString == "12345"s);
}

//=================================================================================================

TEST_CASE("TextCodec utf8 encoding")
{
	TextCodec codec = makeCodec(Encoding::Utf8);

	string utf8Umlaute = codec.encode(UTF16_CHARACTERS);

	REQUIRE(UTF8_CHARACTERS == utf8Umlaute);
}

TEST_CASE("TextCodec utf8 decoding")
{
	TextCodec codec = makeCodec(Encoding::Utf8);

	wstring utf16Umlaute = codec.decode(UTF8_CHARACTERS);

	REQUIRE(UTF16_CHARACTERS == utf16Umlaute);
}

//=================================================================================================

TEST_CASE("TextCodec iso-8859-1 encoding")
{
	TextCodec codec = makeCodec(Encoding::Latin1);

	string narrowUmlaute = codec.encode(ISO_8859_1_WIDE_CHARACTERS);

	REQUIRE(narrowUmlaute == ISO_8859_1_NARROW_CHARACTERS);
}

TEST_CASE("TextCodec iso-8859-1 decoding")
{
	TextCodec codec = makeCodec(Encoding::Latin1);

	wstring wideUmlaute = codec.decode(ISO_8859_1_NARROW_CHARACTERS);

	REQUIRE(wideUmlaute == ISO_8859_1_WIDE_CHARACTERS);
}

