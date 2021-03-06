#ifndef QREGEXWIDGET_H
#define QREGEXWIDGET_H

#include <QMainWindow>

namespace Ui {
class QRegexWidget;
}

class QRegexWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit QRegexWidget(QWidget *parent = 0);
    ~QRegexWidget();

protected:
	void doMatch();
	void clearMatches();

private:
    Ui::QRegexWidget *ui;
};

#endif // QREGEXWIDGET_H
