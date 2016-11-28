#include "window.hpp"
#include "../build/ui_window.h"

#include "utility.hpp"
#include "procedures.hpp"
#include "askBaseProbability.hpp"

Window::Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
}

Window::~Window() {
    delete ui;
}

void Window::on_buttonLeave_clicked() {
    qApp->quit();
}

void Window::on_chooseFasta_clicked() {
    fastaLocation = QFileDialog::getOpenFileName(this, "Open a Sequence File", fastaLocation, "Fasta files only! ( *.fasta *.fas *.ffn *.faa *.frn )");
    //QString file = QFileDialog::getOpenFileName(this, "Open a Sequence File" ,QString(),"Fasta files only! ( *.fasta *.fas *ffn *.faa *.frn )");

    //QMessageBox::information(this, "Fasta File", "You have chosen this file: " + fastaLocation);

    ui->showFastaLocation->setText(fastaLocation);
    ui->showFastaLocation->adjustSize();
}

void Window::on_chooseMatrix_clicked() {
    matrixLocation = QFileDialog::getOpenFileName(this, "Open a Matrix File", matrixLocation, "(*.mat)");
    ui->showMatrixLocation->setText(matrixLocation);
    ui->showMatrixLocation->adjustSize();
}

std::string matrixFilePath;
std::string fastaFilePath;
void Window::on_sequenceFromMatrixButton_clicked() {
    if(fastaLocation.isEmpty() or matrixLocation.isEmpty()) {
        QMessageBox::critical(this, "Error: Files not chosen", "You havent chosen your Sequence or your Matrix file.");
    }
    else {
    //matrixFilePath = relativePath(matrixLocation.toStdString());
    //fastaFilePath = relativePath(fastaLocation.toStdString());
        matrixFilePath = matrixLocation.toStdString();
        fastaFilePath = fastaLocation.toStdString();
    enzyme_on_sequence();
    }
}


void Window::on_matrixFromSequenceButton_clicked() {
    if(fastaLocation.isEmpty()) {
        QMessageBox::critical(this, "Error: File not chosen", "You havent chosen your Sequence file.");
    }
    else {
    std::string fastaFilePath = relativePath(fastaLocation.toStdString());
    askBaseProbability glass;
    glass.show();
    glass.exec();

    enzyme_from_sequences();
    }
}

std::string Window::getFastaLocation(){
    return fastaFilePath;
}

std::string Window::getMatrixLocation(){
    return matrixFilePath;
}
