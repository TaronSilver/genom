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

    static unsigned int getMatrixChoice();
    static unsigned int getPosition();
    static unsigned int getLength();
    static bool getBool();

public slots:

    void on_buttonSave_clicked();
    void on_chooseMatrix_currentIndexChanged(int);
    void on_intPosition_valueChanged(int);
    void on_intLength_valueChanged(int);
    void on_checkBox_stateChanged();


private:
    Ui::matrixFromSequence *ui;


};

#endif // matrixFromSequence_HPP
