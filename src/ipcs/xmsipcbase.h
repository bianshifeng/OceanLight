#ifndef XMSIPCBASE_H
#define XMSIPCBASE_H

#include <QObject>
#include <QList>

class XmsAlgBase;
class XmsIpcBase : public QObject
{
    Q_OBJECT
public:
    explicit XmsIpcBase(QObject *parent = 0);

signals:

public slots:

};

#endif // XMSIPCBASE_H
