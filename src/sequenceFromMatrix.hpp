#ifndef SEQUENCEFROMMATRIX_HPP
#define SEQUENCEFROMMATRIX_HPP

#include <QDialog>

#include "resultsWindow.hpp"
#include "procedures.hpp"

namespace Ui {
class sequenceFromMatrix;
}

class sequenceFromMatrix : public QDialog
{
    Q_OBJECT

public:
    explicit sequenceFromMatrix(QWidget *parent = 0);
    ~sequenceFromMatrix();

    static double getCutoff();

public slots:
    void on_buttonSave_clicked();
    void on_spinDouble_valueChanged();

private:
    Ui::sequenceFromMatrix *ui;
};

#endif // SEQUENCEFROMMATRIX_HPP
