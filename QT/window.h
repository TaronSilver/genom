#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>

namespace Ui {
    class Window;
}

class Window : public QDialog
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

public slots:
    void on_chooseFasta_clicked();
    void on_chooseMatrix_clicked();
    void on_buttonLeave_clicked();

private:
    Ui::Window *ui;

    QString fastaLocation;
    QString matrixLocation;

    /*
     * Leagcy attributes (whatever you wanna call them)
    QPushButton *m_fileName;
    QPushButton *m_directoryName;
    QPushButton *m_dialogueButton; */
};

#endif // WINDOW_H
