#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>

class Window: public QWidget
{
    Q_OBJECT

public:
    Window();

public slots:
    void askFileName();
    void openDirectory();
    void openDialogue();


private:
    QPushButton *m_fileName;
    QPushButton *m_quit;
    QPushButton *m_directoryName;
    QPushButton *m_dialogueButton;
};

#endif // WINDOW_H
