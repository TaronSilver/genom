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
    unsigned int matrixChoice = 1;
void matrixFromSequence::on_chooseMatrix_currentIndexChanged(int){
    matrixChoice = ui->chooseMatrix->currentIndex()+1;
}

unsigned int matrixFromSequence::getMatrixChoice(){
    unsigned int choice = matrixChoice;
    matrixChoice = 1;
    return choice;
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
    unsigned int pos = position;
    position = 1;
    return pos;
}

unsigned int matrixFromSequence::getLength(){
    unsigned le = length;
    length = 0;
    return le;
}

bool matrixFromSequence::getBool(){
    bool check = checkBox;
    checkBox = false;
    return check;
}

void matrixFromSequence::on_buttonSave_clicked(){
    if( length == 0 ) QMessageBox::critical(this, "Length Value Invalid", "Your value for your length is impossible, please try again.");
    else if( position != 0 ) this->close();
}
