#ifndef XMSALGBASE_H
#define XMSALGBASE_H

#include <QObject>

class XmsAlgBase : public QObject
{
    Q_OBJECT
public:
    explicit XmsAlgBase(QObject *parent = 0);

signals:

public slots:
};

#endif // XMSALGBASE_H