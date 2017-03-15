#ifndef PFR_PROCESSOR_H
#define PFR_PROCESSOR_H

#include <QThread>
#include <iostream>
#include <QVideoFrame>
#include "IMP_StringQueue.h"
#include "common/imp_algo_type.h"
class PFRProcessor : public QThread
{
    Q_OBJECT
public:
    PFRProcessor();
    ~PFRProcessor();
    void initFrameQueue();
    void push_frame(QString &file_path, int recOrReg, QString &name);
    void stop();
    void startProcessor();

protected:
    void run();

signals:
    void sig_alg_result(const QString &message);
    void sig_reg_result(const QString &message);


 private:
    IMP_StringQueue* m_queue;
    volatile bool stopped;
};

#endif // PFR_PROCESSOR_H
