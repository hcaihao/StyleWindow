#pragma once

#include <QWidget>
#include <QFile>
#include <QToolButton>
#include <QMouseEvent>

class TitleBar : public QWidget
{
	Q_OBJECT

public:
	TitleBar(QWidget *parent);
	~TitleBar();
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
private:
	void toggleMaxState();
};
