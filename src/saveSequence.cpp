#include "saveSequence.hpp"
#include "../build/ui_saveSequence.h"

SaveSequence::SaveSequence(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveSequence)
{
    ui->setupUi(this);
}

SaveSequence::~SaveSequence()
{
    delete ui;
}

bool SaveSequence::getCheckbox(){
    return ui->checkBox->isChecked();
}

std::string SaveSequence::getFileName(){
    return ui->editFileName->text().toStdString();
}

void SaveSequence::on_buttonLeave_clicked(){
    this->close();
}
