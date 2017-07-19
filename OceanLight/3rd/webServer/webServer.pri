
QT += network

#include(../../../Bulid_debug/OceanLight/Bin/Win32/UnicodeDebug/etc/web.pri)

# Enable very detailed debug messages when compiling the debug version
CONFIG(debug, debug|release) {
    DEFINES += SUPERVERBOSE
}

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/webglobaltool.h \
    $$PWD/webrequestrouter.h \
    $$PWD/webserver.h \
    $$PWD/controller/dumpcontroller.h \
    $$PWD/controller/mainpage_templatecontroller.h \
    $$PWD/controller/controllerAlgconfig.h \
    $$PWD/controller/fileuploadcontroller.h \
    $$PWD/controller/controlleripcconfig.h

SOURCES += \
    $$PWD/webglobaltool.cpp \
    $$PWD/webrequestrouter.cpp \
    $$PWD/webserver.cpp \
    $$PWD/controller/dumpcontroller.cpp \
    $$PWD/controller/mainpage_templatecontroller.cpp \
    $$PWD/controller/controllerAlgconfig.cpp \
    $$PWD/controller/fileuploadcontroller.cpp \
    $$PWD/controller/controlleripcconfig.cpp




#From QtWebApp
#---------------------------------------------------------------------------------------------------
PATH_HTTPSERVER = $$PWD/../../..//ThirdProject/QtWebApp/httpserver

INCLUDEPATH += $$PATH_HTTPSERVER
DEPENDPATH += $$PATH_HTTPSERVER

HEADERS += $$PATH_HTTPSERVER/httpglobal.h \
           $$PATH_HTTPSERVER/httplistener.h \
           $$PATH_HTTPSERVER/httpconnectionhandler.h \
           $$PATH_HTTPSERVER/httpconnectionhandlerpool.h \
           $$PATH_HTTPSERVER/httprequest.h \
           $$PATH_HTTPSERVER/httpresponse.h \
           $$PATH_HTTPSERVER/httpcookie.h \
           $$PATH_HTTPSERVER/httprequesthandler.h \
           $$PATH_HTTPSERVER/httpsession.h \
           $$PATH_HTTPSERVER/httpsessionstore.h \
           $$PATH_HTTPSERVER/staticfilecontroller.h

SOURCES += $$PATH_HTTPSERVER/httpglobal.cpp \
           $$PATH_HTTPSERVER/httplistener.cpp \
           $$PATH_HTTPSERVER/httpconnectionhandler.cpp \
           $$PATH_HTTPSERVER/httpconnectionhandlerpool.cpp \
           $$PATH_HTTPSERVER/httprequest.cpp \
           $$PATH_HTTPSERVER/httpresponse.cpp \
           $$PATH_HTTPSERVER/httpcookie.cpp \
           $$PATH_HTTPSERVER/httprequesthandler.cpp \
           $$PATH_HTTPSERVER/httpsession.cpp \
           $$PATH_HTTPSERVER/httpsessionstore.cpp \
           $$PATH_HTTPSERVER/staticfilecontroller.cpp

#-----------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------
PATH_LOGGING = $$PWD/../../..//ThirdProject/QtWebApp/logging
INCLUDEPATH += $$PATH_LOGGING
DEPENDPATH += $$PATH_LOGGING

HEADERS += $$PATH_LOGGING/logglobal.h \
    $$PATH_LOGGING/logmessage.h \
    $$PATH_LOGGING/logger.h \
    $$PATH_LOGGING/filelogger.h \
    $$PATH_LOGGING/dualfilelogger.h

SOURCES += $$PATH_LOGGING/logmessage.cpp \
    $$PATH_LOGGING/logger.cpp \
    $$PATH_LOGGING/filelogger.cpp \
    $$PATH_LOGGING/dualfilelogger.cpp
#-----------------------------------------------------------------------------------------------
PATH_TEMPLATE = $$PWD/../../..//ThirdProject/QtWebApp/templateengine
INCLUDEPATH += $$PATH_TEMPLATE
DEPENDPATH += $$PATH_TEMPLATE

HEADERS += $$PATH_TEMPLATE/templateglobal.h
HEADERS += $$PATH_TEMPLATE/template.h
HEADERS += $$PATH_TEMPLATE/templateloader.h
HEADERS += $$PATH_TEMPLATE/templatecache.h

SOURCES += $$PATH_TEMPLATE/template.cpp
SOURCES += $$PATH_TEMPLATE/templateloader.cpp
SOURCES += $$PATH_TEMPLATE/templatecache.cpp
#-------------------------------------------------------------------------------------------------




