#include <QApplication>
#include"mainwindow.h"

int main(int argc,char *argv[]){
    QApplication app(argc,argv);
    // int id1 = QFontDatabase::addApplicationFont(":/fonts/inter-bold.ttf");
    // int id2 = QFontDatabase::addApplicationFont(":/fonts/inter-regl.ttf");
    // int id3 n                                         = QFontDatabase::addApplicationFont(":/fonts/inter-semibold.ttf");
    // if (id1 == -1 || id2 == -1 || id3 == -1) {
    //     qWarning() << "Warning: One or more Inter fonts failed to load from resources!";
    // }
    // QFile file(":/styles/global.qss");
    // if(file.open(QFile::ReadOnly))
    // {
    //     app.setStyleSheet(file.readAll());
    // }
    // app.setWindowIcon(QIcon(":/icons/logo.png"));
    MainWindow mainWindow;
    mainWindow.showMaximized();
   

    return app.exec();


}
