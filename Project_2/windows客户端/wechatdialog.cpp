#include "wechatdialog.h"
#include "ui_wechatdialog.h"
#include<QMessageBox>
#include"qDebug"

WeChatDialog::WeChatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeChatDialog)
{
    ui->setupUi(this);

    setWindowTitle("视频会议v1.0");
}

WeChatDialog::~WeChatDialog()
{
    qDebug() << __func__;
    delete ui;
}

//关闭事件
void WeChatDialog::closeEvent(QCloseEvent *event)
{
    qDebug() << __func__;
    if( QMessageBox::question( this , "提示", "是否退出?")
            == QMessageBox::Yes )
    {
        Q_EMIT SIG_close();
        event->accept();
    }else
    {
        event->ignore();
    }

//    event->accept(); // 执行
    //    event->ignore(); // 忽略
}

void WeChatDialog::setInfo(QString name, int icon)
{
    //设置名字 头像
    ui->lb_name->setText( name );
}

void WeChatDialog::on_pb_create_clicked()
{
    Q_EMIT SIG_createRoom();
}

void WeChatDialog::on_pb_join_clicked()
{
    Q_EMIT SIG_joinRoom();
}
