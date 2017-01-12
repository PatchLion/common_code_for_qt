#ifndef Log4QtObject_H_
#define Log4QtObject_H_

#include <QtCore>
#include "logger.h"

class CLog4QtObject : public QObject
{
    Q_OBJECT
    LOG4QT_DECLARE_QCLASS_LOGGER

public:
    CLog4QtObject(QObject* parent=0) : QObject(parent){ logger()->info("constructor");}
    ~CLog4QtObject(){ logger()->info("destructor");}
};

#endif Log4QtObject_H_
