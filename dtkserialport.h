#include <QWidget>
#include <DMainWindow>
#include <DGuiApplicationHelper>
#include <DLabel>
#include <DPushButton>
#include <DTextEdit>
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
};

#endif // DTKSERIALPORT_H
