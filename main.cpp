#include "stdafx.h"
#include "stylewindow.h"
#include <QtWidgets/QApplication>

#pragma comment(lib, "Dwmapi.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoadStyle(DEFAULT_STYLE);

    StyleWindow w;
    w.show();
    return a.exec();
}
