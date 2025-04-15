#ifndef QT_KEY_SEQUENCES_H
#define QT_KEY_SEQUENCES_H

#include <QCoreApplication>
#include <QKeySequence>
#include <QList>

class QtActions final {
	Q_DECLARE_TR_FUNCTIONS(QtActions)
	
public:
	static const char SHORTCUT_SEPARATOR[];
	
	class Info {
		public:
			Info(QString text, QString shortcut);
			Info(QString text, QList<QString> shortcuts);
			
			Info(QString text, QKeySequence shortcut);
			Info(QString text, QList<QKeySequence> shortcuts);
			
			Info(QString text, QString shortcut1, QString shortcut2);
			
			QString text() const;
			QString plainText() const; // without '&' and/or '...'
			
			QString shortcut() const;
			QList<QString> shortcuts() const;
			
			QString tooltip() const;
			
		private:
			QString m_text;
			QString m_tooltip;
			QList<QString> m_shortcuts;
	};
	// Project keys:

	static Info newProject();
	static Info openProject();
	static Info exit();

	// Edit keys:
	
	static Info refresh();
	static Info fullRefresh();
	static Info findSymbol();
	static Info executeFindSymbol();
	static Info findText();
	static Info nextReference();
	static Info previousReference();
	static Info nextLocalReference();
	static Info previousLocalReference();
	static Info customTrailDialog();
	static Info toOverview();
	static Info saveGraphAsImage();
	static Info preferences();

	// View keys:
	
	static Info newTab();
	static Info closeTab();
	static Info selectNextTab();
	static Info selectPreviousTab();
	static Info largerFont();
	static Info smallerFont();
	static Info resetFontSize();
	
	static Info switchGraphCodeFocus();
	static Info moveCodeFocus();
	static Info moveReferenceFocus();
	static Info activateLocation();
	static Info activateLocationNewTab();
	static Info scrollCodeArea();
	static Info moveNodeFocus();
	static Info moveEdgeFocus();
	static Info activateNodeEdge();
	static Info expandOrCollapseNode();
	static Info activateNodeNewTab();
	static Info scrollGraphArea();
	static Info refreshUI();
	
	static Info zoomIn();
	static Info zoomOut();
	static Info resetZoom();

	// History keys:
	
	static Info back();
	static Info forward();

	// Bookmark keys:

	static Info bookmarkActiveSymbol();
	static Info bookmarkManager();
	static Info activateBookmark();
	
	// Screen search keys:
	
	static Info findOnScreen();
	static Info screenSearchNext();
	static Info screenSearchPrevious();
	static Info screenSearchClose();
	
	// Pseudo mouse keys:
	
	static Info zoomInWithMouse();
	static Info zoomOutWithMouse();
	static Info expandNodeWithMouse();
	static Info collapseNodeWithMouse();
	static Info showInIDEWithMouse();
	static Info openInNewTabWithMouse();
	static Info showDefinitionWithMouse();
	static Info hideNodeWithMouse();
	static Info hideEdgeWithMouse();
	
	// 'Help' keys:
	
	static Info showKeyboardShortcuts();
	static Info showLegend();
};

#endif
