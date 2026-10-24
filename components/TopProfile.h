#ifndef TOPPROFILE_H
#define TOPPROFILE_H

#include <QWidget>
#include <QString>

class QLabel;
class QToolButton;

class TopProfile : public QWidget
{
    Q_OBJECT

public:
    explicit TopProfile(
        const QString &name,
        QWidget *parent = nullptr
    );

    void setName(const QString &name);
    QString name() const;

private:
    QLabel *profileCircle;
    QLabel *nameLabel;
    QToolButton *arrowButton;

    QString personName;
};

#endif // TOPPROFILE_H