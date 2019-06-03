#include "mainwindow.h"
#include "App.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App* app = new App();
    app->GetInstancePtr();
    MainWindow w;
    w.show();

    return a.exec();
}
