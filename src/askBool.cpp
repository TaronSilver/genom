#include "askBool.hpp"
#include "../build/ui_askBool.h"

askBool::askBool(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::askBool)
{
    ui->setupUi(this);
}

askBool::~askBool()
{
    delete ui;
}

bool askBool::getBool(){
    return ui->checkBox->isChecked();
}

void askBool::on_buttonLeave_clicked(){
    this->close();
}
