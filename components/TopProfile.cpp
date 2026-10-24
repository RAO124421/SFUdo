#include"TopProfile.h"

#include<QHBoxLayout>
#include<QLabel>
#include<QToolButton>
#include<QSizePolicy>
#include<QStyle>

#include<QPixmap>
#include<QPainter>
#include<QIcon>

TopProfile::TopProfile(const QString &name, QWidget *parent)
    : QWidget(parent),
      personName(name)
{
    setObjectName("TopProfile");
    setAttribute(Qt::WA_StyledBackground, true);

    /*
     * Height fixed 35px.
     * Width wrap content.
     */
    setFixedHeight(35);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    QHBoxLayout *layout = new QHBoxLayout(this);

    /*
     * Margin 5px.
     */
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(6);

    /*
     * Left profile circle.
     */
    profileCircle = new QLabel(this);
    profileCircle->setObjectName("TopProfileCircle");
    profileCircle->setFixedSize(25, 25);
    profileCircle->setAlignment(Qt::AlignCenter);

    QString firstLetter = personName.isEmpty()
                              ? "U"
                              : personName.left(1).toUpper();

    profileCircle->setText(firstLetter);

    /*
     * Person name.
     */
    nameLabel = new QLabel(personName, this);
    nameLabel->setObjectName("TopProfileName");
    nameLabel->setAlignment(Qt::AlignVCenter);
    nameLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);


    arrowButton = new QToolButton(this);
    arrowButton->setObjectName("TopProfileArrow");
    arrowButton->setFixedSize(18, 18);
    arrowButton->setCursor(Qt::PointingHandCursor);
    arrowButton->setAutoRaise(true);

    QIcon defaultIcon = style()->standardIcon(QStyle::SP_ArrowDown);

    QPixmap pixmap = defaultIcon.pixmap(12, 12);

    QPixmap tintedPixmap(pixmap.size());
    tintedPixmap.fill(Qt::transparent);

    QPainter painter(&tintedPixmap);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawPixmap(0, 0, pixmap);

    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(tintedPixmap.rect(), QColor("white")); // icon tint color
    painter.end();

    arrowButton->setIcon(QIcon(tintedPixmap));
    arrowButton->setIconSize(QSize(12, 12));

  

    layout->addWidget(profileCircle);
    layout->addWidget(nameLabel);
    layout->addWidget(arrowButton);

    adjustSize();
}

void TopProfile::setName(const QString &name)
{
    personName = name;
    nameLabel->setText(personName);

    QString firstLetter = personName.isEmpty()
                              ? "U"
                              : personName.left(1).toUpper();

    profileCircle->setText(firstLetter);

    adjustSize();
}

QString TopProfile::name() const
{
    return personName;
}