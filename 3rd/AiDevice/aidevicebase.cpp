#include "aidevicebase.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

AiDeviceBase::AiDeviceBase(QObject *parent) : QObject(parent)
{

}

AiDeviceBase::~AiDeviceBase()
{

}

void AiDeviceBase::initDevice(const QString &ipcMessage, const QString &algMessage)
{
    Q_UNUSED(&ipcMessage);
    Q_UNUSED(&algMessage);

}

QString AiDeviceBase::algConfig() const
{
    return m_algConfig;
}

QString AiDeviceBase::ipcConfig() const
{
    return m_ipcConfig;
}

bool AiDeviceBase::isLiving() const
{
    return m_isLiving;
}

QString AiDeviceBase::getAlgResult() const
{
    return m_algResult;

}

void AiDeviceBase::updateAlgConfig()
{

    QJsonObject json;
    json.insert("algId", QString("hello I came from world"));
    json.insert("algName", QString("bianziluo"));
    json.insert("algParams", QString("[1111111111]"));
    json.insert("algType", QString("cpc"));
    json.insert("algIpc", QString("camera001"));
    json.insert("algActiveStatus", true);


    QJsonDocument document;
    document.setObject(json);
    m_algConfig = QString(document.toJson(QJsonDocument::Compact));
    qDebug() << m_algConfig;
    //QByteArray body = document.toJson(QJsonDocument::Compact);
}

bool AiDeviceBase::isRuningAlg() const
{
    return m_isRuningAlg;
}



void AiDeviceBase::setAlgConfig(QString algConfig)
{
    if (m_algConfig == algConfig)
        return;

    m_algConfig = algConfig;
    emit algConfigChanged(algConfig);
}

void AiDeviceBase::setIpcConfig(QString ipcConfig)
{
    if (m_ipcConfig == ipcConfig)
        return;

    m_ipcConfig = ipcConfig;
    emit ipcConfigChanged(ipcConfig);
}

void AiDeviceBase::setIsRuningAlg(bool isRuningAlg)
{
    if (m_isRuningAlg == isRuningAlg)
        return;

    m_isRuningAlg = isRuningAlg;
    emit isRuningAlgChanged(isRuningAlg);
}

void AiDeviceBase::convertorJsonToStruct(QString &jsonAlg, impCPC_Para_S &structAlg)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonAlg.toLocal8Bit().data());
    if( jsonDocument.isNull() ){
        qDebug()<< "===> please check the string "<< jsonAlg.toLocal8Bit().data();
     }
     QJsonObject jsonObject = jsonDocument.object();




     structAlg.enSensity =  IMP_CPC_SENS_NORMAL;
     structAlg.stDirection.stPe.s16X = 10;
     structAlg.stDirection.stPe.s16Y = 20;
     structAlg.stDirection.stPs.s16X = 20;
     structAlg.stDirection.stPs.s16Y =30;
     structAlg.stROIRect.s16X1 = 20;
     structAlg.stROIRect.s16Y1 = 20;
     structAlg.stROIRect.s16X2 = 40;
     structAlg.stROIRect.s16Y2 = 50;
     return;
}

void AiDeviceBase::convertorStructToJson(impCPC_Para_S &structAlg, QString &jsonAlg)
{

}
