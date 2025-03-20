#include "QtKeySequences.h"

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


using StandardKey = QKeySequence::StandardKey;

constexpr QKeySequence::SequenceFormat KEY_FORMAT = QKeySequence::SequenceFormat::NativeText;

QString toString(const QKeySequence &sequence)
{
	return sequence.toString(KEY_FORMAT);
}

const QString &toString(const QString &s)
{
	return s;
}

static QList<QString> toString(const QList<QKeySequence> &sequences)
{
	QList<QString> strings;

	for (const QKeySequence &sequence : sequences)
		strings.append(toString(sequence));

	return strings;
}


bool operator == (const QKeyEvent *event, const QKeySequence &keySequence)
{
	for (int i = 0; i < keySequence.count(); ++i) {
		if (event->key() == keySequence[i].key() && event->modifiers() == keySequence[i].keyboardModifiers())
			return true;
	}
	return false;
}

bool operator == (const QKeyEvent *event, const QList<QKeySequence> &keySequences)
{
	for (const QKeySequence &keySequence : keySequences) {
		if (event == keySequence)
			return true;
	}
	return false;
}

static QKeySequence addModifier(Qt::KeyboardModifiers modifiers, const QKeySequence &keySequence)
{
	Q_ASSERT(!keySequence.isEmpty());

	// Test again to prevent crashes in release build:
	if (!keySequence.isEmpty())
		return modifiers | keySequence[0].keyboardModifiers() | keySequence[0].key() ;
	else
		return keySequence;
}

QKeySequence QtKeySequences::newProject()
{
	return StandardKey::New;
}

QKeySequence QtKeySequences::openProject()
{
	return StandardKey::Open;
}

QKeySequence QtKeySequences::exit()
{
	return StandardKey::Quit;
}

QKeySequence QtKeySequences::refresh()
{
	return StandardKey::Refresh;
}

QKeySequence QtKeySequences::fullRefresh()
{
	return addModifier(Qt::ShiftModifier, refresh());
}

QKeySequence QtKeySequences::findSymbol()
{
	return StandardKey::Find;
}

QKeySequence QtKeySequences::findText()
{
	return addModifier(Qt::ShiftModifier | Qt::ControlModifier, findSymbol());
}

QList<QKeySequence> QtKeySequences::findOnScreen()
{
	return {
		Qt::ControlModifier | Qt::Key_D,

		// Handled in QtMainWindow::keyPressEvent:
		Qt::Key_Slash,
		Qt::Key_Question
	};
}

QKeySequence QtKeySequences::nextReference()
{
	return Qt::ControlModifier | Qt::Key_G;
}

QKeySequence QtKeySequences::previousReference()
{
	return addModifier(Qt::ShiftModifier, nextReference());
}

QKeySequence QtKeySequences::nextLocalReference()
{
	return Qt::ControlModifier | Qt::Key_L;
}

QKeySequence QtKeySequences::previousLocalReference()
{
	return addModifier(Qt::ShiftModifier, nextLocalReference());
}

QKeySequence QtKeySequences::customTrailDialog()
{
	return Qt::ControlModifier | Qt::Key_U;
}

QKeySequence QtKeySequences::toOverview()
{
	return Qt::ControlModifier | Qt::Key_Home;
}

QKeySequence QtKeySequences::saveGraphAsImage()
{
	return StandardKey::SaveAs;
}

QKeySequence QtKeySequences::preferences()
{
	// Alternative: StandardKey::Preferences is only defined for MacOS!

	return Qt::ControlModifier | Qt::Key_Comma;
}

QKeySequence QtKeySequences::newTab()
{
	return StandardKey::AddTab;
}

QList<QKeySequence> QtKeySequences::closeTab()
{
	return {
		QKeySequence::Close,

		// Handled in QtMainWindow::keyPressEvent:
		Qt::ControlModifier | Qt::Key_F4
	};
}

QKeySequence QtKeySequences::selectNextTab()
{
	// Alternative: 'QKeySequence::NextChild'

	return Qt::ControlModifier | Qt::Key_Tab;
}

QKeySequence QtKeySequences::selectPreviousTab()
{
	// Alternative: 'QKeySequence::PreviousChild'

	return addModifier(Qt::ShiftModifier, selectNextTab());
}

QKeySequence QtKeySequences::largerFont()
{
	return StandardKey::ZoomIn;
}

QKeySequence QtKeySequences::smallerFont()
{
	return StandardKey::ZoomOut;
}

QKeySequence QtKeySequences::resetFontSize()
{
	return Qt::ControlModifier | Qt::Key_0;
}

QString QtKeySequences::switchGraphCodeFocus()
{
	return toString(Qt::Key_Tab);
}

QList<QString> QtKeySequences::moveCodeFocus()
{
	return toString({
		Qt::Key_W,    Qt::Key_A,     Qt::Key_S,  Qt::Key_D,
		Qt::Key_H,    Qt::Key_J,     Qt::Key_K,  Qt::Key_L,
		Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down
	});
}

QList<QString> QtKeySequences::moveReferenceFocus()
{
	return toString({
		Qt::ShiftModifier | Qt::Key_W,    Qt::ShiftModifier | Qt::Key_A,     Qt::ShiftModifier | Qt::Key_S,  Qt::ShiftModifier | Qt::Key_D,
		Qt::ShiftModifier | Qt::Key_H,    Qt::ShiftModifier | Qt::Key_J,     Qt::ShiftModifier | Qt::Key_K,  Qt::ShiftModifier | Qt::Key_L,
		Qt::ShiftModifier | Qt::Key_Left, Qt::ShiftModifier | Qt::Key_Right, Qt::ShiftModifier | Qt::Key_Up, Qt::ShiftModifier | Qt::Key_Down
	});
}

