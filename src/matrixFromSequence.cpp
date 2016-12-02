#include "matrixFromSequence.hpp"
#include "../build/ui_matrixFromSequence.h"

#include <QMessageBox>
#include <iostream>

matrixFromSequence::matrixFromSequence(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::matrixFromSequence)
{
    ui->setupUi(this);
}

matrixFromSequence::~matrixFromSequence()
{
    delete ui;
}
    unsigned int baseChoiceFinal;
void matrixFromSequence::on_chooseBase_currentIndexChanged(int){
    if(ui->chooseBase->currentIndex()==2){
        ui->spinA->setEnabled(true);
        ui->spinC->setEnabled(true);
        ui->spinG->setEnabled(true);
        ui->spinT->setEnabled(true);
    }
    baseChoice = ui->chooseBase->currentIndex();
    baseChoiceFinal=baseChoice;
}

unsigned int matrixFromSequence::getBaseChoiceFinal(){
   return  baseChoiceFinal;
}

int matrixFromSequence::getBaseChoice(){
    return baseChoice;
}

double matrixFromSequence::getProbA() {
    return probA;
}
double matrixFromSequence::getProbC(){
    return probC;
}

double matrixFromSequence::getProbG(){
    return probG;
}

double matrixFromSequence::getProbT(){
    return probG;
}

void matrixFromSequence::on_spinA_valueChanged(double){
    probA = ui->spinA->value();
}

void matrixFromSequence::on_spinC_valueChanged(double){
    probC = ui->spinC->value();
}

void matrixFromSequence::on_spinG_valueChanged(double){
    probG = ui->spinG->value();
}

void matrixFromSequence::on_spinT_valueChanged(double){
    probT = ui->spinT->value();
}

unsigned int matrixFromSequence::getMatrixChoice(){
    return matrixChoice;
}

bool checkBox(false);
void matrixFromSequence::on_checkBox_stateChanged(){
    if(ui->checkBox->isChecked()){
        ui->intLength->setEnabled(true);
        checkBox = !checkBox;
    }
    else{
        ui->intLength->setEnabled(false);
        checkBox = !checkBox;
    }
}

void matrixFromSequence::on_chooseMatrix_currentIndexChanged(int){
    matrixChoice = ui->chooseMatrix->currentIndex()+1;
}

unsigned int position=1;
unsigned int length=0;

void matrixFromSequence::on_intPosition_valueChanged(int){
    position = ui->intPosition->value();
}

void matrixFromSequence::on_intLength_valueChanged(int){
    length = ui->intLength->value();
}

unsigned int matrixFromSequence::getPosition(){
    return position;
}

unsigned int matrixFromSequence::getLength(){
    return length;
}

bool matrixFromSequence::getBool(){
    return checkBox;
}

void matrixFromSequence::on_buttonSave_clicked(){
    if( length == 0 ) QMessageBox::critical(this, "Length Value Invalid", "Your value for your length is impossible, please try again.");
    else if( position != 0 ) this->close();
}
