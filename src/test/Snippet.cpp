/*
ää ÄÄ
😀😀😀😀
ßßß😀😀😀😀
ßßß
*/

[[maybe_unused]]
static const int fileScopeConst = 0;

[[maybe_unused]]
static constexpr int fileScopeConstExpr = 0;

void testFunctionForTooltipWithUmlauteInSignature(/* äöüÄÖÜß€😀 */ )
{
	[[maybe_unused]]
	constexpr int functionScopeConstExpr = 0;
	
	[[maybe_unused]]
	int functionScopeVariable = functionScopeConstExpr;
}
