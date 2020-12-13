#include "dtkserialport.h"
#include <DWidgetUtil> //加入此头文件方可使用moveToCenter
#include <DSearchEdit>
#include <DTitlebar>
#include <QDebug>
#include <QMenu>
#include <QAction>

DtkSerialport::DtkSerialport(DMainWindow *parent)
    : DMainWindow(parent)
{
    //初始化主窗口 Initialize the main window
    setCentralWidget(w);//将w作为窗口的用户部分（整个窗口除了标题栏的部分）
    moveToCenter(this); //把窗口移动到屏幕中间
    DtkSerialport::resize(630,500); //改变窗口大小应当改变MainWindow的大小
\
    QHBoxLayout *layout = new QHBoxLayout(this);
    QHBoxLayout *layoutleft = new QHBoxLayout(this);
    QWidget *lineEditWidget = new QWidget(this);
    QWidget *sendBtnWidget = new QWidget(this);
    QWidget *textEditWidget = new QWidget(this);

    DLineEdit *lineEdit = new DLineEdit(lineEditWidget);
    \
  //  lineEdit->resize(400,40);


    DPushButton *sendBtn =new DPushButton(sendBtnWidget);
  \
    sendBtn->resize(80,40);
    sendBtn->setText("发送");


    DTextEdit *textEdit = new DTextEdit(textEditWidget);
    //textEdit->setParent(w);
   // textEdit->move(5,70);
   // textEdit->resize(522,500);
    //textEdit->show();

    layoutleft->setSpacing(0);
    layoutleft->addSpacing(30);
   // layout->addWidget(lineEditWidget);
    layoutleft->addSpacing(30);
    layoutleft->addWidget(sendBtnWidget);
    layoutleft->addSpacing(30);
    layoutleft->addWidget(textEditWidget);

    //在标题栏添加控件（其实可以把标题栏看成一个Widget,详细的说明请看文档) Add a control to the title bar (In fact, the title bar can be regarded as a Widget. Please refer to the document for detailed instructions.)
    DSearchEdit *searchEdit = new DSearchEdit;
    titlebar()->setCustomWidget(searchEdit);
    searchEdit->setFixedWidth(200);
    searchEdit->show();

    //在标题栏上添加一个菜单/菜单项 Add a menu/menu item to the title bar
    QMenu *menu=new QMenu;
    QAction *action=new QAction("action");
    menu->addAction(action);
    titlebar()->setMenu(menu);

    //设置标题栏上的图标 Set the icon on the title bar
    titlebar()->setIcon(QIcon::fromTheme("deepin-launcher"));

    //让程序适配浅色模式和深色模式 Adapt the program to light and dark model
    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged,this,&DtkSerialport::setTheme);
}

DtkSerialport::~DtkSerialport()
{
    delete w;
}

void DtkSerialport::setTheme(DGuiApplicationHelper::ColorType theme)
{
    //这个函数在程序运行之初就会被调用一次，而后每次更换主题颜色时被调用。 This function is called at the beginning of the program and then every time the theme color is changed.
    if(theme==DGuiApplicationHelper::LightType){ //在这个位置设置两种不同的样式 Set two different styles at this location
        //浅色模式 Light Mode
        qDebug()<<"Lighe";
    }else {
        //深色模式 Dark Mode
        qDebug()<<"Dark";
    }
}
