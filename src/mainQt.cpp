#include "Matrix.hpp"
#include "Sequence.hpp"
#include "utility.hpp"
#include <QApplication>
#include <window.hpp>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Window window;
    window.show();
    return app.exec();
}
