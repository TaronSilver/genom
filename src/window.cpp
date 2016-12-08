#include "window.hpp"
#include "../build/ui_window.h"


#include "logo.hpp"

std::string matrixFilePath;
std::string fastaFilePath;
std::string output;

Window::Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    matrixFilePath="";
    fastaFilePath="";
    output="";
}

Window::~Window() {
    delete ui;
}

void Window::on_buttonLeave_clicked() {
    qApp->quit();
}

void Window::on_buttonFasta_clicked() {
    fastaLocation = QFileDialog::getOpenFileName(this, "Open a Sequence File", fastaLocation, "Fasta files only! ( *.fasta *.fas *.ffn *.faa *.frn )");

    ui->showFastaLocation->setText(fastaLocation);
    ui->showFastaLocation->adjustSize();
}

void Window::on_buttonMatrix_clicked() {
    matrixLocation = QFileDialog::getOpenFileName(this, "Open a Matrix File", matrixLocation, "(*.mat)");
    ui->showMatrixLocation->setText(matrixLocation);
    ui->showMatrixLocation->adjustSize();
}

void Window::on_buttonSequenceFromMatrix_clicked() {
    if(fastaLocation.isEmpty() or matrixLocation.isEmpty()) {
        QMessageBox::critical(this, "Error: Files not chosen", "You havent chosen your Sequence or your Matrix file.");
    }
    else {
        matrixFilePath = matrixLocation.toStdString();
        fastaFilePath = fastaLocation.toStdString();
       this->getFileName();

        sequenceFromMatrix mac;
        mac.show();
        mac.exec();

        askBaseProb base;
        base.show();
        base.exec();

        enzyme_on_sequence();

        resultsWindow results;
        results.show();
        results.exec();
    }
}

void Window::on_buttonMatrixFromSequence_clicked() {
    if(fastaLocation.isEmpty()) {
        QMessageBox::critical(this, "Error: File not chosen", "You havent chosen your Sequence file.");
    }
    else {
    fastaFilePath = fastaLocation.toStdString();

    matrixFromSequence glass;
    glass.show();
    glass.exec();

    enzyme_from_sequences();
    }
}

void Window::on_buttonLogo_clicked(){
  if(matrixLocation.isEmpty()) {
      QMessageBox::critical(this, "Error: File not chosen", "You havent chosen your Matrix file.");
  }
  else{
    matrixFilePath = matrixLocation.toStdString();
    logo();
  }
}

std::string Window::getFastaLocation(){
    return fastaFilePath;
}

std::string Window::getMatrixLocation(){
    return matrixFilePath;
}

void Window::getFileName(){
    output = ui->editFileName->text().toStdString();
}

std::string Window::getOutputName(){
    return "../" + output;
}
