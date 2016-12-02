#ifndef matrixFromSequence_HPP
#define matrixFromSequence_HPP

#include <QDialog>

namespace Ui {
class matrixFromSequence;
}

class matrixFromSequence : public QDialog
{
    Q_OBJECT

public:
    explicit matrixFromSequence(QWidget *parent = 0);
    ~matrixFromSequence();

    double getProbA();
    double getProbC();
    double getProbG();
    double getProbT();
    int getBaseChoice();
    unsigned int getMatrixChoice();
    static unsigned int getPosition();
    static unsigned int getLength();
    static bool getBool();
    static unsigned int getBaseChoiceFinal();

public slots:
    void on_chooseBase_currentIndexChanged(int);
    void on_spinA_valueChanged(double);
    void on_spinC_valueChanged(double);
    void on_spinG_valueChanged(double);
    void on_spinT_valueChanged(double);
    void on_buttonSave_clicked();
    void on_chooseMatrix_currentIndexChanged(int);
    void on_intPosition_valueChanged(int);
    void on_intLength_valueChanged(int);
    void on_checkBox_stateChanged();


private:
    Ui::matrixFromSequence *ui;
    double probA;
    double probC;
    double probG;
    double probT;
    int baseChoice = 0; //0=0.25 for all, 1= to EM Algorithm, 2 = custom base choice by user input
    unsigned int matrixChoice = 1;
};

#endif // matrixFromSequence_HPP
