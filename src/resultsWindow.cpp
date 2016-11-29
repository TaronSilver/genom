#include "resultsWindow.hpp"
#include "ui_resultsWindow.h"

resultsWindow::resultsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resultsWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setText("whatever");
}

resultsWindow::~resultsWindow()
{
    delete ui;
}
