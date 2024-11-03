#include "A8.h"
# include "ui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //testAll();
    Repository repo;
    Services service(repo);
    Ui ui(service);
    ui.startUp();

    A8 w;
    w.show();
    return a.exec();
}
