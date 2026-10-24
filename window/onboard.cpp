#include"onboard.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include"../components/header.h"
#include"../components/onServer.h"
#include"../components/onNetwrok.h"
#include"../components/onSystem.h"
#include"../components/onRoomList.h"
OnBoardScreen::OnBoardScreen(QWidget *parent):QWidget(parent){
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint|Qt::NoDropShadowWindowHint);
    this->setObjectName("onboard");
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    Header *header=new Header(this);
    mainLayout->addWidget(header);

    
    QWidget *body = new QWidget(this);
    body->setObjectName("onboard-body");
    QHBoxLayout *hmainlayout=new QHBoxLayout(body);
    hmainlayout->setContentsMargins(0, 0, 0, 0);
    hmainlayout->setSpacing(0);
    OnNetwrok *onNetwrok=new OnNetwrok(body);
    OnServer *onServer=new OnServer(body);
    OnSystem *onSystem=new OnSystem(body);
    OnRoomList *onRoomList=new OnRoomList(body);
    hmainlayout->addWidget(onRoomList,25);
    hmainlayout->addWidget(onServer,25);
    hmainlayout->addWidget(onNetwrok,25);
    hmainlayout->addWidget(onSystem,25);





    mainLayout->addWidget(body,1);


    
}

