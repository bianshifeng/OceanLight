#ifndef DEVICE_LIVEX_H
#define DEVICE_LIVEX_H

#include <QObject>

#ifdef _DEBUG
    #define LVDEBUG(fmt,...) printf ("%s %s,"__FILE__"[%d],DEBUG: "fmt,__DATE__,__TIME__,##__VA_ARGS__);
#endif

#define LVERROR(fmt, ...)  printf("%s %s, "__FILE__"[%d], ERROR: "fmt, __DATE__, __TIME__, __LINE__, ##__VA_ARGS__);

class Device_LiveX : public QObject
{
    Q_OBJECT
public:
    explicit Device_LiveX(QObject *parent = 0);

    int livexSend(int fd, const char *buf, int specified_len, int time_out);

signals:
   void SockCondition(const QString& info);
public slots:
};

#endif // DEVICE_LIVEX_H
