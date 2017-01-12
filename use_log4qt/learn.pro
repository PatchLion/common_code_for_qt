TEMPLATE = app
CONFIG += console

TARGET = log4qt_learn

QT += core
UI_DIR = ./temp/GeneratedFiles
RCC_DIR = ./temp/GeneratedFiles
MOC_DIR = ./temp/GeneratedFiles

INCLUDEPATH += ./temp/GeneratedFiles
DEFINES -= \
    QT_NO_CAST_FROM_ASCII \
	QT_NO_CAST_TO_ASCII

include(../submodule/log4qt/src/log4qt/log4qt.pri)

INCLUDEPATH += ../submodule/log4qt/src/log4qt

HEADERS += *.h
SOURCES += *.cpp

OTHER_FILES += log4qt.conf \
                          log.log

