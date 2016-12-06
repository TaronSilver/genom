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

#include "procedures.hpp"
#include "matrixFromSequence.hpp"
#include "sequenceFromMatrix.hpp"

namespace Ui {
    class Window;
}

class Window : public QDialog
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();
    static std::string getFastaLocation();
    static std::string getMatrixLocation();
    static std::string getOutputName();
    void getFileName();

public slots:
    void on_buttonFasta_clicked();
    void on_buttonMatrix_clicked();
    void on_buttonLeave_clicked();
    void on_buttonSequenceFromMatrix_clicked();
    void on_buttonMatrixFromSequence_clicked();
    void on_buttonLogo_clicked();


private:
    Ui::Window *ui;

    QString fastaLocation;
    QString matrixLocation;
    std::string fastaLocationFromWindow;
    std::string matrixLocationFromWindow;
};

#endif // WINDOW_H
