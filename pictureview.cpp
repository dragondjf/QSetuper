#include "PictureView.h"
#include <QPropertyAnimation>


PictureView::PictureView(QWidget *parent) :
    QLabel(parent)
{
    initData();
    initUI();
    initConnect();
}

void PictureView::initData()
{
    pictures << "://skin/1.jpg";
    pictures << "://skin/2.jpg";
    pictures << "://skin/3.jpg";
    pictures << "://skin/4.jpg";
    pictures << "://skin/5.jpg";
    currentIndex = 0;
    baseStyle = QString("QLabel{\
                border-image:url(%1);\
            }");
}

void PictureView::initUI()
{

//    setStyleSheet(baseStyle.arg(pictures[currentIndex]));

    setPixmap(QPixmap(pictures[currentIndex]));

//    animationPPT();
}

void PictureView::initConnect()
{

}

void PictureView::animationPPT()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    connect(animation, SIGNAL(finished()), this, SLOT(updatePicture()));
    connect(animation, SIGNAL(finished()), this, SLOT(animationPPT()));
    animation->setDuration(2000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
}

void PictureView::updatePicture()
{
    if (currentIndex < pictures.length() - 1){
        currentIndex += 1;
    }else{
        currentIndex = 0;
    }
//    setStyleSheet(baseStyle.arg(pictures[currentIndex]));
    setPixmap(QPixmap(pictures[currentIndex]));
}
