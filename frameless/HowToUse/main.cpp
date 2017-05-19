#include <QtWidgets/QApplication>
#include "demo.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CTestMainWidget test;
    test.show();

    return app.exec();
}
