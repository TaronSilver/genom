#ifndef ASKPOSANDLENGTH_HPP
#define ASKPOSANDLENGTH_HPP

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class askPosAndLength;
}

class askPosAndLength : public QDialog
{
    Q_OBJECT

public:
    explicit askPosAndLength(QWidget *parent = 0);
    ~askPosAndLength();
    unsigned int getPosition();
    unsigned int getLength();

public slots:
    void on_intPosition_valueChanged(int);
    void on_intLength_valueChanged(int);
    void on_setValues_clicked();


private:
    Ui::askPosAndLength *ui;
    unsigned int position=1;
    unsigned int length=0;
};

#endif // ASKPOSANDLENGTH_HPP
