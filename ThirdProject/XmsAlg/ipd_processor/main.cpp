#include <QCoreApplication>
#include <QTime>
#include <QVideoFrame>
#include "ipd_processor.h"

#include <QList>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QImage image("D://Sample/ipd_processor/ipd_processor/1.png");
    //BOOL tmpBool = image.load("D://Sample/ipd_processor/ipd_processor/1.png");
    bool tmp = image.load("D://Sample/ipd_processor/ipd_processor/1.png");
    printf("w(%d),h(%d)format(%d)bits(%d)count(%d) bool(%d)\n",image.width(),image.height(),image.format(),image.bits(),image.byteCount(),tmp);
    IMP_FrameQueue *fq = new IMP_FrameQueue();
    fq->InitFrameQueue();
    ipd_processor b;
    b.set_video_resolution(1920,1080);
    b.set_frame_queue(fq);
    b.setMessage("111111\n");
    b.start();
    b.push_frame(image);
    QTime dieTime = QTime::currentTime().addMSecs(5000);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    b.push_frame(image);
    dieTime = QTime::currentTime().addMSecs(5000);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    b.push_frame(image);
    dieTime = QTime::currentTime().addMSecs(5000);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    b.push_frame(image);
    dieTime = QTime::currentTime().addMSecs(5000);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    b.push_frame(image);
    dieTime = QTime::currentTime().addMSecs(5000);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    b.push_frame(image);
    dieTime = QTime::currentTime().addMSecs(5000);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    b.setMessage("333333\n");
    dieTime = QTime::currentTime().addMSecs(5000);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    b.wait();
    return a.exec();
}
