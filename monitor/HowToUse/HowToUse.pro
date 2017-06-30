TEMPLATE = app
TARGET = HowToUse
QT += core widgets gui

include(../../public.pri)

INCLUDEPATH +=. \
.. \
 ../../singleton \
 ../../macro

HEADERS += ../*.h ./*.h \
    SliderForm.h
SOURCES += ../*.cpp ./*.cpp \
    SliderForm.cpp

FORMS += ./*.ui \
    SliderForm.ui
