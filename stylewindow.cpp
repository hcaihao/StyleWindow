#include "stdafx.h"
#include "stylewindow.h"
#include "stdafx.h"

StyleWindow::StyleWindow(QWidget* parent)
    : FramelessWindow(parent)
{
    resize(800, 600);
}
