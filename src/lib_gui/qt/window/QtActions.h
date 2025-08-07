#ifndef QT_KEY_SEQUENCES_H
#define QT_KEY_SEQUENCES_H

#include <QCoreApplication>
#include <QKeySequence>
#include <QList>

// This list contains only the keys which are specifically handled in various keyPressEvent/keyReleaseEvent:

constexpr Qt::Key KEY_HELP                     = Qt::Key_F1;
constexpr Qt::Key KEY_COPY_TO_CLIPBOARD        = Qt::Key_C;
constexpr Qt::Key KEY_RESET                    = Qt::Key_0;
constexpr Qt::Key KEY_BOOKMARK                 = Qt::Key_B;
constexpr Qt::Key KEY_OVERVIEW                 = Qt::Key_Home;
constexpr Qt::Key KEY_CLOSE_TAB                = Qt::Key_F4;
constexpr Qt::Key KEY_REFRESH_UI               = Qt::Key_R;
constexpr Qt::Key KEY_PREFERENCES              = Qt::Key_Comma;
constexpr Qt::Key KEY_CUSTOM_TRAIL_DIALOG      = Qt::Key_U;
constexpr Qt::Key KEY_NEXT_PREVIOUS_REFERENCE  = Qt::Key_G;

// History keys:

constexpr Qt::Key KEY_HISTORY_UNDO        = Qt::Key_Backspace;
constexpr Qt::Key KEY_HISTORY_UNDO_REDO_1 = Qt::Key_Y;
constexpr Qt::Key KEY_HISTORY_UNDO_REDO_2 = Qt::Key_Z;

constexpr Qt::Key KEY_ACTIVATE_FOCUS_1 = Qt::Key_Return;
constexpr Qt::Key KEY_ACTIVATE_FOCUS_2 = Qt::Key_E;

constexpr Qt::Key KEY_SCREEN_SEARCH_1 = Qt::Key_Slash;
constexpr Qt::Key KEY_SCREEN_SEARCH_2 = Qt::Key_Question;

// Vim keys:

constexpr Qt::Key KEY_VIM_UP    = Qt::Key_K;
constexpr Qt::Key KEY_VIM_DOWN  = Qt::Key_J;
constexpr Qt::Key KEY_VIM_LEFT  = Qt::Key_H;
constexpr Qt::Key KEY_VIM_RIGHT = Qt::Key_L;

// Game/WASD keys:

constexpr Qt::Key KEY_GAME_UP    = Qt::Key_W;
constexpr Qt::Key KEY_GAME_DOWN  = Qt::Key_S;
constexpr Qt::Key KEY_GAME_LEFT  = Qt::Key_A;
constexpr Qt::Key KEY_GAME_RIGHT = Qt::Key_D;

class QtActions final
{
	Q_DECLARE_TR_FUNCTIONS(QtActions)

public:
	class Info
	{
	public:
		Info(const QString &text, const QString &shortcut);
		Info(const QString &text, const QList<QString> &shortcuts);

		Info(const QString &text, const QKeySequence &shortcut);
		Info(const QString &text, const QList<QKeySequence> &shortcuts);

		QString text() const;
		QString shortcut() const;
		QString tooltip() const;
		QString menuText() const;

		// For 'Keyboard shortcuts...' table:
		QString name() const; // without '&' and/or '...'
		QString shortcuts() const;

	private:
		const QString m_text;
		const QString m_tooltip;
		const QList<QString> m_shortcuts;
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
	static Info saveAsImage();
	static Info copyToClipboard();

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
	static Info bookmarkNode();

	// Screen search keys:

	static Info findOnScreen();
	static Info screenSearchNext();
	static Info screenSearchPrevious();
	static Info screenSearchClose();

	// 'Help' keys:

	static Info showKeyboardShortcuts();
	static Info showLegend();

	// Miscellaneous:

	static Info textEncoding();

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
};

#endif
