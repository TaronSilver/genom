#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QDialog>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QObject>

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
    void on_sequenceFromMatrixButton_clicked();
    void on_matrixFromSequenceButton_clicked();


private:
    Ui::Window *ui;

    QString fastaLocation;
    QString matrixLocation;
};



#endif // WINDOW_H
