#include "sequenceFromMatrix.hpp"
#include "ui_sequenceFromMatrix.h"
#include "resultsWindow.hpp"

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

double cutoff;
void sequenceFromMatrix::setCutoff(){
    cutoff = ui->spinDouble->value();
}

double sequenceFromMatrix::getCutoff(){
    return cutoff;
}

void sequenceFromMatrix::on_buttonSave_clicked(){
    resultsWindow results;
    results.show();
    results.exec();

    this->close();
}
