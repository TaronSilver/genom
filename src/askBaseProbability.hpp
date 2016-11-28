#ifndef ASKBASEPROBABILITY_HPP
#define ASKBASEPROBABILITY_HPP

#include <QDialog>

namespace Ui {
class askBaseProbability;
}

class askBaseProbability : public QDialog
{
    Q_OBJECT

public:
    explicit askBaseProbability(QWidget *parent = 0);
    ~askBaseProbability();

    double getProbA();
    double getProbC();
    double getProbG();
    double getProbT();
    int getBaseChoice();
    unsigned int getMatrixChoice();
    std::string getFileName();
    static unsigned int getPosition();
    static unsigned int getLength();

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


private:
    Ui::askBaseProbability *ui;
    double probA;
    double probC;
    double probG;
    double probT;
    int baseChoice = 0;
    unsigned int matrixChoice = 1;
};

#endif // ASKBASEPROBABILITY_HPP
