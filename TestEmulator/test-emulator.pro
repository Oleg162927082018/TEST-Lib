VERSION = 1.1.0.0
QMAKE_TARGET_PRODUCT = Test emulator adapter
QMAKE_TARGET_DESCRIPTION = Adapter for the test emulator
QMAKE_TARGET_COPYRIGHT = Copyright\xA9 Oleg Kopyev 2016-2018

QT       -= gui
QT       += widgets xml

TARGET = test-emulator
TEMPLATE = lib

DEFINES += TESTEMULATOR_LIBRARY

SOURCES += test-emulator.cpp \
    test-emulator-main.cpp \
    test-emulator-edit-widget.cpp \
    test-emulator-output-comparator.cpp \
    test-emulator-compare-widget.cpp \
    test-emulator-image-viewer.cpp

HEADERS += test-emulator.h\
    test-emulator_global.h \
    ../../TTI/Common/itestcasetemplate.h \
    test-emulator-compare-widget.h \
    test-emulator-edit-widget.h \
    test-emulator-output-comparator.h \
    test-emulator-image-viewer.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES +=

FORMS += \
    test-emulator-edit-widget.ui \
    test-emulator-compare-widget.ui
