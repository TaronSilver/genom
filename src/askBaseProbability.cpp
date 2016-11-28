#include "askBaseProbability.hpp"
#include "../build/ui_askBaseProbability.h"

#include <QMessageBox>
#include <iostream>
using namespace  std;

askBaseProbability::askBaseProbability(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::askBaseProbability)
{
    ui->setupUi(this);
}

askBaseProbability::~askBaseProbability()
{
    delete ui;
}

void askBaseProbability::on_chooseBase_currentIndexChanged(int){
    if(ui->chooseBase->currentIndex()==2){
        ui->spinA->setEnabled(true);
        ui->spinC->setEnabled(true);
        ui->spinG->setEnabled(true);
        ui->spinT->setEnabled(true);
    }
    baseChoice = ui->chooseBase->currentIndex();
}

int askBaseProbability::getBaseChoice(){
    return baseChoice;
}

double askBaseProbability::getProbA() {
    return probA;
}
double askBaseProbability::getProbC(){
    return probC;
}

double askBaseProbability::getProbG(){
    return probG;
}

double askBaseProbability::getProbT(){
    return probG;
}

void askBaseProbability::on_spinA_valueChanged(double){
    probA = ui->spinA->value();
}

void askBaseProbability::on_spinC_valueChanged(double){
    probC = ui->spinC->value();
}

void askBaseProbability::on_spinG_valueChanged(double){
    probG = ui->spinG->value();
}

void askBaseProbability::on_spinT_valueChanged(double){
    probT = ui->spinT->value();
}

unsigned int askBaseProbability::getMatrixChoice(){
    return matrixChoice;
}

std::string askBaseProbability::getFileName(){
    return ui->editFileName->text().toStdString();
}
//std::string output=getFileName();
std::string askBaseProbability::getOutputName(){
    //return output;
}

void askBaseProbability::on_checkBox_stateChanged(){
    if(ui->checkBox->isChecked()){
        ui->intLength->setEnabled(true);
    }
}

void askBaseProbability::on_chooseMatrix_currentIndexChanged(int){
    matrixChoice = ui->chooseMatrix->currentIndex()+1;
}

unsigned int position=1;
unsigned int length=0;

void askBaseProbability::on_intPosition_valueChanged(int){
    position = ui->intPosition->value();
    cout <<endl <<position;
}

void askBaseProbability::on_intLength_valueChanged(int){
    length = ui->intLength->value();
    cout <<endl <<length;
}

unsigned int askBaseProbability::getPosition(){
    cout <<endl <<"Position finale :" <<position;
    return position;
}

unsigned int askBaseProbability::getLength(){
    cout <<endl <<"Length finale :" <<length;
    return length;
}
bool checkBox;
void askBaseProbability::getCheckState(){
    checkBox = ui->checkBox->isChecked();
}

bool askBaseProbability::getBool(){
    return checkBox;
}

void askBaseProbability::on_buttonSave_clicked(){
    if( length == 0 ) QMessageBox::critical(this, "Length Value Invalid", "Your value for your length is impossible, please try again.");
    else if( position != 0 ) this->close();
}
