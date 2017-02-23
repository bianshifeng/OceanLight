#include "controllerAlgconfig.h"
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include "webglobaltool.h"
#include "aidevicebase.h"

ControllerAlgconfig::ControllerAlgconfig()
{

}

void ControllerAlgconfig::service(HttpRequest &request, HttpResponse &response)
{

    if(g_AIDevice){
        if (request.getParameter("action")=="getAlg")
        {
            g_AIDevice->updateAlgConfig();
            QByteArray body = g_AIDevice->algConfig().toLatin1();
            response.write(body,true);
        }

        if(request.getParameter("action")=="setAlg"){
            g_AIDevice->setAlgConfig(QString(request.getParameter("algConfig")));
            response.write(g_AIDevice->algConfig().toLatin1(),true);

        }
        if(request.getParameter("action")=="startAlg"){
            g_AIDevice->setIsRuningAlg(true);
            response.write("startAlg",true);

        }
        if(request.getParameter("action") == "stopAlg"){
            g_AIDevice->setIsRuningAlg(false);
            response.write("stopAlg",true);
        }

    }else{
        response.write("unline",true);
    }
}
