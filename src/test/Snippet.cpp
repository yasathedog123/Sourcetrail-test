/*
ää ÄÄ
😀😀😀😀
ßßß😀😀😀😀
ßßß
*/

#include <string>

[[maybe_unused]]
static const int fileScopeConst = 0;

[[maybe_unused]]
static constexpr int fileScopeConstExpr = 0;

[[maybe_unused]]
static constexpr char singleLineRawString[] = R"(Some single line raw string)";

[[maybe_unused]]
static constexpr char multiLineRawString[] = R"(
	class A {
	};

	int f()
	{
		A a;
	}
)";

void callFunction(const std::string &)
{
}

void testFunctionForTooltipWithUmlauteInSignature(/* äöüÄÖÜß€😀 */ )
{
	[[maybe_unused]]
	constexpr int functionScopeConstExpr = 0;
	
	[[maybe_unused]]
	int functionScopeVariable = functionScopeConstExpr;

	callFunction(R"(
		Multi
		line
		comment
	)");
}
