#include"mainwindow.h"
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QImage>
#include"cameraworker.h"
#include<iostream>
#include<QLabel>
#include<QVBoxLayout>
MainWindow::MainWindow(QWidget *parent):QWidget(parent){
    this->setWindowTitle("CMP");
    
    statustxt=new QLabel("Prese the button to connect signaling server !",this);
    videoLabel = new QLabel(this);
    // videoLabel->setMinimumSize(1280, 720);
    videoLabel->setFixedSize(640, 360);
    videoLabel->setScaledContents(true);
    QVBoxLayout *mainlayout=new QVBoxLayout(this);
    mainlayout->addWidget(statustxt);
    mainlayout->addWidget(videoLabel);
    CameraWorker* worker=new CameraWorker;
    sfu = new SFU();
    sfu->start();
    worker->start();
    connect(worker,&CameraWorker::framReady,this,&MainWindow::updateFrame);
    connect(worker,&CameraWorker::nalReady,this,&MainWindow::updatenalReady);
    // this->setWindowsFlags()
    // QMediaPlayer *player = new QMediaPlayer;
    // player->setSource(QUrl("https://avtshare01.rz.tu-ilmenau.de/avt-vqdb-uhd-1/test_1/segments/bigbuck_bunny_8bit_15000kbps_1080p_60.0fps_h264.mp4"));

    // QVideoWidget *videoWidget = new QVideoWidget;
    // player->setVideoOutput(videoWidget);

    // videoWidget->show();
    // player->play();
   

}
void MainWindow::updateFrame(const QImage& img){
    // std::cout<<"Data recive"<<std::endl;
    // static int count=0;
     
    videoLabel->setPixmap(
        QPixmap::fromImage(img)
    );
    // std::string msg="Data Comes count : "+std::to_string(count);
    // QString msgshow=QString::fromStdString(msg);
    // statustxt->setText(
    //    msgshow
    // );
    // count++;
    
}
void MainWindow::updatenalReady(const std::vector<uint8_t>& nal){
    sfu->sendNAL(nal);
    static int count=0;
    std::string msg=std::to_string(nal.size());
    QString msgshow=QString::fromStdString(msg);
    statustxt->setText(
       msgshow
    );
    count++;
}