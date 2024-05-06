#include "QtWindowsTaskbarButton.h"
#include <Os.h>

// Disable this code for now because of https://www.qt.io/blog/qt-extras-modules-in-qt-6#qwintaskbarbutton
// It also mentions 2 bug reports:
// https://bugreports.qt.io/browse/QTBUG-94008 "Add API to set progress for application, reflected in Dock/task bar"
// https://bugreports.qt.io/browse/QTBUG-94009 "Add API to set overlay for application icon"
// 
// Maybe a solution will be available in the future

#if 0 // BOOST_OS_WINDOWS
	#include <QWinTaskbarButton>
	#include <QWinTaskbarProgress>
#endif

#include "QtMainWindow.h"

QtWindowsTaskbarButton::QtWindowsTaskbarButton()
{
}

void QtWindowsTaskbarButton::setWindow(QtMainWindow* mainWindow)
{
#if 0 // BOOST_OS_WINDOWS
	QWinTaskbarButton* taskbarButton = new QWinTaskbarButton(mainWindow);
	taskbarButton->setWindow(mainWindow->windowHandle());
	m_taskbarProgress = taskbarButton->progress();
#endif
}

void QtWindowsTaskbarButton::setProgress(float progress)
{
#if 0 // BOOST_OS_WINDOWS
	if (m_taskbarProgress != nullptr)
	{
		m_taskbarProgress->show();
		m_taskbarProgress->setValue(
			static_cast<int>(std::max(0, std::min<int>(100, static_cast<int>(100 * progress)))));
	}
#endif
}

void QtWindowsTaskbarButton::hideProgress()
{
#if 0 // BOOST_OS_WINDOWS
	if (m_taskbarProgress != nullptr)
	{
		m_taskbarProgress->hide();
	}
#endif
}
