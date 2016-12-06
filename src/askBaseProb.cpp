#include "askBaseProb.hpp"
#include "ui_askBaseProb.h"

askBaseProb::askBaseProb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::askBaseProb)
{
    ui->setupUi(this);
}

askBaseProb::~askBaseProb()
{
    delete ui;
}

unsigned int baseChoice;
void askBaseProb::on_chooseBase_currentIndexChanged(int){
    if(ui->chooseBase->currentIndex()==2){
        ui->spinA->setEnabled(true);
        ui->spinC->setEnabled(true);
        ui->spinG->setEnabled(true);
        ui->spinT->setEnabled(true);
    }
    else{
        ui->spinA->setEnabled(false);
        ui->spinC->setEnabled(false);
        ui->spinG->setEnabled(false);
        ui->spinT->setEnabled(false);
    }
    baseChoice = ui->chooseBase->currentIndex();
}

unsigned int askBaseProb::getBaseChoiceFinal(){
    if (baseChoice == 0) return 1;
    else if (baseChoice == 1) return 3;
    else if(baseChoice ==2) return 2;
    else if(baseChoice==3) return 0;
}

double probA;
double probC;
double probG;
double probT;

double askBaseProb::getProbA() {
    return probA;
}
double askBaseProb::getProbC(){
    return probC;
}

double askBaseProb::getProbG(){
    return probG;
}

double askBaseProb::getProbT(){
    return probG;
}

void askBaseProb::on_spinA_valueChanged(double){
    probA = ui->spinA->value();
}

void askBaseProb::on_spinC_valueChanged(double){
    probC = ui->spinC->value();
}

void askBaseProb::on_spinG_valueChanged(double){
    probG = ui->spinG->value();
}

void askBaseProb::on_spinT_valueChanged(double){
    probT = ui->spinT->value();
}

void askBaseProb::on_buttonSave_clicked(){
    this->close();
}

unsigned int matrixChoiceS = 1;
void askBaseProb::on_chooseMatrix_currentIndexChanged(int){
matrixChoiceS = ui->chooseMatrix->currentIndex()+1;
}

unsigned int askBaseProb::getMatrixChoice(){
return matrixChoiceS;
}
