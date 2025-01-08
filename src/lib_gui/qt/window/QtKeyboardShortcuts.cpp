#include "QtKeyboardShortcuts.h"

#include <QHeaderView>
#include <QLabel>

#include "QtKeySequences.h"
#include "ResourcePaths.h"
#include "utilityQt.h"

namespace
{

template <typename T>
QString joinToString(const QList<T> &list)
{
	QString str;

	auto it = list.begin();
	if (it != list.end()) {
		str.append(toString(*it++));
		while (it != list.end())
			str.append(" | ").append(toString(*it++));
	}
	return str;
}

struct Shortcut
{
	const QString name;
	const QString shortcut;

	Shortcut(const QString& name, const QString& shortcut)
		: name(name), shortcut(shortcut)
	{}

	Shortcut(const QString &name, const QKeySequence &shortcut)
		: Shortcut(name, shortcut.toString())
	{}

	Shortcut(const QString &name, const QList<QString> &shortcuts)
		: Shortcut(name, joinToString(shortcuts))
	{}

	Shortcut(const QString &name, const QList<QKeySequence> &shortcuts)
		: Shortcut(name, joinToString(shortcuts))
	{}
};

void addShortcuts(QtShortcutTable* table, const std::vector<Shortcut>& shortcuts)
{
	table->setRowCount(static_cast<int>(shortcuts.size()));

	for (size_t i = 0; i < shortcuts.size(); ++i)
	{
		table->setItem(static_cast<int>(i), 0, new QTableWidgetItem(shortcuts[i].name));
		table->setItem(static_cast<int>(i), 1, new QTableWidgetItem(shortcuts[i].shortcut));
	}
	table->updateSize();
}

}

QtShortcutTable::QtShortcutTable(QWidget* parent): QTableWidget(parent) {}

void QtShortcutTable::updateSize()
{
	int height = rowCount() * rowHeight(0) + horizontalHeader()->height() + 2 * frameWidth() + 8;
	setMinimumHeight(height);
	setMaximumHeight(height);
}

void QtShortcutTable::wheelEvent(QWheelEvent* event)
{
	event->ignore();
}


QtKeyboardShortcuts::QtKeyboardShortcuts(QWidget* parent)
	: QtWindow(false, parent)
{
	setScrollAble(true);
}

QtKeyboardShortcuts::~QtKeyboardShortcuts() = default;

QSize QtKeyboardShortcuts::sizeHint() const
{
	return QSize(666, 666);
}

void QtKeyboardShortcuts::populateWindow(QWidget* widget)
{
	QVBoxLayout* layout = new QVBoxLayout(widget);

	QLabel* generalLabel = new QLabel(this);
	generalLabel->setObjectName(QStringLiteral("general_label"));
	generalLabel->setText(tr("General Shortcuts"));
	layout->addWidget(generalLabel);

	layout->addWidget(createGeneralShortcutsTable());

	layout->addSpacing(20);

	QLabel* codeLabel = new QLabel(this);
	codeLabel->setObjectName(QStringLiteral("code_label"));
	codeLabel->setText(tr("Code View Shortcuts"));
	layout->addWidget(codeLabel);

	layout->addWidget(createCodeViewShortcutsTable());

	layout->addSpacing(20);

	QLabel* graphLabel = new QLabel(this);
	graphLabel->setObjectName(QStringLiteral("graph_label"));
	graphLabel->setText(tr("Graph View Shortcuts"));
	layout->addWidget(graphLabel);

	layout->addWidget(createGraphViewShortcutsTable());

	widget->setLayout(layout);

	widget->setStyleSheet(utility::getStyleSheet(ResourcePaths::getGuiDirectoryPath().concatenate(
		L"keyboard_shortcuts/keyboard_shortcuts.css")).c_str());
}

void QtKeyboardShortcuts::windowReady()
{
	updateTitle(QStringLiteral("Keyboard Shortcuts"));
	updateCloseButton(QStringLiteral("Close"));

	setNextVisible(false);
	setPreviousVisible(false);
}


QtShortcutTable* QtKeyboardShortcuts::createTableWidget(const std::string& objectName)
{
	QtShortcutTable* table = new QtShortcutTable(this);
	table->setObjectName(objectName.c_str());

	table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	table->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

	table->setShowGrid(true);
	table->setAlternatingRowColors(true);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	table->horizontalHeader()->setStretchLastSection(true);
	table->verticalHeader()->hide();

	table->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

	table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	table->setColumnCount(2);
	table->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Command")));
	table->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Shortcut")));

	return table;
}


