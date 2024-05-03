#ifndef QT_TOOLTIP_H
#define QT_TOOLTIP_H

#include <QFrame>

struct TooltipInfo;

class QtTooltip: public QFrame
{
	Q_OBJECT

public:
	QtTooltip(QWidget* parent = nullptr);
	~QtTooltip() override;

	void setTooltipInfo(const TooltipInfo& info);

	void setParentView(QWidget* parentView);

	bool isHovered() const;

public slots:
	virtual void show();
	virtual void hide(bool force = false);

protected:
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;

private:
	void addTitle(const QString& title, int count, const QString& countText);
	void addWidget(QWidget* widget);

	void clearLayout(QLayout* layout);

	QWidget* m_parentView;
	QPoint m_offset;

	bool m_isHovered;
};

#endif	  // QT_TOOLTIP_H
