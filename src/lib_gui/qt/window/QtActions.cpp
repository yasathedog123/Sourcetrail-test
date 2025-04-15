#include "QtActions.h"

#include <QKeyEvent>

// Notes:
// - Use functions and not constants to create the key sequences at runtime, because the QKeySequence
//   ctor depends on an existing QCoreApplication!
// - Those functions returning String/QList<QString> are only meant for informational purposes,
//   like tooltips or the shortcut table. They are not meant to initialize QActions!
//
// TODO (petermost): Replace hardcoded key event handling with comparisons i.e.:
// if (event == QtKeySequences::back()
//     ...
// bool operator == (const QKeyEvent *event, const QKeySequence &keySequence)
// {
// 	for (int i = 0; i < keySequence.count(); ++i) {
// 		if (event->key() == keySequence[i].key() && event->modifiers() == keySequence[i].keyboardModifiers())
// 			return true;
// 	}
// 	return false;
// }

// bool operator == (const QKeyEvent *event, const QList<QKeySequence> &keySequences)
// {
// 	for (const QKeySequence &keySequence : keySequences) {
// 		if (event == keySequence)
// 			return true;
// 	}
// 	return false;
// }

namespace
{

using StandardKey = QKeySequence::StandardKey;
constexpr QKeySequence::SequenceFormat KEY_FORMAT = QKeySequence::SequenceFormat::NativeText;

constexpr char MOUSE_LEFT_CLICK[] = "Left Click";
constexpr char MOUSE_LEFT_DOUBLE_CLICK[] = "Left Double Click";

constexpr char MOUSE_WHEEL_UP[]   = "Mouse Wheel Up";
constexpr char MOUSE_WHEEL_DOWN[] = "Mouse Wheel Down";

QString toString(const QKeySequence &sequence)
{
	return sequence.toString(KEY_FORMAT);
}

QList<QString> toStringList(const QList<QKeySequence> &sequences)
{
	QList<QString> strings;
	
	for (const QKeySequence &sequence : sequences)
		strings.append(toString(sequence));
	
	return strings;
}

QKeySequence addModifier(Qt::KeyboardModifiers modifiers, const QKeySequence &keySequence)
{
	Q_ASSERT(!keySequence.isEmpty());

	// Test again to prevent crashes in release build:
	if (!keySequence.isEmpty())
		return modifiers | keySequence[0].keyboardModifiers() | keySequence[0].key() ;
	else
		return keySequence;
}

inline QString removeAcceleratorEllipsis(QString s)
{
	return s.remove('&').remove("...");
}

inline QString appendShortcut(QString s, QString shortcut)
{
	return s + QString(" (%1)").arg(shortcut);
}

inline QString appendShortcut(QString s, QString shortcut1, QString shortcut2)
{
	return s + QString(" (%1%2%3)").arg(shortcut1, QtActions::SHORTCUT_SEPARATOR, shortcut2);
}

} // namespace


const char QtActions::SHORTCUT_SEPARATOR[] = " | ";

QtActions::Info::Info(QString text, QString shortcut)
	: QtActions::Info(text, QList({shortcut}))
{
}

QtActions::Info::Info(QString text, QList<QString> shortcuts)
{
	m_text = appendShortcut(text, shortcuts.first());
	m_tooltip = m_text;
	m_shortcuts = shortcuts;
}

QtActions::Info::Info(QString text, QKeySequence shortcut)
	: QtActions::Info(text, QList({shortcut}))
{
}

QtActions::Info::Info(QString text, QList<QKeySequence> shortcuts)
{
	m_text = text;
	m_tooltip = appendShortcut(removeAcceleratorEllipsis(m_text), toString(shortcuts.first()));
	m_shortcuts = toStringList(shortcuts);
}

QtActions::Info::Info(QString text, QString shortcut1, QString shortcut2)
{
	m_text = appendShortcut(text, shortcut1, shortcut2);
	m_tooltip = m_text;
	m_shortcuts = QList<QString>({shortcut1, shortcut2});
}

QString QtActions::Info::text() const
{
	return m_text;
}

QString QtActions::Info::plainText() const
{
	return removeAcceleratorEllipsis(m_text);
}

QString QtActions::Info::shortcut() const
{
	return m_shortcuts.first();
}

QList<QString> QtActions::Info::shortcuts() const
{
	return m_shortcuts;
}

