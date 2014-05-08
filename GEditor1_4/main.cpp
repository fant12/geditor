#include "geditor.h"
#include <QApplication>

int main(int argc, char **argv){

    QApplication app(argc, argv);
    GEditor window;
    window.showMaximized();

    return app.exec();
}
