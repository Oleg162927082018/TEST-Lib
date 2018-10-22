VERSION = 1.0.0.0
QMAKE_TARGET_PRODUCT = PhantomJS adapter
QMAKE_TARGET_DESCRIPTION = Adapter for PhantomJS test-case
QMAKE_TARGET_COPYRIGHT = Copyright\xA9 Oleg Kopyev 2016-2017

QT       -= gui
QT       += widgets xml

TARGET = phantomjs
TEMPLATE = lib

DEFINES += PHANTOMJS_LIBRARY

SOURCES += phantomjs.cpp \
    phantomjs-main.cpp \
    phantomjs-edit-widget.cpp \
    phantomjs-output-comparator.cpp \
    phantomjs-compare-widget.cpp \
    plantomjs-image-viewer.cpp

HEADERS += phantomjs.h\
    phantomjs_global.h \
    ../../TTI/Common/itestcasetemplate.h \
    phantomjs-compare-widget.h \
    phantomjs-edit-widget.h \
    phantomjs-output-comparator.h \
    plantomjs-image-viewer.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES +=

FORMS += \
    phantomjs-edit-widget.ui \
    phantomjs-compare-widget.ui
