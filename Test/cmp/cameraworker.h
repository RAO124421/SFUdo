#include<QObject>
#include<QImage>
#include<vector>
#include"H264Encoder.h"
class CameraWorker:public QObject{
    Q_OBJECT
    H264Encoder m_encoder;
    public:
        void start();
    signals:
        void framReady(const QImage& image);
        void nalReady(const std::vector<uint8_t>& nal);
};