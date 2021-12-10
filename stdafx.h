#include <QtWidgets>

#define BORDER_WIDTH 5
#define TITLE_HEIGHT 38
#define BUTTON_WIDTH 38

#define DEFAULT_STYLE ":/StyleWindow/Resources/default.qss"

extern void RefreshStyle(QWidget* widget, const char* name, QVariant value);
extern void LoadStyle(QString filePath);