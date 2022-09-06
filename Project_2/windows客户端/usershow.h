#ifndef USERSHOW_H
#define USERSHOW_H

#include <QWidget>
#include <QPaintEvent>
#include<QImage>
#include<QMouseEvent>

namespace Ui {
class UserShow;
}

class UserShow : public QWidget
{
    Q_OBJECT

public:
    explicit UserShow(QWidget *parent = 0);
    ~UserShow();
signals:
    void SIG_itemClicked( int id , QString name);

public slots:
    void slot_setInfo(int id , QString name);
    void paintEvent(QPaintEvent *event);
    void slot_setImage( QImage& img);

    void mousePressEvent(QMouseEvent *event);
private:
    Ui::UserShow *ui;

    int m_id;
    QString m_userName;
    QImage m_img;
    friend class RoomDialog;
};

#endif // USERSHOW_H
