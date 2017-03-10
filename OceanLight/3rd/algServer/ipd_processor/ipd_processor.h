#ifndef IPD_PROCESSOR_H
#define IPD_PROCESSOR_H

#include "alg_processor/alg_processor.h"
class IPDProcessor : public AlgProcessor
{
    Q_OBJECT
public:
    IPDProcessor();
protected:
    void run();
    void setEmitIpdData(QJsonObject &dataStr);

signals:
    void sig_alg_result(const QString &algMessage);
};

#endif // IPD_PROCESSOR_H
