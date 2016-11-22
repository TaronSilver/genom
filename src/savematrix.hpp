#ifndef SAVEMATRIX_HPP
#define SAVEMATRIX_HPP

#include <QDialog>

namespace Ui {
class saveMatrix;
}

class saveMatrix : public QDialog
{
    Q_OBJECT

public:
    explicit saveMatrix(QWidget *parent = 0);
    ~saveMatrix();

    unsigned int getMatrixChoice();
    std::string getFileName();

public slots:
    void on_buttonSave_clicked();
    void on_chooseMatrix_currentIndexChanged(int);

private:
    Ui::saveMatrix *ui;
    unsigned int matrixChoice = 1;
};

#endif // SAVEMATRIX_HPP
