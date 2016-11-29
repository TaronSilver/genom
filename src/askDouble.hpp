#ifndef askDouble_HPP
#define askDouble_HPP

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class askDouble;
}

class askDouble : public QDialog
{
    Q_OBJECT

public:
    explicit askDouble(QWidget *parent = 0);
    ~askDouble();
    double getDouble();

public slots:
    void on_setDouble_clicked();
    void on_spinDouble_valueChanged(double);

private:
    Ui::askDouble *ui;
    double Double;

};

#endif // askDouble_HPP
