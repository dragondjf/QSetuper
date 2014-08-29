/****************************************************************************
**
** Copyright (C) 2014 dragondjf
**
** QFramer is a frame based on Qt5.3, you will be more efficient with it. 
** As an Qter, Qt give us a nice coding experience. With user interactive experience(UE) 
** become more and more important in modern software, deveployers should consider business and UE.
** So, QFramer is born. QFramer's goal is to be a mature solution 
** which you only need to be focus on your business but UE for all Qters.
**
** Version	: 0.2.2.0
** Author	: dragondjf
** Website	: https://github.com/dragondjf
** Project	: https://github.com/dragondjf/QCFramer
** Blog		: http://my.oschina.net/dragondjf/home/?ft=atme
** Wiki		: https://github.com/dragondjf/QCFramer/wiki
** Lincence: LGPL V2
** QQ: 465398889
** Email: dragondjf@gmail.com, ding465398889@163.com, 465398889@qq.com
** 
****************************************************************************/

#include "ftitlebar.h"
#include <QHBoxLayout>

FTitleBar* FTitleBar::instance = NULL;

FTitleBar::FTitleBar(QWidget *parent) :
    QFrame(parent)
{
    initData();
    initUI();
    initConnect();
}

FTitleBar* FTitleBar::getInstace()
{
    if(!instance)
    {
        instance = new FTitleBar();
    }
    return instance;
}

void FTitleBar::initData()
{
    title = tr("");
    logoButton = new QToolButton;
    logoButton->setObjectName(QString("titleToolButton"));
    titleLabel = new QLabel;

    minButton = new QToolButton;
    minButton->setObjectName(QString("titleToolButton"));
    closeButton = new QToolButton;
    closeButton->setObjectName(QString("titleToolButton"));

    logoButton->setFocusPolicy(Qt::NoFocus);
    minButton->setFocusPolicy(Qt::NoFocus);
    closeButton->setFocusPolicy(Qt::NoFocus);

}

void FTitleBar::initUI()
{
    setTitleBarHeight(Title_Height);
    setObjectName(QString("FTitleBar"));
    setLogoButton("://skin/QFramer.png");
    setTitleLabel(tr("QFramer"), "FTitleLabel");
    setMinButton("://skin/appbar.minus.png");
    setCloseButton("://skin/appbar.close.png", "close");

    QHBoxLayout* mainlayout = new QHBoxLayout;
    mainlayout->addWidget(logoButton);
    mainlayout->addWidget(titleLabel);
    mainlayout->addStretch();
    mainlayout->addWidget(minButton);
    mainlayout->addWidget(closeButton);
    mainlayout->setContentsMargins(0, 0, 5, 0);
    mainlayout->setSpacing(0);
    setLayout(mainlayout);
}

void FTitleBar::initConnect()
{
    connect(minButton, SIGNAL(clicked()), this, SIGNAL(minimuned()));
    connect(closeButton, SIGNAL(clicked()), this, SIGNAL(closed()));
}



void FTitleBar::setTitleBarHeight(int height)
{
    setFixedHeight(height);
    logoButton->setIconSize(QSize(height, height));
    titleLabel->setFixedHeight(height);
    minButton->setIconSize(QSize(height, height));
    closeButton->setIconSize(QSize(height, height));
}

void FTitleBar::setLogoButton(const char *str, const char *objectName)
{

    logoButton->setIcon(QIcon(QString(str)));
    logoButton->setIconSize(QSize(height(), height()));
    if(objectName)
        logoButton->setObjectName(QString(objectName));
}

QToolButton* FTitleBar::getLogoButton()
{
    return logoButton;
}


void FTitleBar::setLogoButtonVisible(bool visible)
{
    logoButton->setVisible(visible);
}

bool FTitleBar::isLogoButtonVisible()
{
    return logoButton->isVisible();
}


void FTitleBar::setTitleLabel(QString str, const char *objectName)
{
    titleLabel->setText(str);
    titleLabel->setFixedHeight(height());
    if (objectName)
    {
        titleLabel->setObjectName(QString(objectName));
    }
}

QLabel* FTitleBar::getTitleLabel()
{
    return titleLabel;
}

void FTitleBar::setTitleLabelVisible(bool visible)
{
    titleLabel->setVisible(visible);
}

bool FTitleBar::isTitleLabelVisible()
{
    return titleLabel->isVisible();
}


void FTitleBar::setMinButton(const char *str, const char *objectName)
{
    minButton->setIcon(QIcon(QString(str)));
    minButton->setIconSize(QSize(height(), height()));
    if (objectName)
    {
        minButton->setObjectName(QString(objectName));

    }
}

QToolButton* FTitleBar::getMinButton()
{
    return minButton;
}


void FTitleBar::setMinButtonVisible(bool visible)
{
    minButton->setVisible(visible);
}

bool FTitleBar::isMinButtonVisible()
{
    return minButton->isVisible();
}


void FTitleBar::setCloseButton(const char *str, const char *objectName)
{
    closeButton->setIcon(QIcon(QString(str)));
    closeButton->setIconSize(QSize(height(), height()));
    if (objectName)
    {

        closeButton->setObjectName(QString(objectName));

    }
}

QToolButton* FTitleBar::getCloseButton()
{
    return closeButton;
}


void FTitleBar::setCloseButtonVisible(bool visible)
{
    closeButton->setVisible(visible);
}

bool FTitleBar::isCloseButtonVisible()
{
    return closeButton->isVisible();
}
