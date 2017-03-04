#ifndef QUICK_QML_WIDGET_H
#define QUICK_QML_WIDGET_H

#include <QWidget>
#include <QObject>
#include <QQuickView>


class QuickQmlWidget
{
public:
    explicit QuickQmlWidget(QWidget *parent = 0);
    virtual ~QuickQmlWidget();
    QWidget *getContainer(void) const;

private:
    QQuickView *m_ptrView;
    QWidget    *m_ptrContainer;
};


#endif // QUICK_QML_WIDGET_H
