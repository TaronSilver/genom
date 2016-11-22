#include "savematrix.hpp"
#include "../build/ui_savematrix.h"

saveMatrix::saveMatrix(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveMatrix)
{
    ui->setupUi(this);
}

saveMatrix::~saveMatrix()
{
    delete ui;
}

unsigned int saveMatrix::getMatrixChoice(){
    return matrixChoice;
}

std::string saveMatrix::getFileName(){
    return ui->editFileName->text().toStdString();
}

void saveMatrix::on_buttonSave_clicked(){
    this->close();
}

void saveMatrix::on_chooseMatrix_currentIndexChanged(int){
    matrixChoice = ui->chooseMatrix->currentIndex()+1;
}

