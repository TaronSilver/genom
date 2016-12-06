#ifndef ASKBASEPROB_HPP
#define ASKBASEPROB_HPP

#include <QDialog>

namespace Ui {
class askBaseProb;
}

class askBaseProb : public QDialog
{
    Q_OBJECT

public:
    explicit askBaseProb(QWidget *parent = 0);
    ~askBaseProb();

    static unsigned int getBaseChoiceFinal();
    static double getProbA();
    static double getProbC();
    static double getProbG();
    static double getProbT();
    static unsigned int getMatrixChoice();

public slots:
    void on_chooseBase_currentIndexChanged(int);
    void on_spinA_valueChanged(double);
    void on_spinC_valueChanged(double);
    void on_spinG_valueChanged(double);
    void on_spinT_valueChanged(double);
    void on_chooseMatrix_currentIndexChanged(int);
    void on_buttonSave_clicked();

private:
    Ui::askBaseProb *ui;
};

#endif // ASKBASEPROB_HPP
