#include "matrixFromSequence.hpp"
#include "../build/ui_matrixFromSequence.h"

#include <iostream>
#include <QMessageBox>

bool checkBox;
unsigned int matrixChoice;
unsigned int position;
unsigned int length;
unsigned int sequenceOrigin;
matrixFromSequence::matrixFromSequence(QWidget *parent) :
    QDialog(parent), ui(new Ui::matrixFromSequence)
{
    ui->setupUi(this);
    checkBox=false;
    matrixChoice = 1;
    position=1;
    length=0;
    sequenceOrigin=1;
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

void matrixFromSequence::on_chooseSequenceOrigin_currentIndexChanged(int){
    sequenceOrigin = ui->chooseSequenceOrigin->currentIndex()+1;
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

unsigned int matrixFromSequence::getSequenceOrigin(){
    return sequenceOrigin;
}

void matrixFromSequence::on_buttonSave_clicked() {
    if( length == 0 ){
        int choice = QMessageBox::question(this, "EM Algorithm", "You haven't chosen a lenght value. Press Ok if you want to use EM Algorithm. Press Cancel if you wish to modify this.", QMessageBox::Ok | QMessageBox::Cancel);

        if (choice == QMessageBox::Ok) this->close();
        else if (choice == QMessageBox::Cancel){}
    }
    else if( position != 0 ) this->close();
}
