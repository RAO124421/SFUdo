#include"loginwindow.h"
#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<iostream>
#include<QTimer>
#include<thread>
LoginWindow::LoginWindow(QWidget *parent):QWidget(parent),webSocketClient(&eventQueue,&connections){
    resize(500,300);
    QVBoxLayout *mainlayout=new QVBoxLayout(this);
    mainlayout->setAlignment(Qt::AlignTop);
    mainlayout->setContentsMargins(0,0,0,0);
    QPushButton *btn=new QPushButton("Connect to the Server",this);
    btn->setObjectName("connectbtn");

    QLabel *statustxt=new QLabel("Prese the button to connect signaling server !",this);
    statustxt->setAlignment(Qt::AlignCenter);
    statustxt->setObjectName("statustxt");

    
    QTimer *timer=new QTimer(this);
    connect(timer,&QTimer::timeout,[this,statustxt](){
        Event event;
        while(eventQueue.pop(event)){
            if(event.type=="connected"){
                statustxt->setText("Connected");
                statustxt->setStyleSheet("color:green");
                continue;
            }
            if(event.type=="message"){
                QString msg=QString::fromStdString(event.data);
                statustxt->setText(msg);
                statustxt->setStyleSheet("color:green");
                continue;
            }
            if(event.type=="setConnected"){
                QString msg=QString::fromStdString("We are Connected to Signaling Server");
                statustxt->setText(msg);
                statustxt->setStyleSheet("color:green");
                continue;
            }
            
        }
    });
    connect(btn,&QPushButton::clicked,[=](){
        std::cout<<"This is Rao "<<std::endl;
        statustxt->setText("Connecting...");
        timer->start(16);
        std::thread([=](){
            webSocketClient.connectWebSocket();
        }).detach();
        
    });

    mainlayout->addWidget(btn);
    mainlayout->addWidget(statustxt);


   


}