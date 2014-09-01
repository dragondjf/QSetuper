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

#ifndef FTITLEBAR_H
#define FTITLEBAR_H

#include <QFrame>
#include <QToolButton>
#include <QLabel>


#define Title_Height 25

class FTitleBar : public QFrame
{
    Q_OBJECT
private:
    QIcon* logoIcon;
    QIcon* minIcon;
    QLabel* titleLabel;
    QToolButton* logoButton;
    QToolButton* minButton;
    QToolButton* closeButton;

private:
    void initData();
    void initConnect();
    void initUI();

public:
    QString title;
    static FTitleBar* instance;

public:
    explicit FTitleBar(QWidget *parent = 0);
    static FTitleBar* getInstace();



    void setTitleBarHeight(int height);


    void setLogoButton(const char * str, const char *objectName=NULL);
    QToolButton* getLogoButton();
    void setLogoButtonVisible(bool visible);
    bool isLogoButtonVisible();

    void setTitleLabel(QString str , const char *objectName=NULL);
    QLabel* getTitleLabel();
    void setTitleLabelVisible(bool visible);
    bool isTitleLabelVisible();

    void setMinButton(const char * str, const char *objectName=NULL);
    QToolButton* getMinButton();
    void setMinButtonVisible(bool visible);
    bool isMinButtonVisible();


    void setCloseButton(const char * str, const char *objectName=NULL);
    QToolButton* getCloseButton();
    void setCloseButtonVisible(bool visible);
    bool isCloseButtonVisible();

signals:
    void minimuned();
    void closed();

public slots:


};

#endif // FTITLEBAR_H
