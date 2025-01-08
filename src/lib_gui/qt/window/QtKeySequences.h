#ifndef QT_KEY_SEQUENCES_H
#define QT_KEY_SEQUENCES_H

#include <QKeySequence>
#include <QList>

QString toString(const QKeySequence &sequence);
const QString &toString(const QString &s);

class QtKeySequences final {
public:
	// Project keys:

	static QKeySequence newProject();
	static QKeySequence openProject();
	static QKeySequence exit();

	// Edit keys:

	static QKeySequence refresh();
	static QKeySequence fullRefresh();
	static QKeySequence findSymbol();
	static QKeySequence findText();
	static QList<QKeySequence> findOnScreen();
	static QKeySequence nextReference();
	static QKeySequence previousReference();
	static QKeySequence nextLocalReference();
	static QKeySequence previousLocalReference();
	static QKeySequence customTrailDialog();
	static QKeySequence toOverview();
	static QKeySequence saveGraphAsImage();
	static QKeySequence preferences();

	// View keys:

	static QKeySequence newTab();
	static QList<QKeySequence> closeTab();
	static QKeySequence selectNextTab();
	static QKeySequence selectPreviousTab();
	static QKeySequence largerFont();
	static QKeySequence smallerFont();
	static QKeySequence resetFontSize();

	static QString switchGraphCodeFocus();
	static QList<QString> moveCodeFocus();
	static QList<QString> moveReferenceFocus();
	static QList<QString> activateLocation();
	static QList<QString> activateLocationNewTab();
	static QList<QString> scrollCodeArea();
	static QList<QString> moveNodeFocus();
	static QList<QString> moveEdgeFocus();
	static QList<QString> activateNodeEdge();
	static QList<QString> expandOrCollapseNode();
	static QList<QString> activateNodeNewTab();
	static QList<QString> scrollGraphArea();
	static QString refreshUI();

	static QList<QString> zoomIn();
	static QList<QString> zoomOut();
	static QString resetZoom();

	// History keys:

	static QList<QKeySequence> back();
	static QList<QKeySequence> forward();

	// Bookmark keys:

	static QKeySequence bookmarkActiveSymbol();
	static QKeySequence bookmarkManager();

	// Pseudo mouse keys:

	static QString zoomInWithMouse();
	static QString zoomOutWithMouse();
	static QString expandOrCollapseNodeWithMouse();
	static QString showInIDEWithMouse();
	static QString openInNewTabWithMouse();
	static QString showDefinitionWithMouse();
	static QString hideWithMouse();
};

#endif // QTKEYSEQUENCES_H
