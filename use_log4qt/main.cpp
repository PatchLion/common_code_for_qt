#include <QCoreApplication>
#include "logger.h"
#include "basicconfigurator.h"
#include "propertyconfigurator.h"
#include "Log4QtObject.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    Log4Qt::BasicConfigurator::configure();
    Log4Qt::Logger *log = Log4Qt::Logger::rootLogger();
    log->debug("Hello Log4Qt");
    log->info("Hello Qt!");
    log->warn("Hello C++");

    {
        Log4Qt::PropertyConfigurator::configure("log4qt.conf");

        Log4Qt::Logger *log2 = Log4Qt::Logger::logger("A2");
        log2->debug("++++");
        log2->info("----");
        log2->warn("====");


        CLog4QtObject testObj;
    }

    return 0;//a.exec();
}
