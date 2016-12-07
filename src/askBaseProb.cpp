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

unsigned int baseChoice(0);
void askBaseProb::on_chooseBase_currentIndexChanged(int){
    if(ui->chooseBase->currentIndex()==3){
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
    unsigned int value=baseChoice;
    baseChoice=0;
    if (value == 0) return 1;
    else if (value == 1) return 3;
    else if(value ==2) return 2;
    else if(value==3) return 0;
    else return 1;
}

double probA(0);
double probC(0);
double probG(0);
double probT(0);

double askBaseProb::getProbA() {
    double prob1=probA;
    probA=0;
    return prob1;
}
double askBaseProb::getProbC(){
    double prob2=probC;
    probC=0;
    return prob2;
}

double askBaseProb::getProbG(){
    double prob3=probG;
    probG=0;
    return prob3;
}

double askBaseProb::getProbT(){
    double prob4=probT;
    probT=0;
    return prob4;
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
    unsigned int choice1 = matrixChoiceS;
    matrixChoiceS = 1;
    return choice1;
}
