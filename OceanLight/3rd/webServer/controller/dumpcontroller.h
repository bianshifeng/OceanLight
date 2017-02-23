#ifndef DUMPCONTROLLER_H
#define DUMPCONTROLLER_H
#include "httprequesthandler.h"
#include "httprequest.h"
#include "httpresponse.h"
using namespace stefanfrings;
class DumpController : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(DumpController)
public:
    DumpController();

    // HttpRequestHandler interface
public:
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // DUMPCONTROLLER_H
