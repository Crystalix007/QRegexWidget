#include "qregexwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QRegexWidget w{};
    w.show();

    return app.exec();
}

