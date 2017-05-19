TEMPLATE = app
TARGET = demo
QT += core gui widgets
CONFIG += console

include(../../../public.pri)

INCLUDEPATH += . ..

HEADERS += ./*.h ../*.h

SOURCES += ./*.cpp ../*.cpp

FORMS += ./*.ui
