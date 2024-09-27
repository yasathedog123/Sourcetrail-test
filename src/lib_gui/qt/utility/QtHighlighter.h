#ifndef QT_HIGHLIGHTER_H
#define QT_HIGHLIGHTER_H

#include <QRegExp>
#include <QTextCharFormat>

#include <enum_class.hpp>

class QTextBlock;
class QTextDocument;

class QtHighlighter
{
public:
	class HighlightType final : public aidkit::enum_class<HighlightType>
	{
	public:
		static const HighlightType COMMENT;
		static const HighlightType DIRECTIVE;
		static const HighlightType FUNCTION;
		static const HighlightType KEYWORD;
		static const HighlightType NUMBER;
		static const HighlightType QUOTATION;
		static const HighlightType TEXT;
		static const HighlightType TYPE;

	private:
		using enum_class::enum_class;
	};

	static void loadHighlightingRules();
	static void clearHighlightingRules();

	QtHighlighter(QTextDocument* parent, const std::wstring& language);
	~QtHighlighter() = default;

	void highlightDocument();
	void highlightRange(int startLine, int endLine);

	void rehighlightLines(const std::vector<int>& lines);

	void applyFormat(int startPosition, int endPosition, const QTextCharFormat& format);

	QTextCharFormat getFormat(int startPosition, int endPosition) const;

private:
	struct HighlightingRule
	{
		HighlightingRule();
		HighlightingRule(
			HighlightType type, const QRegExp& regExp, bool priority, bool multiLine = false);

		HighlightType type = HighlightType::TEXT;
		QRegExp pattern;
		bool priority = false;
		bool multiLine = false;
	};

	void createRanges(QTextDocument* doc, const std::vector<HighlightingRule>& quotationRules);
	std::vector<std::tuple<HighlightType, int, int>> createMultiLineRanges(
		QTextDocument* doc, std::vector<std::tuple<HighlightType, int, int>>* ranges);
	std::vector<std::tuple<QtHighlighter::HighlightType, int, int>> createMultiLineRangesForRules(
		QTextDocument* doc,
		std::vector<std::tuple<HighlightType, int, int>>* ranges,
		const HighlightingRule* startRule,
		const HighlightingRule* endRule);

	static bool isInRange(int index, const std::vector<std::tuple<HighlightType, int, int>>& ranges);
	static std::vector<std::tuple<HighlightType, int, int>> getRangesForRule(
		const QTextBlock& block, const HighlightingRule& rule);

	void formatBlockForRule(
		const QTextBlock& block,
		const HighlightingRule& rule,
		std::vector<std::tuple<HighlightType, int, int>>* ranges);
	void formatBlockIfInRange(
		const QTextBlock& block,
		HighlightType type,
		std::vector<std::tuple<HighlightType, int, int>>* ranges);
	void formatBlockIfInRange(
		const QTextBlock& block, std::vector<std::tuple<HighlightType, int, int>>* ranges);

	QTextDocument* document() const;

	static std::map<std::wstring, std::vector<HighlightingRule>> s_highlightingRules;
	static std::map<HighlightType, QTextCharFormat> s_charFormats;

	QTextDocument* m_document;

	std::vector<HighlightingRule> m_highlightingRules;
	std::vector<std::tuple<HighlightType, int, int>> m_singleLineRanges;
	std::vector<std::tuple<HighlightType, int, int>> m_multiLineRanges;
	std::vector<bool> m_highlightedLines;
};

#endif	  // QT_HIGHLIGHTER_H
