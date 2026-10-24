#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QWidget>
#include<QImage>
#include<QLabel>
#include<vector>
#include"sfu.h"
class MainWindow : public QWidget{
    QLabel *statustxt;
    QLabel* videoLabel;
    SFU* sfu;
    public:
        explicit MainWindow(QWidget *parent=nullptr);
    public slots:
        void updateFrame(const QImage& image);
        // void updateFrame(const QImage& img);
        void updatenalReady(const std::vector<uint8_t>& nal);
};
#endif