#ifndef RESULTSWINDOW_HPP
#define RESULTSWINDOW_HPP

#include <QDialog>
#include <QTextBrowser>

namespace Ui {
class resultsWindow;
}

class resultsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit resultsWindow(QWidget *parent = 0);
    ~resultsWindow();


private:
    Ui::resultsWindow *ui;
    std::string resultsLocation;
    QTextBrowser resultsBrowser;
};

#endif // RESULTSWINDOW_HPP
