#include "dtkserialport.h"
#include <DWidgetUtil> //加入此头文件方可使用moveToCenter
#include <DSearchEdit>
#include <DTitlebar>



DtkSerialport::DtkSerialport(DMainWindow *parent)
    : DMainWindow(parent)
{
    //初始化主窗口 Initialize the main window
    setCentralWidget(w);//将w作为窗口的用户部分（整个窗口除了标题栏的部分）
    moveToCenter(this); //把窗口移动到屏幕中间
    DtkSerialport::resize(630,500); //改变窗口大小应当改变MainWindow的大小
    DtkSerialport::setMinimumSize(630,500);

   QGridLayout* layout = new QGridLayout(w);
   QVBoxLayout *vlayout =new QVBoxLayout(w);
   DLineEdit *sendLineEdit = new DLineEdit;
   DTextEdit *messageBox = new DTextEdit;
   QHBoxLayout *hlayout = new QHBoxLayout(w);
   DPushButton *sendButton = new DPushButton;
   DLabel *status = new DLabel;
   status->setAlignment(Qt::AlignCenter);
   status->setText("尚未连接");
   DComboBox *inputAppend= new DComboBox;
   inputAppend->addItem("输入内容无追加");
   inputAppend->addItem("CR");
   inputAppend->addItem("LF");
   inputAppend->addItem("CR/LF");
   DPushButton *question = new DPushButton;
   question->setText("?");
   sendButton->setText("发送");
   sendButton->setShortcut(Qt::Key_Return);
   DPushButton *clearText = new DPushButton;
   clearText->setText("清屏");
   DComboBox *setting1= new DComboBox;
   setting1->addItem("/dev/ttyUSB0");
   setting1->addItem("/dev/ttyUSB1");
   setting1->addItem("/dev/ttyUSB2");
   setting1->addItem("/dev/ttyUSB3");
   setting1->addItem("/dev/ttyUSB4");
   DComboBox *setting2= new DComboBox;
   setting2->addItem("115200");
   setting2->addItem("921600");
   setting2->addItem("57600");
   setting2->addItem("38400");
   setting2->addItem("19200");
   setting2->addItem("9600");
   setting2->addItem("4800");
   DCheckBox *setting3=new DCheckBox;
   setting3->setText("以十六进制形式显示");
   DPushButton *openButton = new DPushButton(w);
   openButton->setText("打开");
   openButton->setShortcut(QKeySequence::Open);
   DPushButton *closeButton = new DPushButton;
   closeButton->setText("关闭");
   closeButton->setShortcut(QKeySequence::Close);

   layout->addWidget(messageBox,0,0,10,7);
   layout->addLayout(vlayout,0,8,10,3);
   vlayout->addWidget(status);
   vlayout->addWidget(sendLineEdit);
   vlayout->addLayout(hlayout);
   hlayout->addWidget(inputAppend);
   hlayout->addWidget(question);
   vlayout->addWidget(sendButton);
   vlayout->addWidget(clearText);
   vlayout->addSpacing(40);
  // vlayout->addStretch();
   vlayout->addWidget(setting1);
   vlayout->addWidget(setting2);
   vlayout->addWidget(setting3);
   vlayout->addWidget(openButton);
   vlayout->addWidget(closeButton);


   //setLayout(layout);

   //question button
   connect(question,&DPushButton::clicked,this,[](){
       DDialog dlg("解惑", "CR（Carriage Return）表示回车；LF（Line Feed）表示换行；Dos和Windows采用回车+换行（CR+LF）表示下一行；而UNIX/Linux采用换行符（LF）表示下一行；苹果机(MAC OS系统)则采用回车符（CR）表示下一行。\\r 是回车，return;  \\n 是换行，newline");
       dlg.addButton("好的", true, DDialog::ButtonWarning);
       dlg.setIcon(QIcon(":/images/hyw.ico"));
       dlg.exec();
   });

    //在标题栏添加控件（其实可以把标题栏看成一个Widget,详细的说明请看文档) Add a control to the title bar (In fact, the title bar can be regarded as a Widget. Please refer to the document for detailed instructions.)
    DSearchEdit *searchEdit = new DSearchEdit;
    titlebar()->setCustomWidget(searchEdit);
    searchEdit->setFixedWidth(200);
    searchEdit->show();

    //在标题栏上添加一个菜单/菜单项 Add a menu/menu item to the title bar
    QMenu *menu=new QMenu;
    QAction *action=new QAction("彩蛋");
    menu->addAction(action);
    connect(action, &QAction::triggered, this, []() {
        DDialog dlg("并没有", "想啥呢，我自己啥都不会还彩蛋");
        dlg.addButton("好吧", true, DDialog::ButtonWarning);
        dlg.setIcon(QIcon(":/images/hyw.ico"));
        dlg.exec();
    });
    titlebar()->setMenu(menu);

    //设置标题栏上的图标 Set the icon on the title bar
   // titlebar()->setIcon(QIcon::fromTheme("deepin-launcher"));
    titlebar()->setIcon(QIcon(":/images/hyw.ico"));

    //让程序适配浅色模式和深色模式 Adapt the program to light and dark model
    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged,this,&DtkSerialport::setTheme);
    system_init();
   // connect(openButton,&DPushButton::clicked,this,&DtkSerialport::openButton_click);
    //open
    connect(openButton, &DPushButton::clicked, this, [ = ] {
     status->setText("串口已连接");
     qInfo()<<setting1->currentText();
     qInfo()<<setting2->currentIndex();
     QString portname =setting1->currentText();
     global_port.setPortName(setting1->currentText());

     switch(setting2->currentIndex()){
     case 0:
        global_port.setBaudRate(QSerialPort::Baud115200);
         break;
     case 1:
        global_port.setBaudRate(921600);
         break;
     case 2:
        global_port.setBaudRate(QSerialPort::Baud57600);
         break;
     case 3:
        global_port.setBaudRate(QSerialPort::Baud19200);
         break;
     case 4:
        global_port.setBaudRate(QSerialPort::Baud9600);
         break;
     default:
        global_port.setBaudRate(QSerialPort::Baud4800);
         break;
        }
     global_port.open(QIODevice::ReadWrite);
     });
     //close
      connect(closeButton, &DPushButton::clicked, this, [ = ] {
          status->setText("已断开连接");
      global_port.close();
      });
      //send
      connect(sendButton, &DPushButton::clicked, this, [ = ] {
          QString data = sendLineEdit->text();
          qInfo()<<inputAppend->currentIndex();
          QByteArray sendArray = data.toLatin1();
          global_port.write(sendArray);
          switch(inputAppend->currentIndex()){
          case 0:
             //sendArray.append("");
              break;
          case 1:
              global_port.write("\r");
              break;
          case 2:
              global_port.write("\n");
              break;
          case 3:
              global_port.write("\r\n");
              break;
          default:
              //sendArray.append("");
              break;
             }


      });
      //receive
      connect(&global_port,&QSerialPort::readyRead, this, [ = ] {
          QByteArray receiveArray = global_port.readAll();
          qInfo()<<receiveArray;
          QDateTime current_time = QDateTime::currentDateTime();
          //QString current_date = current_time.toString("yyyy-MM-dd hh:mm:ss");
          QString time = current_time.toString("hh:mm:ss");
          if(setting3->checkState() == Qt::Checked)
          messageBox->insertPlainText(QString(receiveArray.toHex()).toUpper().append(' '));
          else
          messageBox->insertPlainText(QString(receiveArray));
          if (QString(receiveArray)=="\r")
          messageBox->insertPlainText(time);
          messageBox->moveCursor(QTextCursor::End);

      });

      //clear text
      connect(clearText,&DPushButton::clicked, messageBox, &DTextEdit::clear);



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
        qDebug()<<"Dark";
    }
}

void DtkSerialport::system_init()
{
   qInfo()<<"系统初始化"<<endl;
   global_port.setParity(QSerialPort::NoParity);
   global_port.setDataBits(QSerialPort::Data8);
   global_port.setStopBits(QSerialPort::OneStop);
}
