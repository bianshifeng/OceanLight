#ifndef FILEUPLOADCONTROLLER_H
#define FILEUPLOADCONTROLLER_H
#include "httprequesthandler.h"
#include "httprequest.h"
#include "httpresponse.h"
using namespace stefanfrings;
class FileUploadController : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(FileUploadController)
public:
    explicit FileUploadController();

signals:

public slots:

    // HttpRequestHandler interface
public:
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // FILEUPLOADCONTROLLER_H
