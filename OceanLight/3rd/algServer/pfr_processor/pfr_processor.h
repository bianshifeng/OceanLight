#ifndef PFR_PROCESSOR_H
#define PFR_PROCESSOR_H

#include <QObject>
#include "alg_processor/alg_processor.h"

class PFRProcessor : public AlgProcessor
{
    Q_OBJECT
public:
    explicit PFRProcessor();

signals:

public slots:

    void slot_register_face(){}

    // QThread interface
protected:
    void run();



};

#endif // PFR_PROCESSOR_H
