TEMPLATE = app
TARGET = HowToUse
QT += core widgets gui

include(public.pri)

INCLUDEPATH +=. \
../include \
 ../../singleton \
 ../../macro

HEADERS += ../include/*.h ./*.h
SOURCES += ../*.cpp ./*.cpp

FORMS += ./*.ui

RESOURCES += ./resources/*.qrc