QTableWidget* QtKeyboardShortcuts::createGeneralShortcutsTable()
{
	QtShortcutTable* table = createTableWidget("table_general");

	addShortcuts(table, {
		Shortcut(tr("Switch Focus between Graph and Code"), QtKeySequences::switchGraphCodeFocus()),
		Shortcut(tr("Larger Font"), QtKeySequences::largerFont()),
		Shortcut(tr("Smaller Font"), QtKeySequences::smallerFont()),
		Shortcut(tr("Reset Font Size"), QtKeySequences::resetFontSize()),
		Shortcut(tr("Back"), QtKeySequences::back()),
		Shortcut(tr("Forward"), QtKeySequences::forward()),
		Shortcut(tr("Refresh"), QtKeySequences::refresh()),
		Shortcut(tr("Full Refresh"), QtKeySequences::fullRefresh()),
		Shortcut(tr("Find Symbol"), QtKeySequences::findSymbol()),
		Shortcut(tr("Find Text"), QtKeySequences::findText()),
		Shortcut(tr("Find On-Screen"), QtKeySequences::findOnScreen()),
		Shortcut(tr("New Project"), QtKeySequences::newProject()),
		Shortcut(tr("Open Project"), QtKeySequences::openProject()),
		Shortcut(tr("Close Window"), QtKeySequences::closeTab()),
		Shortcut(tr("Refresh UI"), QtKeySequences::refreshUI()),
		Shortcut(tr("To Overview"), QtKeySequences::toOverview()),
		Shortcut(tr("Preferences"), QtKeySequences::preferences()),
		Shortcut(tr("Bookmark Active Symbol"), QtKeySequences::bookmarkActiveSymbol()),
		Shortcut(tr("Bookmark Manager"), QtKeySequences::bookmarkManager())
	});
	return table;
}

QTableWidget* QtKeyboardShortcuts::createCodeViewShortcutsTable()
{
	QtShortcutTable* table = createTableWidget("table_code");

	addShortcuts(table, {
		Shortcut(tr("Move Focus Within Code"), QtKeySequences::moveCodeFocus()),
		Shortcut(tr("Move Focus to Closest Reference"), QtKeySequences::moveReferenceFocus()),
		Shortcut(tr("Activate Location"), QtKeySequences::activateLocation()),
		Shortcut(tr("Activate Location in New Tab"), QtKeySequences::activateLocationNewTab()),
		Shortcut(tr("Next Reference"), QtKeySequences::nextReference()),
		Shortcut(tr("Previous Reference"), QtKeySequences::previousReference()),
		Shortcut(tr("Next Local Reference"), QtKeySequences::nextLocalReference()),
		Shortcut(tr("Previous Local Reference"), QtKeySequences::previousLocalReference()),
		Shortcut(tr("Scroll Code Area"), QtKeySequences::scrollCodeArea())
	});

	return table;
}

QTableWidget* QtKeyboardShortcuts::createGraphViewShortcutsTable()
{
	QtShortcutTable* table = createTableWidget("table_graph");

	addShortcuts(table, {
		Shortcut(tr("Move Focus Within Nodes"), QtKeySequences::moveNodeFocus()),
		Shortcut(tr("Move Focus Within Edges"), QtKeySequences::moveEdgeFocus()),
		Shortcut(tr("Activate Node/Edge"), QtKeySequences::activateNodeEdge()),
		Shortcut(tr("Expand/Collapse Node"), QtKeySequences::expandOrCollapseNode()),
		Shortcut(tr("Activate Node in New Tab"), QtKeySequences::activateNodeNewTab()),
		Shortcut(tr("Scroll Graph Area"), QtKeySequences::scrollGraphArea()),
		Shortcut(tr("Zoom in"), QtKeySequences::zoomIn()),
		Shortcut(tr("Zoom out"), QtKeySequences::zoomOut()),
		Shortcut(tr("Reset Zoom"), QtKeySequences::resetZoom()),
		Shortcut(tr("Open Custom Trail Dialog"), QtKeySequences::customTrailDialog())
	});

	return table;
}
