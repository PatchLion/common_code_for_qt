#include <QCoreApplication>
#include "QtCommonMacros.h"
#include "log4qtlib.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const QString join_path1 = SAFE_JOIN_PATH("c:/test", "folder");
    const QString join_path2 = SAFE_JOIN_PATH("c:/test/", "folder");
    const QString join_path3 = SAFE_JOIN_PATH("c:/test", "file.jpg");
    const QString join_path4 = SAFE_JOIN_PATH("c:/test/", "file.jpg");

    qDebug() << join_path1;
    qDebug() << join_path2;
    qDebug() << join_path3;
    qDebug() << join_path4;

    return a.exec();
}
