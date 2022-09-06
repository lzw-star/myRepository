#ifndef WECHATDIALOG_H
#define WECHATDIALOG_H

#include <QDialog>
#include<QCloseEvent>

namespace Ui {
class WeChatDialog;
}

class WeChatDialog : public QDialog
{
    Q_OBJECT
signals:
    void SIG_close();
    void SIG_createRoom();
    void SIG_joinRoom();
public:
    explicit WeChatDialog(QWidget *parent = 0);
    ~WeChatDialog();

    void closeEvent(QCloseEvent *event);

    void setInfo( QString name , int icon = 1);
private slots:
    void on_pb_create_clicked();

    void on_pb_join_clicked();

private:
    Ui::WeChatDialog *ui;
};

#endif // WECHATDIALOG_H
