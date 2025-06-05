#include "QtStatusBar.h"

#include "ApplicationSettings.h"
#include "MessageErrorsAll.h"
#include "MessageIndexingShowDialog.h"
#include "MessageShowStatus.h"
#include "QtResources.h"
#include "utilityQt.h"

#include <QHBoxLayout>
#include <QMovie>
#include <QProgressBar>

using namespace utility;

QtStatusBar::QtStatusBar()
{
	addWidget(new QWidget()); // add some space

	// loader animation
	{
		m_movie = new QMovie(this);
		m_movie->setFileName(QString::fromUtf8(QtResources::STATUSBAR_VIEW_LOADER));
		
		// Set the movie to loop forever:
		if (m_movie->loopCount() != -1)
			connect(m_movie, &QMovie::finished, m_movie, &QMovie::start);
		m_movie->start();

		m_loader = new QLabel(this);	
		m_loader->setMovie(m_movie);
		m_loader->hide();
		addWidget(m_loader);
	}
	
	// status text
	{
		m_text = new QPushButton(this);
		m_text->setFlat(true);
		m_text->setAttribute(Qt::WA_LayoutUsesWidgetRect); // fixes layouting on Mac
		m_text->setSizePolicy(QSizePolicy::Ignored, m_text->sizePolicy().verticalPolicy());
		m_text->setCursor(Qt::PointingHandCursor);
		addWidget(m_text, 1);
		setText("", false, false);
	
		connect(m_text, &QPushButton::clicked, this, &QtStatusBar::showStatus);
	}
		
	// indexing status
	{
		m_vlineIndexing = new QtVerticalLine(this);
		m_vlineIndexing->hide();
		addPermanentWidget(m_vlineIndexing);
		
		m_indexingStatus = new QPushButton(this);
		m_indexingStatus->setFlat(true);
		m_indexingStatus->setMinimumWidth(150);
		m_indexingStatus->setStyleSheet(QStringLiteral("QPushButton { margin-right: 0; spacing: none; }"));
		m_indexingStatus->setAttribute(Qt::WA_LayoutUsesWidgetRect); // fixes layouting on Mac
		m_indexingStatus->setCursor(Qt::PointingHandCursor);
		
		connect(m_indexingStatus, &QPushButton::clicked, this, &QtStatusBar::clickedIndexingProgress);
		
		QHBoxLayout *layout = new QHBoxLayout();
		layout->setContentsMargins(0, 0, 0, 0);
		
		layout->addWidget(new QLabel(tr("Indexing:")));
		
		m_indexingProgress = new QProgressBar(this);
		m_indexingProgress->setMinimum(0);
		m_indexingProgress->setMaximum(100);
		m_indexingProgress->setValue(100);
		layout->addWidget(m_indexingProgress);
		
		m_indexingStatus->setLayout(layout);
		m_indexingStatus->hide();
		
		addPermanentWidget(m_indexingStatus);
	}
	
	// errors
	{
		m_vlineError = new QtVerticalLine(this);
		m_vlineError->hide();
		addPermanentWidget(m_vlineError);
		
		m_errorButton = new QPushButton(this);
		m_errorButton->hide();
		m_errorButton->setFlat(true);
		m_errorButton->setAttribute(Qt::WA_LayoutUsesWidgetRect); // fixes layouting on Mac
		m_errorButton->setStyleSheet(QStringLiteral("QPushButton { color: #D00000; margin-right: 0; spacing: none; }"));
		m_errorButton->setIcon(colorizePixmap(QPixmap(QString::fromUtf8(QtResources::STATUSBAR_VIEW_DOT)), QColor(0xD0, 0, 0)).scaledToHeight(12));
		m_errorButton->setCursor(Qt::PointingHandCursor);
		addPermanentWidget(m_errorButton);
		
		connect(m_errorButton, &QPushButton::clicked, this, &QtStatusBar::showErrors);
	}

	// ide status
	{
		addPermanentWidget(new QtVerticalLine(this));
		
		m_ideStatusText = new QLabel(this);
		m_ideStatusText->setToolTip(tr("IDE Status"));
		addPermanentWidget(m_ideStatusText);
	}

	// text encoding
	{
		m_vlineTextEncoding = new QtVerticalLine(this);
		addPermanentWidget(m_vlineTextEncoding);
		
		m_textEncoding = new QLabel(this);
		m_textEncoding->setToolTip(tr("Text Encoding"));
		addPermanentWidget(m_textEncoding);
		
		setTextEncoding(ApplicationSettings::getInstance()->getTextEncoding());
	}
}

void QtStatusBar::setText(const std::string &text, bool isError, bool showLoader)
{
	if (isError)
		m_text->setStyleSheet(QStringLiteral("QPushButton { color: #D00000; margin-right: 0; spacing: none; text-align: left; }"));
	else
		m_text->setStyleSheet(QStringLiteral("QPushButton { margin-right: 0; spacing: none; text-align: left; }"));

	if (showLoader)
		m_loader->show();
	else
		m_loader->hide();

	m_text->setText(m_text->fontMetrics().elidedText(QString::fromStdString(text), Qt::ElideRight, m_text->width()));
}

void QtStatusBar::setErrorCount(ErrorCountInfo errorCount)
{
	if (errorCount.total > 0)
	{
		QString errorText = tr("%1 error%2").arg(errorCount.total).arg(errorCount.total > 1 ? "s" : "");
		QString fatalText = tr("(%1 fatal)").arg(errorCount.fatal);
		m_errorButton->setText(errorText + (errorCount.fatal > 0 ? " " + fatalText : ""));
		m_errorButton->setMinimumWidth(m_errorButton->fontMetrics().boundingRect(QString(m_errorButton->text().size(), 'a')).width());

		if (errorCount.fatal > 0)
			m_errorButton->setStyleSheet(QStringLiteral("QPushButton { color: #D00000; margin-right: 0; spacing: none; }"));
		else
			m_errorButton->setStyleSheet(QStringLiteral("QPushButton { margin-right: 0; spacing: none; }"));

		m_errorButton->show();
		m_vlineError->show();
	}
	else
	{
		m_errorButton->hide();
		m_vlineError->hide();
	}
}

void QtStatusBar::setIdeStatus(const std::string &text)
{
	m_ideStatusText->setText(QString::fromStdString(text));
}

void QtStatusBar::showIndexingProgress(size_t progressPercent)
{
	m_indexingStatus->show();
	m_vlineIndexing->show();

	m_indexingProgress->setValue(static_cast<int>(progressPercent));
}

void QtStatusBar::hideIndexingProgress()
{
	m_indexingStatus->hide();
	m_vlineIndexing->hide();
}

void QtStatusBar::setTextEncoding(const std::string &encoding)
{
	m_textEncoding->setText(QString::fromStdString(encoding));
}

void QtStatusBar::resizeEvent(QResizeEvent * /*event*/)
{
	m_text->setText(m_text->fontMetrics().elidedText(m_text->text(), Qt::ElideRight, m_text->width()));
}

void QtStatusBar::showStatus()
{
	MessageShowStatus().dispatch();
}

void QtStatusBar::showErrors()
{
	MessageErrorsAll().dispatch();
}

void QtStatusBar::clickedIndexingProgress()
{
	MessageIndexingShowDialog().dispatch();
}
