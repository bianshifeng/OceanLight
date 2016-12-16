#ifndef CONTROLLERIPCCONFIG_H
#define CONTROLLERIPCCONFIG_H

#include "httprequesthandler.h"
#include "httprequest.h"
#include "httpresponse.h"
using namespace stefanfrings;

class ControllerIpcConfig : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(ControllerIpcConfig)
public:
    explicit ControllerIpcConfig();

signals:

public slots:

    // HttpRequestHandler interface
public:
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // CONTROLLERIPCCONFIG_H
