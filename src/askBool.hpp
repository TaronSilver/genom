#ifndef ASKBOOL_HPP
#define ASKBOOL_HPP

#include <QDialog>

namespace Ui {
class askBool;
}

class askBool: public QDialog
{
    Q_OBJECT

public:
    explicit askBool(QWidget *parent=0);
    ~askBool();
    bool getBool();

public slots:
    void on_buttonLeave_clicked();

private:
     Ui::askBool *ui;
};

#endif
