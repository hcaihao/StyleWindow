#include "stdafx.h"
#include "framelesswindow.h"
#include "titlebar.h"
#include "windoweffect.h"

FramelessWindow::FramelessWindow(QWidget* parent)
	: QWidget(parent)
{
	memset(&monitorInfo, 0, sizeof(MONITORINFO));
	monitorInfo.cbSize = sizeof(MONITORINFO);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

	titleBar = new TitleBar(this);
	titleBar->setObjectName("titleBar");
	titleBar->setStyleSheet("background: rgb(47,70,146);");
	layout->addWidget(titleBar);

	QLabel* testLabel = new QLabel(this);
	testLabel->setObjectName("testLabel");
	testLabel->setStyleSheet("background: rgb(240, 240, 240);");
	layout->addWidget(testLabel);

	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

	WindowEffect::addWindowAnimation((HWND)winId());
	WindowEffect::addShadowEffect((HWND)winId());

	connect(windowHandle(), &QWindow::screenChanged, this, [=] {
		auto hWnd = reinterpret_cast<HWND>(windowHandle()->winId());
		SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
		});
}

bool FramelessWindow::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	MSG* msg = reinterpret_cast<MSG*>(message);
	if (msg->message == WM_NCHITTEST)
	{
		int xPos = (LOWORD(msg->lParam) - frameGeometry().x()) % 65536;
		int yPos = HIWORD(msg->lParam) - frameGeometry().y();
		int w = width();
		int h = height();
		bool lx = xPos < BORDER_WIDTH;
		bool rx = xPos + 9 > w - BORDER_WIDTH;
		bool ty = yPos < BORDER_WIDTH;
		bool by = yPos > h - BORDER_WIDTH;

		if (lx && ty)
		{
			*result = HTTOPLEFT;
			return true;
		}
		else if (rx && by)
		{
			*result = HTBOTTOMRIGHT;
			return true;
		}
		else if (rx && ty) {
			*result = HTTOPRIGHT;
			return true;
		}
		else if (lx && by) {
			*result = HTBOTTOMLEFT;
			return true;
		}
		else if (ty) {
			*result = HTTOP;
			return true;
		}
		else if (by) {
			*result = HTBOTTOM;
			return true;
		}
		else if (lx) {
			*result = HTLEFT;
			return true;
		}
		else if (rx) {
			*result = HTRIGHT;
			return true;
		}
	}
	else if (msg->message == WM_NCCALCSIZE)
	{
		if (isWindowMaximized(msg->hwnd))
		{
			monitorNCCALCSIZE(msg);
		}

		*result = HTNOWHERE;
		return true;
	}
	else if (msg->message == WM_GETMINMAXINFO)
	{
		if (isWindowMaximized(msg->hwnd))
		{
			RECT window_rect;
			if (!GetWindowRect(msg->hwnd, &window_rect))
			{
				*result = HTNOWHERE;
				return false;
			}

			HMONITOR hMonitor = MonitorFromRect(&window_rect, MONITOR_DEFAULTTONEAREST);
			if (!hMonitor)
			{
				*result = HTNOWHERE;
				return false;
			}

			GetMonitorInfoW(hMonitor, &monitorInfo);
			RECT monitor_rect = monitorInfo.rcMonitor;
			RECT work_area = monitorInfo.rcWork;

			LPMINMAXINFO info = reinterpret_cast<LPMINMAXINFO>(msg->lParam);

			info->ptMaxSize.x = work_area.right - work_area.left;
			info->ptMaxSize.y = work_area.bottom - work_area.top;
			info->ptMaxTrackSize.x = info->ptMaxSize.x;
			info->ptMaxTrackSize.y = info->ptMaxSize.y;

			info->ptMaxPosition.x = abs(window_rect.left - monitor_rect.left);
			info->ptMaxPosition.y = abs(window_rect.top - monitor_rect.top);
			*result = HTCLIENT;
			return true;
		}
	}

	return QWidget::nativeEvent(eventType, message, result);
}

bool FramelessWindow::isWindowMaximized(HWND hWnd)
{
	WINDOWPLACEMENT wp;
	wp.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(hWnd, &wp);
	return wp.showCmd == SW_MAXIMIZE;
}

void FramelessWindow::monitorNCCALCSIZE(MSG* msg)
{
	HMONITOR hMonitor = MonitorFromWindow(msg->hwnd, MONITOR_DEFAULTTONEAREST);
	if (hMonitor && GetMonitorInfoW(hMonitor, &monitorInfo))
	{
		NCCALCSIZE_PARAMS& params = *reinterpret_cast<NCCALCSIZE_PARAMS*>(msg->lParam);
		params.rgrc[0].left = monitorInfo.rcWork.left;
		params.rgrc[0].top = monitorInfo.rcWork.top;
		params.rgrc[0].right = monitorInfo.rcWork.right;
		params.rgrc[0].bottom = monitorInfo.rcWork.bottom;
	}
}