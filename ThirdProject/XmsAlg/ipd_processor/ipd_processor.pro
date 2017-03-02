#-------------------------------------------------
#
# Project created by QtCreator 2017-02-23T10:10:14
#
#-------------------------------------------------

QT       += core multimedia

QT       -= gui

TARGET = ipd_processor
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ipd_processor.cpp \
    IMP_Lock.cpp \
    IMP_FrameQueue.cpp

HEADERS += \
    ipd_processor.h \
    imp_algo_type.h \
    imp_ipd_adv_para.h \
    imp_ipd_api.h \
    imp_ipd_para.h \
    IMP_Lock.h \
    IMP_Frame.h \
    IMP_FrameQueue.h
LIBS    += \
    IPD.lib

OTHER_FILES += \
    IPD.lib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ -lIP
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ -lIPd

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/IP.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/IPd.lib
