#include "TabIds.h"

Id TabIds::s_nextTabId = 10;
Id TabIds::s_currentTabId = 0;

Id TabIds::app()
{
	return 1;
}

Id TabIds::background()
{
	return 2;
}

Id TabIds::ignore()
{
	return 3;
}

Id TabIds::nextTab()
{
	return s_nextTabId++;
}

Id TabIds::currentTab()
{
	return s_currentTabId;
}

void TabIds::setCurrentTabId(Id currentTabId)
{
	s_currentTabId = currentTabId;
}
