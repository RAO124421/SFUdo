#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QWidget>
#include"../SSsokcet/signaling.h"
#include"../core/eventqueue.h"
#include"../core/sfuconnections.h"
class LoginWindow : public QWidget{
    Q_OBJECT
    private:
        WebSocketClient webSocketClient;
        EventQueue eventQueue;
        Connections connections;

    public:
        explicit LoginWindow(QWidget *parent=nullptr);
};
#endif