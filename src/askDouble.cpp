#include "askDouble.hpp"
#include "../build/ui_askDouble.h"

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

double askDouble::getDouble(){
    return Double;
}

void askDouble::on_setDouble_clicked(){
    this->close();
}

void askDouble::on_spinDouble_valueChanged(double){
    Double = ui->spinDouble->value();
}
