QT += core
CONFIG += console

DESTDIR = ./bin
TARGET = test
TEMPLATE = app

UI_DIR = ./temp/GeneratedFiles
RCC_DIR = ./temp/GeneratedFiles
MOC_DIR = ./temp/GeneratedFiles

INCLUDEPATH += ../macro \
                            ./temp/GeneratedFiles

SOURCES += main.cpp

HEADERS  += ../macro/QtCommonMacros.h

#FORMS    += widget.ui
