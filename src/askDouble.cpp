include "askDouble.hpp"
#include "../build/ui_askDouble.h"

askDouble::askDouble(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::askDouble)
{
    ui->setupUi(this);
}
/*
sequenceFromMatrix::~sequenceFromMatrix()
{
    delete ui;
}

double sequenceFromMatrix::getDouble(){
    return Double;
}

void sequenceFromMatrix::on_setDouble_clicked(){
    this->close();
}

void sequenceFromMatrix::on_spinDouble_valueChanged(double){
    Double = ui->spinDouble->value();
}
*/
