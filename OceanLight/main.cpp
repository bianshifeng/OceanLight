/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Quick Controls module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QApplication>
#include <QGuiApplication>
#include <QOpenGLContext>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlEngine>
#include <QtQml>

#include <QScreen>
#include <QDebug>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "sqleventmodel.h"
#include "websystetraymenu.h"
#include "touchsettings.h"

#include "algs/algcpc.h"
#include "ipcs/xmsipcbase.h"
#include "3rd/ffmpegPlayer/ffmpeg_logger.h"


#include "webserver.h"

FFMPEGLogger* FFMPEGLogger::_instance = nullptr;

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    qmlRegisterType<AlgCPC>("Xms.Alg", 1, 0, "AlgCPC");
    qmlRegisterType<XmsIpcBase>("Xms.Ipc", 1, 0, "IpcRstp");
    qmlRegisterSingletonType<FFMPEGLogger>("Xms.Logger",1,0,"FFmpegLogger",FFMPEGLogger::GetInstance);
    qRegisterMetaType<FFMPEGLogger::Level>("Level");


    QSettings extraSettings;
    extraSettings.beginGroup("CPP");
    extraSettings.setValue("cppSettings", "this is cpp settings");
    extraSettings.endGroup();


    TouchSettings touchSettings;

    //init view
    QQuickView view;
//    view.setFormat(format);
    view.create();


    view.rootContext()->setContextProperty("touchSettings", &touchSettings);

    QApplication::connect(view.engine(),SIGNAL(quit()),qApp,SLOT(quit()));

    //QApplication::connect(view.rootContext(),SIGNAL(showFullScreen()),&view,SLOT(showFullScreen()));
    view.setSource(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    //view.setFlags(Qt::WindowFullscreenButtonHint);
    //view.setMinimumWidth(516);
    //view.setPosition(200,100);
    view.showNormal();


    WebServer webServer;
    return app.exec();
}



//    QSurfaceFormat format;
//    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
//        format.setVersion(3, 2);
//        format.setProfile(QSurfaceFormat::CoreProfile);
//    }
//    format.setDepthBufferSize(24);
//    format.setStencilBufferSize(8);
//view.setFlags(Qt::CustomizeWindowHint|Qt::WindowMinimizeButtonHint);
//view.setModality(Qt::WindowModal);
//QObject *webServer = new QObject;
//view.engine()->rootContext()->setContextProperty("g_sebServer",webServer);

//    QObject *webServer = new QObject;
//    WebSysteTrayMenu *m_trayMenu = new WebSysteTrayMenu(webServer);
//    m_trayMenu->show();
//    qApp->connect(m_trayMenu,SIGNAL(sigShowView()),&view,SLOT(showNormal()));
//    qApp->connect(view.engine(),SIGNAL(quit()),qApp,SLOT(quit()));
