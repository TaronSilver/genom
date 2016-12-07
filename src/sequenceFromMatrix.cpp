#include "sequenceFromMatrix.hpp"
#include "../build/ui_sequenceFromMatrix.h"

sequenceFromMatrix::sequenceFromMatrix(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sequenceFromMatrix)
{
    ui->setupUi(this);
}

sequenceFromMatrix::~sequenceFromMatrix()
{
    delete ui;
}

double cutoff(0);
void sequenceFromMatrix::on_spinCutoff_valueChanged(){
    cutoff = ui->spinCutoff->value();
}

double sequenceFromMatrix::getCutoff(){
    double cut = cutoff;
    cutoff = 0;
    return cut;
}

void sequenceFromMatrix::on_buttonSave_clicked(){
    this->close();
}

bool saveM(false);
bool useEM(false);
void sequenceFromMatrix::on_checkBoxSaveResults_stateChanged(){
    if(ui->checkBoxSaveResults->isChecked()){
        saveM = true;
        ui->checkBoxUseEM->setEnabled(true);
    }
    else{
        saveM = false;
        ui->checkBoxUseEM->setEnabled(false);
        useEM = false;
    }
}

bool sequenceFromMatrix::getBool(){
    return saveM;
}

void sequenceFromMatrix::on_checkBoxUseEM_stateChanged(){
    if(ui->checkBoxSaveResults->isChecked() and ui->checkBoxUseEM->isCheckable() and ui->checkBoxUseEM->isChecked()){
        useEM = true;
    }
    else useEM = false;
}

bool sequenceFromMatrix::isEM(){
    bool doEM = useEM;
    useEM = false;
    return doEM;
}
