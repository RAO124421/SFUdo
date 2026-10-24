#ifndef HEADER_H
#define HEADER_H
#include<QWidget>
#include<QFrame>
class Header:public QWidget{
    Q_OBJECT
    private:
        QFrame *header;
    public:
        explicit Header(QWidget *parent=nullptr);
        // QFrame* getHeaderWidget();
};
#endif