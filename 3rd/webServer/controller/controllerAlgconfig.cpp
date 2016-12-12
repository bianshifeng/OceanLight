#include "controllerAlgconfig.h"
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>

ControllerAlgconfig::ControllerAlgconfig()
{

}

void ControllerAlgconfig::service(HttpRequest &request, HttpResponse &response)
{
    Q_UNUSED(&request);

    QJsonObject json;
    json.insert("algId", QString("bianshifeng"));
    json.insert("algName", QString("bianziluo"));
    json.insert("algParams", QString("[1111111111]"));
    json.insert("algType", QString("cpc"));
    json.insert("algIpc", QString("camera001"));
    json.insert("algActiveStatus", true);


    QJsonDocument document;
    document.setObject(json);
    QByteArray body = document.toJson(QJsonDocument::Compact);
    //QString json_str(byte_array);
    response.write(body,true);
}
