#ifndef RAMUSAGEWIDGET_H
#define RAMUSAGEWIDGET_H

#include <QWidget>
#include <QVector>
#include <QString>

class RamUsageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RamUsageWidget(
        const QString &title,
        double currentValue,
        const QString &unit,
        double maxValue,
        const QVector<double> &data,
        QWidget *parent = nullptr
    );

    void setTitle(const QString &title);
    void setCurrentValue(double value);
    void setData(const QVector<double> &data);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString graphTitle;
    QString valueUnit;

    double currentValue;
    double maxValue;

    QVector<double> usageData;

    void drawBackground(QPainter &painter);
    void drawHeader(QPainter &painter);
    void drawGraph(QPainter &painter, const QRectF &graphRect);
};

#endif // RAMUSAGEWIDGET_H