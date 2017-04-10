TEMPLATE = app
TARGET = HowToUse
QT += core network

include(public.pri)

INCLUDEPATH +=. \
.. \
 ../../singleton \
 ../../macro

HEADERS += ../*.h
SOURCES += ../*.cpp ./*.cpp
