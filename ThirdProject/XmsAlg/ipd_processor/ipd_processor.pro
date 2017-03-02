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

OTHER_FILES += \
    IPD.lib


INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

LIBS += -LI:/XMS/OceanLight/ThirdProject/XmsAlg/ipd_processor -lIPD

#win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/IPD.lib
#else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/IPD.lib
