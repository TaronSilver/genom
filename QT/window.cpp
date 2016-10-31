#include "window.hpp"

Window::Window(): QWidget()
{
    setFixedSize(150, 100);

    m_quit = new QPushButton("Leave", this);
    m_quit->setFont(QFont("Uubntu", 11));
    m_quit->move(60, 50);
    QObject::connect(m_quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    m_fileName = new QPushButton("Sequence File", this);
    m_fileName->move(40, 30);
    QObject::connect(m_fileName, SIGNAL(clicked(bool)), this, SLOT(askFileName()));

}

void Window::askFileName(){
    QString file = QFileDialog::getOpenFileName(this, "Open a Sequence File" ,QString(),"Fasta files only! ( *.fasta *.fas *ffn *.faa *.frn )");
    QMessageBox::information(this, "Fasta File", "You have chosen this file: " + file);
}

void Window::openDirectory(){

}

void Window::openDialogue(){

}
