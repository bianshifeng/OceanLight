#ifndef AIDEVICEBASE_H
#define AIDEVICEBASE_H

#include <QObject>
#include "imp_cpc_para.h"
#include "imp_cpc_api.h"
#include "imp_algo_type.h"

//QByteArray cstr("abcd");
//QString s = cstr;

//QByteArray cstr("abcd");
//QString s;
//s.prepend(cstr);

//QString s("hello");
//QByteArray cstr = s.toAscii();

//QString s("hello");
//QByteArray cstr = s.toLatin1();

class AiDeviceBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString algConfig READ algConfig WRITE setAlgConfig NOTIFY algConfigChanged)
    Q_PROPERTY(QString ipcConfig READ ipcConfig WRITE setIpcConfig NOTIFY ipcConfigChanged)
    Q_PROPERTY(bool isRuningAlg READ isRuningAlg WRITE setIsRuningAlg NOTIFY isRuningAlgChanged)
    Q_PROPERTY(bool isLiving READ isLiving NOTIFY isLivingChanged)

public:
    explicit AiDeviceBase(QObject *parent = 0);
    virtual ~AiDeviceBase();
    virtual void initDevice(const QString& ipcMessage, const QString& algMessage);
    QString algConfig() const;
    QString ipcConfig() const;
    bool isLiving() const;
    QString getAlgResult() const;
    void updateAlgConfig();
    bool isRuningAlg() const;

public slots:
    void setAlgConfig(QString algConfig);
    void setIpcConfig(QString ipcConfig);

    void setIsRuningAlg(bool isRuningAlg);

signals:
    void algConfigChanged(QString algConfig);
    void ipcConfigChanged(QString ipcConfig);
    void isLivingChanged(bool isLiving);

    void isRuningAlgChanged(bool isRuningAlg);

private:
    void convertorJsonToStruct(QString& jsonAlg, impCPC_Para_S& structAlg);
    void convertorStructToJson(impCPC_Para_S& structAlg, QString& jsonAlg);



private:
    //Sharedlib_kdxf* pr_pkdxf;
    IMP_HANDLE m_alg_hd;
    impCPC_Para_S m_alg_para;
    impCPC_Result_S m_alg_result;

    QString m_algConfig;
    QString m_ipcConfig;
    bool m_isLiving;
    QString m_algResult;
    bool m_isRuningAlg;
};

#endif // AIDEVICEBASE_H
