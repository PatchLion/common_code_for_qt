TEMPLATE = app
TARGET = HowToUse
QT += core widgets gui

include(../../public.pri)

INCLUDEPATH +=. \
.. \
 ../../singleton \
 ../../macro

HEADERS += ../*.h ./*.h
SOURCES += ../*.cpp ./*.cpp

FORMS += ./*.ui

RESOURCES += ./resources/*.qrc
