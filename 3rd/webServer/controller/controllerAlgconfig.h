#ifndef CONTROLLER_ALGCONFIG_H
#define CONTROLLER_ALGCONFIG_H
#include "httpconnectionhandler.h"
#include <QObject>
using namespace stefanfrings;
class ControllerAlgconfig : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(ControllerAlgconfig)
public:
    explicit ControllerAlgconfig();

signals:

public slots:

    // HttpRequestHandler interface
public:
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // CONTROLLER_ALGCONFIG_H
