#include "quick_qml_widget.h"
#include <QQmlContext>
#include <QQuickItem>
#include <QApplication>
#include <QSurfaceFormat>
#include <QUrl>

QuickQmlWidget::QuickQmlWidget(QWidget *parent):m_ptrView(0), m_ptrContainer(0)
{

    int t_g_dp = 1;
    m_ptrView = new QQuickView;
    QSurfaceFormat format = m_ptrView->format();
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    m_ptrView->setFormat(format);

    m_ptrView->rootContext()->setContextProperty("g_dp", t_g_dp);

    m_ptrView->rootContext()->setContextProperty("touchSettings", true);

    QString rootPath = qApp->applicationDirPath();

    m_ptrView->rootContext()->setContextProperty("rootPath",rootPath);
    m_ptrView->setResizeMode(QQuickView::SizeRootObjectToView);
    m_ptrView->setSource(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    m_ptrContainer = QWidget::createWindowContainer(m_ptrView, parent);
    m_ptrContainer->setProperty("CanMove",true);
    m_ptrContainer->setProperty("CanResize",true);


    m_ptrContainer->show();


}

QWidget *QuickQmlWidget::getContainer() const
{
    return m_ptrContainer;
}


QuickQmlWidget::~QuickQmlWidget()
{

}
