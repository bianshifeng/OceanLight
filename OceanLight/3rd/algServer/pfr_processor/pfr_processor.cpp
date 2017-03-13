#include <QDebug>
#include <QJsonObject>
#include <QCoreApplication>
#include <QtNetwork>
#include "pfr_processor.h"

PFRProcessor::PFRProcessor():
    m_queue(Q_NULLPTR),
    videoHeight(0),
    videoWidth(0),
    stopped(false)
{
    stopped = false;
    m_queue = new IMP_StringQueue();
    moveToThread(this);
}

PFRProcessor::~PFRProcessor()
{
    stopped = true;
    if(m_queue)
    {
        delete m_queue;
    }
}

void PFRProcessor::set_video_resolution(int width, int height)
{
    videoWidth = width;
    videoHeight = height;
}

void PFRProcessor::initFrameQueue()
{
    m_queue->InitQueue();
}

#define FILE_MAX_SIZE 1024*1024
void Usage(char* ctrl)
{
    printf("Usage:\n");
    printf("\t%s  <SERVER_IP> \n",ctrl);
    printf("    SERVER_IP  ------  Server Ip addr \n");
}

void itostring(int num, char * arr)
{
    int i = 0,tmp = num;
    while(tmp)
    {
        i++;
        tmp = tmp/10;
    }
    arr[i] = '\0';
    for(i;i>0;i--)
    {
        arr[i-1] = num%10 +'0';
        num = num/10;
    }
}

int sent_pic(QTcpSocket *client,char *filename,int len)
{
    int ret = 0;
    int tmp = 0;
    int send_size = 0;
    char buff[1024] = {0};
    FILE *pfile = fopen(filename,"rb");
    if( !pfile )
    {
        printf("No such file!~\n");
        return -1;
    }
    //send(fd,filename,len,0);
    client->write(filename,len);
    client->waitForBytesWritten();
    //usleep(500);
    fseek(pfile,0,2);
    int size = ftell(pfile);
    itostring(size,buff);
    //ret = send(fd,buff,6,0);
    client->write(buff,6);
    client->waitForBytesWritten();
    printf("File size = %s \n",buff);
    fseek(pfile,0,0);
    int count = 0 ;
    while(1)
    {
        ret = fread(buff,1,1024,pfile);
        send_size += ret;
        //tmp = send(fd,buff,ret,0);
        printf("\n");
        tmp = client->write(buff,ret);
        client->waitForBytesWritten();
        //printf("\n");
        if(tmp != 1024)
            break;
        //recv(fd,buff,1,0);
        client->waitForReadyRead();
        client->read(buff,1);
    }

    printf("Send PIC succes: %s (%d B)\n",filename,send_size);

    fclose(pfile);
    pfile = NULL;
    return 0;
}

int Face_Regist(QTcpSocket *client,char *filename,int len, char* name, int namelen)
{
    char buff[64];
    int ret = 0;
    printf(" <<<<<< Input regist Name:");
    name[namelen] = '\0';
    printf("%s\n",name);
    //ret = send(fd,buff,16,0);
    client->write(name,16);
    client->waitForBytesWritten();
    do{
        /*printf(" <<<<<< Choose send pic File:");
        scanf("%s",buff);
        scanf("%*[^\n]");
        scanf("%*C");
        buff[strlen(buff)] = '\0';
        ret = sent_pic(client,buff,strlen(buff)+1);*/
        ret = sent_pic(client,filename,len + 1);
    }while(ret != 0);

    //recv(fd,buff,1,0);
    client->waitForReadyRead();
    client->read(buff,1);
    if( buff[0] == '1')
    {
        printf(" Regist succes \n");
    }else{
        printf(" Regist failed \n");
    }
    return 0;
}

int Face_Recog(QTcpSocket *client,char *filename,int len)
{
    char buff[64] = {0};
    int ret = 0;
    do{
        printf(" <<<<<< Choose send pic File:");
        /*scanf("%s",buff);
        scanf("%*[^\n]");
        scanf("%*C");
        buff[strlen(buff)] = '\0';
        ret = sent_pic(client,buff,strlen(buff)+1);*/
        ret = sent_pic(client,filename,len + 1);
    }while(ret != 0);
    //recv(fd,buff,16,0);

    client->waitForReadyRead();
    client->read(buff,16);
    //recogniziton result
    printf(" >>>>>> Found :  %s\n",buff);

    //recv(fd,buff,1,0);
    client->waitForReadyRead();
    client->read(buff,1);
    if( buff[0] == '1')
    {
        printf(" Recog succes \n");
    }else{
        printf(" Recog failed \n");
    }
    return 0;
}
void PFRProcessor::run()
{
    QTcpSocket *client;
    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress("58.246.122.150"), 8888);
    //client->connectToHost(QHostAddress("192.168.3.144"), 8888);
    char tmprecv;
    IMP_PFR_PATH *path_src;
    while(!stopped)
    {
        client->waitForReadyRead();
        client->read(&tmprecv,1);

        printf("recv : %c\n",tmprecv);
        m_queue->Peek(&path_src);
        if(NULL == path_src)
        {
            usleep(100000);
            continue;
        }

        if(path_src->recOrReg == 1)
        {
            QString *zero = new QString("1");
            client->write((const char*)zero->data(),1);
            client->waitForBytesWritten();
            printf("path %s\n",path_src->path);
            Face_Recog(client,path_src->path,path_src->pathlen);
        }
        else if(path_src->recOrReg == 0)
        {
            QString *one = new QString("0");
            client->write((const char*)one->data(),1);
            client->waitForBytesWritten();
            Face_Regist(client,path_src->path,path_src->pathlen,path_src->name,path_src->namelen);
        }
        qDebug()<<"res";
        m_queue->Remove();
        usleep(100000);
    }


    stopped = false;
}

void PFRProcessor::stop()
{
    stopped = true;
}

void PFRProcessor::startProcessor()
{
    this->stopped = false;
    this->start();

}


void PFRProcessor::setEmitPfrData(QString &dataStr)
{
    qDebug() << dataStr;
}
void PFRProcessor::set_frame_queue(IMP_StringQueue* queue)
{
    m_queue = queue;
}
void PFRProcessor::push_frame(QString &file_path,int recOrReg,QString &name)
{
    IMP_PFR_PATH *free_node = m_queue->GetFrameAddr();
    if(!free_node) return;

    QByteArray tmpba = file_path.toLatin1();
    char *tmpc = tmpba.data();
    memcpy(free_node->path,tmpc,strlen(tmpc));

    QByteArray tmpba1 = name.toLatin1();
    char *tmpc1 = tmpba1.data();
    memcpy(free_node->name,tmpc1,strlen(tmpc1));
    free_node->pathlen = strlen(tmpc);
    free_node->namelen = strlen(tmpc1);
    free_node->recOrReg = recOrReg;

}
