#include "askposandlength.hpp"
#include "../build/ui_askposandlength.h"


askPosAndLength::askPosAndLength(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::askPosAndLength) {
    ui->setupUi(this);
}

askPosAndLength::~askPosAndLength() {
    delete ui;
}

void askPosAndLength::on_intPosition_valueChanged(int) {
    position = ui->intPosition->value();
}

void askPosAndLength::on_intLength_valueChanged(int) {
    length = ui->intLength->value();
}

void askPosAndLength::on_setValues_clicked() {
    if( length == 0 ) QMessageBox::critical(this, "Length Value Invalid", "Your value for your length is impossible, please try again.");
    else if( position != 0 ) this->close();
}

unsigned int askPosAndLength::getPosition(){
    return position;
}

unsigned int askPosAndLength::getLength(){
    return length;
}
