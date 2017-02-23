TEMPLATE =  app
TARGET = demo
DEFINES += _WINDOWS _UNICODE CBOX_QT

QT += core
QT += network

DISTFILES += \
    sales_demo.pro.user

SOURCES += \
    main.cpp \
    device_livex.cpp


HEADERS += \
    imp_algo_type.h \
    imp_algopc.h \
    IMP_AlgoRes.h \
    IMP_AlgoResQueue.h \
    imp_cpc_para.h \
    IMP_Lock.h \
    IMP_Socket.h \
    livex_socket.h \
    device_livex.h

SOURCES += \
    imp_algopc.cpp \
    IMP_AlgoResQueue.cpp \
    IMP_Lock.cpp \
    IMP_Socket.cpp \
    livex_socket.c