QString QtActions::Info::tooltip() const
{
	return m_tooltip;
}





QtActions::Info QtActions::newProject()
{
	return Info(tr("&New Project..."), StandardKey::New);
}

QtActions::Info QtActions::openProject()
{
	return Info(tr("&Open Project..."), StandardKey::Open);
}

QtActions::Info QtActions::exit()
{
	return Info(tr("E&xit"), StandardKey::Quit);
}

QtActions::Info QtActions::refresh()
{
	return Info(tr("&Refresh..."), StandardKey::Refresh);
}

QtActions::Info QtActions::fullRefresh()
{
	return Info(tr("&Full Refresh..."), addModifier(Qt::ShiftModifier, refresh().shortcut()));
}

QtActions::Info QtActions::findSymbol()
{
	return Info(tr("&Find Symbol"), StandardKey::Find);
}

QtActions::Info QtActions::executeFindSymbol()
{
	return Info(tr("Search"), Qt::Key_Return);
}

QtActions::Info QtActions::findText()
{
	return Info(tr("&Find Text"), addModifier(Qt::ShiftModifier | Qt::ControlModifier, findSymbol().shortcut()));
}

QtActions::Info QtActions::nextReference()
{
	return Info(tr("Next Reference"), Qt::ControlModifier | Qt::Key_G);
}

QtActions::Info QtActions::previousReference()
{
	return Info(tr("Previous Reference"), addModifier(Qt::ShiftModifier, nextReference().shortcut()));
}

QtActions::Info QtActions::nextLocalReference()
{
	return Info(tr("Next Local Reference"), Qt::ControlModifier | Qt::Key_L);
}

QtActions::Info QtActions::previousLocalReference()
{
	return Info(tr("Previous Local Reference"), addModifier(Qt::ShiftModifier, nextLocalReference().shortcut()));
}

QtActions::Info QtActions::customTrailDialog()
{
	return Info(tr("Custom Trail..."), Qt::ControlModifier | Qt::Key_U);
}

QtActions::Info QtActions::toOverview()
{
	return Info(tr("&To overview"), Qt::ControlModifier | Qt::Key_Home);
}

QtActions::Info QtActions::saveGraphAsImage()
{
	return Info(tr("&Save Graph as Image..."), StandardKey::SaveAs);
}

QtActions::Info QtActions::preferences()
{
	// Alternative: StandardKey::Preferences is only defined for MacOS!

	return Info(tr("Preferences..."), Qt::ControlModifier | Qt::Key_Comma);
}

QtActions::Info QtActions::newTab()
{
	return Info(tr("New Tab"), StandardKey::AddTab);
}

QtActions::Info QtActions::closeTab()
{
	return Info(tr("Close Tab"), QList<QKeySequence>({
		StandardKey::Close,

		// Handled in QtMainWindow::keyPressEvent:
		Qt::ControlModifier | Qt::Key_F4
	}));
}

QtActions::Info QtActions::selectNextTab()
{
	// Alternative: 'QKeySequence::NextChild'

	return Info(tr("Select Next Tab"), Qt::ControlModifier | Qt::Key_Tab);
}

QtActions::Info QtActions::selectPreviousTab()
{
	// Alternative: 'QKeySequence::PreviousChild'

	return Info(tr("Select Previous Tab"), addModifier(Qt::ShiftModifier, selectNextTab().shortcut()));
}

QtActions::Info QtActions::largerFont()
{
	return Info(tr("Larger Font"), StandardKey::ZoomIn);
}

QtActions::Info QtActions::smallerFont()
{
	return Info(tr("Smaller Font"), StandardKey::ZoomOut);
}

QtActions::Info QtActions::resetFontSize()
{
	return Info(tr("Reset Font Size"), Qt::ControlModifier | Qt::Key_0);
}

QtActions::Info QtActions::switchGraphCodeFocus()
{
	return Info(tr("Switch Focus between Graph and Code"), Qt::Key_Tab);
}

QtActions::Info QtActions::moveCodeFocus()
{
	return Info(tr("Move Focus Within Code"), {
		Qt::Key_W,    Qt::Key_A,     Qt::Key_S,  Qt::Key_D,
		Qt::Key_H,    Qt::Key_J,     Qt::Key_K,  Qt::Key_L,
		Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down
	});
}

