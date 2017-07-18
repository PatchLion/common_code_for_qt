TEMPLATE = app
TARGET = HowToUse
CONFIG += console
QT += core widgets gui

include(../../public.pri)

INCLUDEPATH +=. \
.. \
 ../../singleton \
 ../../macro

HEADERS += ../*.h ./*.h ../*.inl
SOURCES += ./*.cpp

FORMS += ./*.ui
