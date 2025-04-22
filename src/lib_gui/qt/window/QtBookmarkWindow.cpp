#include "QtBookmarkWindow.h"

#include "ResourcePaths.h"
#include "utilityQt.h"

#include <string>

using namespace std;
using namespace utility;

QtBookmarkWindow::QtBookmarkWindow(ControllerProxy<BookmarkController> *controllerProxy, bool isSubWindow, QWidget *parent) 
	: QtWindow(isSubWindow, parent)
	, m_controllerProxy(controllerProxy)
{
}

void QtBookmarkWindow::refreshStyleSheet()
{
	string windowStyleSheet = getStyleSheet(ResourcePaths::getGuiDirectoryPath().concatenate(L"window/window.css"));
	string bookmarkStyleSheet = getStyleSheet(ResourcePaths::getGuiDirectoryPath().concatenate(L"bookmark_view/bookmark_view.css"));
	
	setStyleSheet(QString::fromStdString(windowStyleSheet + bookmarkStyleSheet));
}