QtActions::Info QtActions::moveReferenceFocus()
{
	return Info(tr("Move Focus to Closest Reference"), {
		Qt::ShiftModifier | Qt::Key_W,    Qt::ShiftModifier | Qt::Key_A,     Qt::ShiftModifier | Qt::Key_S,  Qt::ShiftModifier | Qt::Key_D,
		Qt::ShiftModifier | Qt::Key_H,    Qt::ShiftModifier | Qt::Key_J,     Qt::ShiftModifier | Qt::Key_K,  Qt::ShiftModifier | Qt::Key_L,
		Qt::ShiftModifier | Qt::Key_Left, Qt::ShiftModifier | Qt::Key_Right, Qt::ShiftModifier | Qt::Key_Up, Qt::ShiftModifier | Qt::Key_Down
	});
}

QtActions::Info QtActions::activateLocation()
{
	return Info(tr("Activate Location"), QList<QKeySequence>({
		Qt::Key_Return,
		Qt::Key_E
	}));
}

QtActions::Info QtActions::activateLocationNewTab()
{
	return Info(tr("Activate Location in New Tab"), QList<QKeySequence>({
		Qt::ControlModifier | Qt::ShiftModifier | Qt::Key_Return,
		Qt::ControlModifier | Qt::ShiftModifier | Qt::Key_E
	}));
}

QtActions::Info QtActions::scrollCodeArea()
{
	return Info(tr("Scroll Code Area"), QList<QKeySequence>({
		Qt::ControlModifier | Qt::Key_Left,
		Qt::ControlModifier | Qt::Key_Right,
		Qt::ControlModifier | Qt::Key_Up,
		Qt::ControlModifier | Qt::Key_Down
	}));
}

QtActions::Info QtActions::moveNodeFocus()
{
	return Info(tr("Move Focus Within Nodes"), {
		Qt::Key_W,    Qt::Key_A,     Qt::Key_S,  Qt::Key_D,
		Qt::Key_H,    Qt::Key_J,     Qt::Key_K,  Qt::Key_L,
		Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down
	});
}

QtActions::Info QtActions::moveEdgeFocus()
{
	return Info(tr("Move Focus Within Edges"), {
		Qt::ShiftModifier | Qt::Key_W,    Qt::ShiftModifier | Qt::Key_A,     Qt::ShiftModifier | Qt::Key_S,  Qt::ShiftModifier | Qt::Key_D,
		Qt::ShiftModifier | Qt::Key_H,    Qt::ShiftModifier | Qt::Key_J,     Qt::ShiftModifier | Qt::Key_K,  Qt::ShiftModifier | Qt::Key_L,
		Qt::ShiftModifier | Qt::Key_Left, Qt::ShiftModifier | Qt::Key_Right, Qt::ShiftModifier | Qt::Key_Up, Qt::ShiftModifier | Qt::Key_Down
	});
}

QtActions::Info QtActions::activateNodeEdge()
{
	return Info(tr("Activate Node/Edge"), QList<QKeySequence>({
		Qt::Key_Return,
		Qt::Key_E
	}));
}

QtActions::Info QtActions::expandOrCollapseNode()
{
	return Info(tr("Expand/Collapse Node"), QList<QKeySequence>({
		Qt::ShiftModifier | Qt::Key_Return,
		Qt::ShiftModifier | Qt::Key_E
	}));

}

QtActions::Info QtActions::activateNodeNewTab()
{
	return Info(tr("Activate Node in New Tab"), QList<QKeySequence>({
		Qt::ControlModifier | Qt::ShiftModifier | Qt::Key_Return,
		Qt::ControlModifier | Qt::ShiftModifier | Qt::Key_E
	}));
}

QtActions::Info QtActions::scrollGraphArea()
{
	return Info(tr("Scroll Graph Area"), QList<QKeySequence>({
		Qt::ControlModifier | Qt::Key_Left,
		Qt::ControlModifier | Qt::Key_Right,
		Qt::ControlModifier | Qt::Key_Up,
		Qt::ControlModifier | Qt::Key_Down
	}));
}

QtActions::Info QtActions::refreshUI()
{
	return Info(tr("Refresh UI"), Qt::ControlModifier | Qt::AltModifier | Qt::Key_R);
}

QtActions::Info QtActions::zoomIn()
{
	return Info(tr("Zoom in"), QList<QString>({
		toString(Qt::ControlModifier | Qt::ShiftModifier | Qt::Key_Up),
		zoomInWithMouse().shortcut()
	}));
}

