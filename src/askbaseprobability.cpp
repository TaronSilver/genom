#include "askbaseprobability.hpp"
#include "../build/ui_askbaseprobability.h"

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

void askBaseProbability::on_buttonLeave_clicked(){
    this->close();
}