QList<QString> QtKeySequences::activateLocation()
{
	return toString({
		QKeySequence(Qt::Key_Return),
		Qt::Key_E
	});
}

QList<QString> QtKeySequences::activateLocationNewTab()
{
	return toString({
		QKeySequence(Qt::ControlModifier | Qt::ShiftModifier | Qt::Key_Return),
		Qt::ControlModifier | Qt::ShiftModifier | Qt::Key_E
	});
}

QList<QString> QtKeySequences::scrollCodeArea()
{
	return toString({
		QKeySequence(Qt::ControlModifier | Qt::Key_Left),
		Qt::ControlModifier | Qt::Key_Right,
		Qt::ControlModifier | Qt::Key_Up,
		Qt::ControlModifier | Qt::Key_Down
	});
}

QList<QString> QtKeySequences::moveNodeFocus()
{
	return toString({
		Qt::Key_W,    Qt::Key_A,     Qt::Key_S,  Qt::Key_D,
		Qt::Key_H,    Qt::Key_J,     Qt::Key_K,  Qt::Key_L,
		Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down
	});
}

QList<QString> QtKeySequences::moveEdgeFocus()
{
	return toString({
		Qt::ShiftModifier | Qt::Key_W,    Qt::ShiftModifier | Qt::Key_A,     Qt::ShiftModifier | Qt::Key_S,  Qt::ShiftModifier | Qt::Key_D,
		Qt::ShiftModifier | Qt::Key_H,    Qt::ShiftModifier | Qt::Key_J,     Qt::ShiftModifier | Qt::Key_K,  Qt::ShiftModifier | Qt::Key_L,
		Qt::ShiftModifier | Qt::Key_Left, Qt::ShiftModifier | Qt::Key_Right, Qt::ShiftModifier | Qt::Key_Up, Qt::ShiftModifier | Qt::Key_Down
	});
}

QList<QString> QtKeySequences::activateNodeEdge()
{
	return toString({
		QKeySequence(Qt::Key_Return),
		Qt::Key_E
	});
}

QList<QString> QtKeySequences::expandOrCollapseNode()
{
	return toString({
		QKeySequence(Qt::ShiftModifier | Qt::Key_Return),
		Qt::ShiftModifier | Qt::Key_E
	});

}

QList<QString> QtKeySequences::activateNodeNewTab()
{
	return toString({
		QKeySequence(Qt::ControlModifier | Qt::ShiftModifier | Qt::Key_Return),
		Qt::ControlModifier | Qt::ShiftModifier | Qt::Key_E
	});
}

QList<QString> QtKeySequences::scrollGraphArea()
{
	return toString({
		QKeySequence(Qt::ControlModifier | Qt::Key_Left),
		Qt::ControlModifier | Qt::Key_Right,
		Qt::ControlModifier | Qt::Key_Up,
		Qt::ControlModifier | Qt::Key_Down
	});
}

QString QtKeySequences::refreshUI()
{
	return toString(Qt::ControlModifier | Qt::AltModifier | Qt::Key_R);
}

QList<QString> QtKeySequences::zoomIn()
{
	return {
		toString(Qt::ControlModifier | Qt::ShiftModifier | Qt::Key_Up),
		zoomInWithMouse()
	};
}

QString QtKeySequences::zoomInWithMouse()
{
	return toString(Qt::ControlModifier) + "Mouse Wheel Up";
}

QList<QString> QtKeySequences::zoomOut()
{
	return {
		toString(Qt::ControlModifier | Qt::ShiftModifier | Qt::Key_Down),
		zoomOutWithMouse()
	};
}

QString QtKeySequences::zoomOutWithMouse()
{
	return toString(Qt::ControlModifier) + "Mouse Wheel Down";
}

QString QtKeySequences::resetZoom()
{
	return toString(Qt::Key_0);
}

QString QtKeySequences::expandOrCollapseNodeWithMouse()
{
	return toString(Qt::ShiftModifier) + "Left Click";
}

QList<QKeySequence> QtKeySequences::back()
{
	return {
		StandardKey::Back,
		Qt::Key_Z,
		Qt::Key_Y,
		Qt::Key_Backspace
	};
}

QList<QKeySequence> QtKeySequences::forward()
{
	return {
		StandardKey::Forward,
		Qt::ShiftModifier | Qt::Key_Z,
		Qt::ShiftModifier | Qt::Key_Y
	};
}

QKeySequence QtKeySequences::bookmarkActiveSymbol()
{
	return StandardKey::Save;
}

QKeySequence QtKeySequences::bookmarkManager()
{
	return Qt::ControlModifier | Qt::Key_B;
}

QString QtKeySequences::showInIDEWithMouse()
{
	return toString(Qt::ControlModifier) + "Left Click";
}

QString QtKeySequences::openInNewTabWithMouse()
{
	return toString(Qt::ControlModifier) + toString(Qt::ShiftModifier) + "Left Click";
}

QString QtKeySequences::showDefinitionWithMouse()
{
	return toString(Qt::ControlModifier) + toString(Qt::AltModifier) + "Left Click";
}

QString QtKeySequences::hideWithMouse()
{
	return toString(Qt::AltModifier) + "Left Click";
}

