#include "alg_server.h"



void AlgServer::setCameraImage(const QImage &image)
{
    Q_UNUSED(image);
}

void AlgServer::setImage(const QImage &image)
{
    Q_UNUSED(image);

    emit sig_alg_test_data("sdsdfsdfsfsdf");
}

AlgServer::AlgServer(QObject *parent) : QObject(parent)
{

}
