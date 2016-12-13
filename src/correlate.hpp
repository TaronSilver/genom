#ifndef CORRELATE_HPP
#define CORRELATE_HPP

#include <QDialog>

namespace Ui {
class Correlate;
}

class Correlate : public QDialog
{
    Q_OBJECT

public:
    explicit Correlate(QWidget *parent = 0);
    ~Correlate();

private:
    Ui::Correlate *ui;
};

#endif // CORRELATE_HPP
