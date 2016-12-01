#include "resultsWindow.hpp"
#include "ui_resultsWindow.h"

#include <QTextStream>
#include <iostream>

#include "window.hpp"

resultsWindow::resultsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resultsWindow)
{
    ui->setupUi(this);

    //The output file is saved one directory before, thus the addtiion of ../
    QString filename = "../" + QString::fromStdString(Window::getOutputName());
    QFile file(filename);

    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream ReadFile(&file);
    ui->textBrowser->setText(ReadFile.readAll());
}

resultsWindow::~resultsWindow()
{
    delete ui;
}