QtActions::Info QtActions::zoomInWithMouse()
{
	return Info(tr("Zoom in"), toString(Qt::ControlModifier) + MOUSE_WHEEL_UP);
}

QtActions::Info QtActions::zoomOut()
{
	return Info(tr("Zoom out"), QList<QString>({
		toString(Qt::ControlModifier | Qt::ShiftModifier | Qt::Key_Down),
		zoomOutWithMouse().shortcut()
	}));
}

QtActions::Info QtActions::zoomOutWithMouse()
{
	return Info(tr("Zoom out"), toString(Qt::ControlModifier) + MOUSE_WHEEL_DOWN);
}

QtActions::Info QtActions::resetZoom()
{
	return Info(tr("Reset Zoom"), Qt::Key_0);
}


QtActions::Info QtActions::expandNodeWithMouse()
{
	return Info(tr("Expand Node"), toString(Qt::ShiftModifier) + MOUSE_LEFT_CLICK);
}

QtActions::Info QtActions::collapseNodeWithMouse()
{
	return Info(tr("Collapse Node"), toString(Qt::ShiftModifier) + MOUSE_LEFT_CLICK);
}

QtActions::Info QtActions::back()
{
	return Info(tr("Back"), QList<QKeySequence>({
		StandardKey::Back,
		Qt::Key_Z,
		Qt::Key_Y,
		Qt::Key_Backspace
	}));
}

QtActions::Info QtActions::forward()
{
	return Info(tr("Forward"), QList<QKeySequence>({
		StandardKey::Forward,
		Qt::ShiftModifier | Qt::Key_Z,
		Qt::ShiftModifier | Qt::Key_Y
	}));
}

QtActions::Info QtActions::bookmarkActiveSymbol()
{
	return Info(tr("Bookmark Active Symbol..."), StandardKey::Save);
}

QtActions::Info QtActions::bookmarkManager()
{
	return Info(tr("Bookmark Manager..."), Qt::ControlModifier | Qt::Key_B);
}

QtActions::Info QtActions::activateBookmark()
{
	Info info(tr("Activate bookmark"), MOUSE_LEFT_CLICK, MOUSE_LEFT_DOUBLE_CLICK);
	
	return info;
}

QtActions::Info QtActions::findOnScreen()
{
	return Info(tr("&Find On-Screen"), QList<QKeySequence>({
		Qt::ControlModifier | Qt::Key_D,

		// Handled in QtMainWindow::keyPressEvent:
		Qt::Key_Slash,
		Qt::Key_Question
	}));
}

QtActions::Info QtActions::screenSearchNext()
{
	return Info(tr("Next match"), Qt::Key_Return);	
}

QtActions::Info QtActions::screenSearchPrevious()
{
	return Info(tr("Previous match"), Qt::ShiftModifier | Qt::Key_Return);	
}

QtActions::Info QtActions::screenSearchClose()
{
	return Info(tr("Close"), Qt::Key_Escape);
}

QtActions::Info QtActions::showInIDEWithMouse()
{
	return Info(tr("Show Definition in IDE"), toString(Qt::ControlModifier) + MOUSE_LEFT_CLICK);
}

QtActions::Info QtActions::openInNewTabWithMouse()
{
	return Info(tr("Open in New Tab"), toString(Qt::ControlModifier) + toString(Qt::ShiftModifier) + MOUSE_LEFT_CLICK);
}

QtActions::Info QtActions::showDefinitionWithMouse()
{
	return Info(tr("Show Definition"), toString(Qt::ControlModifier) + toString(Qt::AltModifier) + MOUSE_LEFT_CLICK);
}

QtActions::Info QtActions::hideNodeWithMouse()
{
	return Info(tr("Hide Node"), toString(Qt::AltModifier) + MOUSE_LEFT_CLICK);
}

QtActions::Info QtActions::hideEdgeWithMouse()
{
	return Info(tr("Hide Edge"), toString(Qt::AltModifier) + MOUSE_LEFT_CLICK);
}

QtActions::Info QtActions::showKeyboardShortcuts()
{
	return Info(tr("Keyboard Shortcuts..."), Qt::Key_F1);
}

QtActions::Info QtActions::showLegend()
{
	return Info(tr("Show legend"), Qt::ShiftModifier | Qt::Key_F1);
}

