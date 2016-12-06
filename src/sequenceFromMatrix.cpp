#include "sequenceFromMatrix.hpp"
#include "../build/ui_sequenceFromMatrix.h"

sequenceFromMatrix::sequenceFromMatrix(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sequenceFromMatrix)
{
    ui->setupUi(this);
}

sequenceFromMatrix::~sequenceFromMatrix()
{
    delete ui;
}

double cutoff;
void sequenceFromMatrix::on_spinDouble_valueChanged(){
    cutoff = ui->spinDouble->value();
}

double sequenceFromMatrix::getCutoff(){
    return cutoff;
}

void sequenceFromMatrix::on_buttonSave_clicked(){
    this->close();
}


bool rex(false);
void sequenceFromMatrix::on_checkBox_stateChanged(){
    if(ui->checkBox->isChecked()){
        rex = !rex;
    }
    else{
        rex = !rex;
    }
}

bool sequenceFromMatrix::getBool(){
    return rex;
}
