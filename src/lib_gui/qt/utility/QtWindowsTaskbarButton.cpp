#include "QtWindowsTaskbarButton.h"

#if BOOST_OS_WINDOWS
	#include <QWinTaskbarButton>
	#include <QWinTaskbarProgress>
#endif

#include "QtMainWindow.h"

QtWindowsTaskbarButton::QtWindowsTaskbarButton()
{
}

void QtWindowsTaskbarButton::setWindow(QtMainWindow* mainWindow)
{
#if BOOST_OS_WINDOWS
	QWinTaskbarButton* taskbarButton = new QWinTaskbarButton(mainWindow);
	taskbarButton->setWindow(mainWindow->windowHandle());
	m_taskbarProgress = taskbarButton->progress();
#endif
}

void QtWindowsTaskbarButton::setProgress(float progress)
{
#if BOOST_OS_WINDOWS
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
#if BOOST_OS_WINDOWS
	if (m_taskbarProgress != nullptr)
	{
		m_taskbarProgress->hide();
	}
#endif
}
