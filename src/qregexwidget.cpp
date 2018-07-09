#include "qregexwidget.h"
#include "ui_qregexwidget.h"

QRegexWidget::QRegexWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QRegexWidget)
{
    ui->setupUi(this);
}

QRegexWidget::~QRegexWidget()
{
    delete ui;
}
