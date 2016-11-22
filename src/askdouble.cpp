#include "askdouble.hpp"
#include "../build/ui_askdouble.h"

askDouble::askDouble(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::askDouble)
{
    ui->setupUi(this);
}

askDouble::~askDouble()
{
    delete ui;
}

double askDouble::getCutoff(){
    return cutoff;
}

void askDouble::on_setCutoff_clicked(){
    this->close();
}

void askDouble::on_spinCutoff_valueChanged(double){
    cutoff = ui->spinCutoff->value();
}
