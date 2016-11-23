#ifndef SAVESEQUENCE_HPP
#define SAVESEQUENCE_HPP

#include <QDialog>
#include <QLabel>

namespace Ui {
class SaveSequence;
}

class SaveSequence : public QDialog
{
    Q_OBJECT

public:
    explicit SaveSequence(QWidget *parent = 0);
    ~SaveSequence();

    bool getCheckbox();
    std::string getFileName();

public slots:
    void on_buttonLeave_clicked();

private:
    Ui::SaveSequence *ui;
    QLabel *label3;
};

#endif // SAVESEQUENCE_HPP
