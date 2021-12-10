#include "stdafx.h"

void RefreshStyle(QWidget* widget, const char* name, QVariant value)
{
	widget->setProperty(name, value);

	qApp->style()->unpolish(widget);
	qApp->style()->polish(widget);

	widget->update();
}

void LoadStyle(QString filePath)
{
	QString styleSheet;

	QFile file(filePath);
	if (file.open(QFile::ReadOnly))
	{
		styleSheet.append(QString::fromLocal8Bit(file.readAll()));

		file.close();
	}

	qApp->setStyleSheet(styleSheet);

}