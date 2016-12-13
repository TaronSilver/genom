#include "correlate.hpp"
#include "../build/ui_correlate.h"

Correlate::Correlate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Correlate)
{
    ui->setupUi(this);
}

Correlate::~Correlate()
{
    delete ui;
}
