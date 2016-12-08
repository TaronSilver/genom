#include "matrixFromSequence.hpp"
#include "../build/ui_matrixFromSequence.h"

#include <iostream>
#include <QMessageBox>

bool checkBox;
unsigned int matrixChoice;
unsigned int position;
unsigned int length;
matrixFromSequence::matrixFromSequence(QWidget *parent) :
    QDialog(parent), ui(new Ui::matrixFromSequence)
{
    ui->setupUi(this);
    checkBox=false;
    matrixChoice = 1;
    position=1;
    length=0;
}

matrixFromSequence::~matrixFromSequence() {
    delete ui;
}

void matrixFromSequence::on_checkBox_stateChanged() {
    if(ui->checkBox->isChecked()){
        ui->intLength->setEnabled(true);
        checkBox = !checkBox;
    }
    else{
        ui->intLength->setEnabled(false);
        checkBox = !checkBox;
    }
}

void matrixFromSequence::on_chooseMatrix_currentIndexChanged(int) {
    matrixChoice = ui->chooseMatrix->currentIndex()+1;
}

void matrixFromSequence::on_intPosition_valueChanged(int) {
    position = ui->intPosition->value();
}

void matrixFromSequence::on_intLength_valueChanged(int) {
    length = ui->intLength->value();
}

unsigned int matrixFromSequence::getPosition() {
    return position;
}

unsigned int matrixFromSequence::getLength() {
    return length;
}

bool matrixFromSequence::getBool() {
    return checkBox;
}

void matrixFromSequence::on_buttonSave_clicked() {
    if( length == 0 ) QMessageBox::critical(this, "Length Value Invalid", "Your value for your length is impossible, please try again.");
    else if( position != 0 ) this->close();
}
