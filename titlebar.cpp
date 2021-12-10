#include "stdafx.h"
#include "titlebar.h"
#include "windows.h"

#include <QDebug>

TitleBar::TitleBar(QWidget* parent)
	: QWidget(parent)
{
	//resize(1360, 38);
	setFixedHeight(TITLE_HEIGHT);
	setAttribute(Qt::WA_StyledBackground);

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

	QLabel* logoLabel = new QLabel(this);
	logoLabel->setObjectName("logoLabel");
	layout->addWidget(logoLabel);
	layout->addStretch(1);

	QToolButton* minToolButton = new QToolButton(this);
	minToolButton->setObjectName("minToolButton");
	connect(minToolButton, &QToolButton::clicked, this->window(), &QWidget::showMinimized);
	layout->addWidget(minToolButton);

	QToolButton* maxToolButton = new QToolButton(this);
	maxToolButton->setObjectName("maxToolButton");
	connect(maxToolButton, &QToolButton::clicked, this, &TitleBar::toggleMaxState);
	maxToolButton->setProperty("MaxState", false);
	layout->addWidget(maxToolButton);

	QToolButton* closeToolButton = new QToolButton(this);
	closeToolButton->setObjectName("closeToolButton");
	connect(closeToolButton, &QToolButton::clicked, this->window(), &QWidget::close);
	layout->addWidget(closeToolButton);
}

TitleBar::~TitleBar()
{
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
	toggleMaxState();
}

void TitleBar::mousePressEvent(QMouseEvent* event)
{
	ReleaseCapture();
	SendMessage((HWND)window()->winId(), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
	event->ignore();
}

void TitleBar::toggleMaxState()
{
	if (window()->isMaximized())
	{
		window()->showNormal();
		RefreshStyle(findChild<QToolButton*>("maxToolButton"), "MaxState", false);
	}
	else
	{
		window()->showMaximized();
		RefreshStyle(findChild<QToolButton*>("maxToolButton"), "MaxState", true);
	}
}