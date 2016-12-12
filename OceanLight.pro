TEMPLATE = app
TARGET = Ocean

VERSION = 1.0.0

#程序编译发布路径
DESTDIR = ./Bin/Win32/UnicodeRelease



QT += qml quick sql quickcontrols2
QT += widgets core gui multimedia

QTPLUGIN += qsqlite

#生成的中间代码
OBJECTS_DIR += temp/bulid_obj_dir
MOC_DIR  += temp/bulid_moc_dir
UI_DIR   += temp/bulid_ui_dir
RCC_DIR  += temp/bulid_rcc_dir


#include(common/common.pri)
include(3rd/webServer/webServer.pri)
include(src/src.pri)

RESOURCES += \
    qml.qrc
target.path =
INSTALLS += target


SOURCES += \
    $$PWD/main.cpp \

