#pragma once

#include <QtWidgets/QWidget>

#include "windows.h"

class TitleBar;

class FramelessWindow : public QWidget
{
public:
    FramelessWindow(QWidget* parent = Q_NULLPTR);
protected:
    bool nativeEvent(const QByteArray& eventType, void* message, long* result);
    void changeEvent(QEvent* event);
private:
    bool isWindowMaximized(HWND hWnd);
    void monitorNCCALCSIZE(MSG* msg);

    TitleBar* titleBar;
    MONITORINFO monitorInfo;
    RECT monitor_rect;
    RECT work_area;
};

