#ifndef ASKDOUBLE_HPP
#define ASKDOUBLE_HPP

#include <QDialog>

namespace Ui {
class askDouble;
}

class askDouble : public QDialog
{
    Q_OBJECT

public:
    explicit askDouble(QWidget *parent = 0);
    ~askDouble();
    double getCutoff();

public slots:
    void on_setCutoff_clicked();
    void on_spinCutoff_valueChanged(double);

private:
    Ui::askDouble *ui;
    double cutoff;

};

#endif // ASKDOUBLE_HPP
