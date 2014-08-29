#ifndef PictureView_H
#define PictureView_H

#include <QLabel>
#include <QWidget>
#include <QTimer>

class PictureView : public QLabel
{
    Q_OBJECT
public:
    QStringList pictures;
    QString baseStyle;
    int currentIndex;
public:
    explicit PictureView(QWidget *parent = 0);
    void initData();
    void initUI();
    void initConnect();

signals:

public slots:
    void animationPPT();
    void updatePicture();
};

#endif // PictureView_H
