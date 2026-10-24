#include "RamUsageWidget.h"

#include <QPainter>
#include <QPen>
#include <QFont>
#include <QPaintEvent>
#include <QSizePolicy>
#include <QtMath>

RamUsageWidget::RamUsageWidget(
    const QString &title,
    double value,
    const QString &unit,
    double max,
    const QVector<double> &data,
    QWidget *parent
)
    : QWidget(parent),
      graphTitle(title),
      valueUnit(unit),
      currentValue(value),
      maxValue(max),
      usageData(data)
{
    setMinimumHeight(95);
    setMaximumHeight(105);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    if (maxValue <= 0.0) {
        maxValue = 1.0;
    }

    if (usageData.isEmpty()) {
        usageData = {
            0.001, 0.002, 0.0015, 0.003, 0.0025,
            0.004, 0.0035, 0.002, 0.00308
        };
    }
}

void RamUsageWidget::setTitle(const QString &title)
{
    graphTitle = title;
    update();
}

void RamUsageWidget::setCurrentValue(double value)
{
    currentValue = value;

    if (!usageData.isEmpty()) {
        usageData.removeFirst();
    }

    usageData.append(currentValue);
    update();
}

void RamUsageWidget::setData(const QVector<double> &data)
{
    usageData = data;
    update();
}

void RamUsageWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    drawBackground(painter);
    drawHeader(painter);

    QRectF graphRect(
        10,
        32,
        width() - 20,
        height() - 40
    );

    drawGraph(painter, graphRect);
}

void RamUsageWidget::drawBackground(QPainter &painter)
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(18, 20, 26));
    painter.drawRect(rect());

    painter.setPen(QPen(QColor(55, 60, 70), 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}

void RamUsageWidget::drawHeader(QPainter &painter)
{
    QFont titleFont;
    titleFont.setPointSize(8);
    titleFont.setBold(true);

    painter.setFont(titleFont);
    painter.setPen(QColor(220, 225, 235));

    painter.drawText(
        QRectF(10, 4, width() / 2, 18),
        Qt::AlignLeft | Qt::AlignVCenter,
        graphTitle
    );

    QFont valueFont;
    valueFont.setPointSize(9);
    valueFont.setBold(true);

    painter.setFont(valueFont);
    painter.setPen(QColor(80, 210, 160));

    QString valueText = QString::number(currentValue, 'f', 6) + " " + valueUnit;

    painter.drawText(
        QRectF(width() - 160, 4, 150, 18),
        Qt::AlignRight | Qt::AlignVCenter,
        valueText
    );

    QFont smallFont;
    smallFont.setPointSize(7);

    painter.setFont(smallFont);
    painter.setPen(QColor(135, 145, 160));

    painter.drawText(
        QRectF(10, 20, 120, 12),
        Qt::AlignLeft | Qt::AlignVCenter,
        "Usage history"
    );
}

void RamUsageWidget::drawGraph(QPainter &painter, const QRectF &graphRect)
{
    if (usageData.size() < 2)
        return;

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(10, 12, 16));
    painter.drawRect(graphRect);

    painter.setPen(QPen(QColor(70, 76, 88), 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(graphRect);

    painter.setPen(QPen(QColor(42, 48, 58), 1));

    for (int i = 1; i < 4; i++) {
        qreal y = graphRect.top() + graphRect.height() / 4 * i;
        painter.drawLine(QPointF(graphRect.left(), y),
                         QPointF(graphRect.right(), y));
    }

    for (int i = 1; i < 8; i++) {
        qreal x = graphRect.left() + graphRect.width() / 8 * i;
        painter.drawLine(QPointF(x, graphRect.top()),
                         QPointF(x, graphRect.bottom()));
    }

    QVector<QPointF> points;

    for (int i = 0; i < usageData.size(); i++) {
        qreal x = graphRect.left()
                  + graphRect.width() / (usageData.size() - 1) * i;

        double value = qBound(0.0, usageData[i], maxValue);

        qreal y = graphRect.bottom()
                  - graphRect.height() * value / maxValue;

        points.append(QPointF(x, y));
    }

    QPen linePen(QColor(80, 210, 160), 2);
    linePen.setCapStyle(Qt::SquareCap);
    linePen.setJoinStyle(Qt::MiterJoin);

    painter.setPen(linePen);

    for (int i = 1; i < points.size(); i++) {
        painter.drawLine(points[i - 1], points[i]);
    }

    QPointF last = points.last();

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(80, 210, 160));
    painter.drawRect(QRectF(last.x() - 2, last.y() - 2, 4, 4));
}