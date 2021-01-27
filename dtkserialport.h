#include <QWidget>
#include <DMainWindow>
#include <DGuiApplicationHelper>
#include <DLabel>
#include <DPushButton>
#include <DTextEdit>
#include <DGroupBox>
#include <DComboBox>
#include <DCheckBox>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <DDialog>
#include <QDateTime>
DWIDGET_USE_NAMESPACE
#ifndef DTKSERIALPORT_H
#define DTKSERIALPORT_H


class DtkSerialport : public DMainWindow
{
    Q_OBJECT

public:
    DtkSerialport(DMainWindow *parent = nullptr);
    ~DtkSerialport();

private:
    QWidget *w=new QWidget;
    void setTheme(DGuiApplicationHelper::ColorType);
    //函数
    void system_init();
    //变量
    QSerialPort global_port;
};

#endif // DTKSERIALPORT_H
