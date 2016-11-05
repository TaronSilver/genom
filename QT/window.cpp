#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    /*Legacy
     * m_quit = new QPushButton("Leave", this);
    m_quit->setFont(QFont("Uubntu", 11));
    m_quit->move(60, 50);
    QObject::connect(m_quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    m_fileName = new QPushButton("Sequence File", this);
    m_fileName->move(40, 30);
    QObject::connect(m_fileName, SIGNAL(clicked(bool)), this, SLOT(askFileName()));*/
}

Window::~Window()
{
    delete ui;
}


void Window::on_buttonLeave_clicked(){
    qApp->quit();
}

void Window::on_chooseFasta_clicked(){
    fastaLocation = QFileDialog::getOpenFileName(this, "Open a Sequence File", fastaLocation, "Fasta files only! ( *.fasta *.fas *.ffn *.faa *.frn )");
    //QString file = QFileDialog::getOpenFileName(this, "Open a Sequence File" ,QString(),"Fasta files only! ( *.fasta *.fas *ffn *.faa *.frn )");

    //QMessageBox::information(this, "Fasta File", "You have chosen this file: " + file);
    ui->showFastaLocation->setText(fastaLocation);
    ui->showFastaLocation->adjustSize();
}

void Window::on_chooseMatrix_clicked(){
    matrixLocation = QFileDialog::getOpenFileName(this, "Open a Matrix File", matrixLocation, "(*.mat)");
    ui->showMatrixLocation->setText(matrixLocation);
    ui->showMatrixLocation->adjustSize();
}

/*  Legacy Slots.
 * void Window::askFileName(){
    QString file = QFileDialog::getOpenFileName(this, "Open a Sequence File" ,QString(),"Fasta files only! ( *.fasta *.fas *ffn *.faa *.frn )");
    QMessageBox::information(this, "Fasta File", "You have chosen this file: " + file);
}

void Window::openDirectory(){

}

void Window::openDialogue(){

}*/
