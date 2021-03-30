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
    DtkSerialport::resize(1000,900); //改变窗口大小应当改变MainWindow的大小
    DtkSerialport::setMinimumSize(1000,900);
    static bool SaveLog=false;

   QGridLayout* layout = new QGridLayout(w);
   QVBoxLayout *vlayout =new QVBoxLayout(w);
   QVBoxLayout *vTextlayout =new QVBoxLayout(w);
   QHBoxLayout *filelayout = new QHBoxLayout(w);
   DLineEdit *sendLineEdit = new DLineEdit;
   sendLineEdit->setMaximumHeight(100);
   DTextEdit *messageBox = new DTextEdit;
   DTextEdit *filemessageBox = new DTextEdit;

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
   foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
   {
       setting1->addItem(serialPortInfo.portName());
   }
//   setting1->addItem("/dev/ttyUSB0");
//   setting1->addItem("/dev/ttyUSB1");
//   setting1->addItem("/dev/ttyUSB2");
//   setting1->addItem("/dev/ttyUSB3");
//   setting1->addItem("/dev/ttyUSB4");

   DComboBox *setting2= new DComboBox;
   setting2->addItem("115200");
   setting2->addItem("941176");
   setting2->addItem("921600");
   setting2->addItem("57600");
   setting2->addItem("38400");
   setting2->addItem("19200");
   setting2->addItem("9600");
   setting2->addItem("4800");
   setting2->addItem("1000000");
   DCheckBox *setting3=new DCheckBox;
   setting3->setText("以十六进制形式显示");
   DPushButton *openButton = new DPushButton(w);
   openButton->setText("打开");
   openButton->setShortcut(QKeySequence::Open);
   DPushButton *closeButton = new DPushButton;
   closeButton->setText("关闭");
   closeButton->setShortcut(QKeySequence::Close);
   DPushButton *refreshButton = new DPushButton;
   refreshButton->setText("刷新串口列表");


   DPushButton *saveButton = new DPushButton(w);
   saveButton->setText("保存日志");
   DComboBox *sendtime= new DComboBox;
   sendtime->addItem("0ms");
   sendtime->addItem("30");
   sendtime->addItem("35");
   sendtime->addItem("40");
   sendtime->addItem("45");
   sendtime->addItem("50");
   sendtime->addItem("55");
   sendtime->addItem("60");
   sendtime->addItem("65");
   sendtime->addItem("70");
   sendtime->addItem("100");
   sendtime->addItem("150");
   sendtime->addItem("200");
   sendtime->addItem("300");
   sendtime->addItem("400");
   sendtime->addItem("500");
   sendtime->addItem("1000");
   DPushButton *readButton = new DPushButton;
   readButton->setText("向串口发送日志");


   layout->addLayout(vTextlayout,0,0,10,7);
   vTextlayout->addWidget(messageBox,7);
   vTextlayout->addWidget(filemessageBox,3);
   layout->addLayout(vlayout,0,8,10,3);
   vlayout->addStretch(1);
   vlayout->addWidget(status);
   vlayout->addStretch(1);
   vlayout->addWidget(sendLineEdit);
   vlayout->addLayout(hlayout);
   hlayout->addWidget(inputAppend);
   hlayout->addWidget(question);
   vlayout->addWidget(sendButton);
   vlayout->addWidget(clearText);
   vlayout->addStretch(1);
  // vlayout->addStretch();
   vlayout->addWidget(setting1);
   vlayout->addWidget(refreshButton);
   vlayout->addWidget(setting2);
   vlayout->addWidget(setting3);
   vlayout->addWidget(openButton);
   vlayout->addWidget(closeButton);
   vlayout->addStretch(1);
   vlayout->addLayout(filelayout);
   filelayout->addWidget(saveButton);
   filelayout->addWidget(sendtime);
   filelayout->addWidget(readButton);
   vlayout->addStretch(1);



   //setLayout(layout);

   //question button
   connect(question,&DPushButton::clicked,this,[](){
       DDialog dlg("解惑", "CR（Carriage Return）表示回车；LF（Line Feed）表示换行；Dos和Windows采用回车+换行（CR+LF）表示下一行；而UNIX/Linux采用换行符（LF）表示下一行；苹果机(MAC OS系统)则采用回车符（CR）表示下一行。\\r 是回车，return;  \\n 是换行，newline");
       dlg.addButton("好的", true, DDialog::ButtonWarning);
       dlg.setIcon(QIcon(":/images/hyw.ico"));
       dlg.exec();
   });


    DSearchEdit *searchEdit = new DSearchEdit;
    titlebar()->setCustomWidget(searchEdit);
    searchEdit->setFixedWidth(200);
    searchEdit->show();

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


    //open button
    connect(openButton, &DPushButton::clicked, this, [ = ] {
     openButton->setDisabled(true);
     closeButton->setEnabled(true);
//     qInfo()<<setting1->currentText();
//     qInfo()<<setting2->currentIndex();
     QString portname =setting1->currentText();
     global_port.setPortName(setting1->currentText());

     switch(setting2->currentIndex()){
     case 0:
        global_port.setBaudRate(QSerialPort::Baud115200);
         break;
     case 1:
        global_port.setBaudRate(941176);
         break;
     case 2:
        global_port.setBaudRate(921600);
         break;
     case 3:
        global_port.setBaudRate(QSerialPort::Baud57600);
         break;
     case 4:
        global_port.setBaudRate(QSerialPort::Baud38400);
         break;
     case 5:
        global_port.setBaudRate(QSerialPort::Baud19200);
         break;
     case 6:
        global_port.setBaudRate(QSerialPort::Baud9600);
         break;
     case 7:
        global_port.setBaudRate(QSerialPort::Baud4800);
        qDebug()<<"4800";
         break;
     case 8:
        global_port.setBaudRate(1000000);
         break;
     default:
        global_port.setBaudRate(QSerialPort::Baud4800);
         break;
        }
     if(global_port.open(QIODevice::ReadWrite))

     {
         QSerialPortInfo SerialInfo(portname);
         //status->setText("串口已连接");
         QString Info = "串  口  已  连  接\n\n"+SerialInfo.portName()+"\n"+SerialInfo.description()+"\n"+SerialInfo.manufacturer()+"\n"+SerialInfo.serialNumber()+"\n"+SerialInfo.systemLocation();
         status->setText(Info);
     }
     else
         status->setText("无法连接至有效串口");

     });

     //close button
      connect(closeButton, &DPushButton::clicked, this, [ = ] {
          openButton->setEnabled(true);
          closeButton->setDisabled(true);
          status->setText("串口连接已断开");
          global_port.close();
      });

      //send button
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

      //receive button
      connect(&global_port,&QSerialPort::readyRead, this, [ = ] {
          QByteArray receiveArray = global_port.readAll();
//          qInfo()<<receiveArray;
          QDateTime current_time = QDateTime::currentDateTime();
          //QString current_date = current_time.toString("yyyy-MM-dd hh:mm:ss");
          QString time = current_time.toString("hh:mm:ss");
          if(setting3->checkState() == Qt::Checked)
          messageBox->insertPlainText(QString(receiveArray.toHex()).toUpper());
          else
          {
          messageBox->insertPlainText(QString(receiveArray));
          if(SaveLog==true)
            {
              QFile file("logsave.txt");
              if (file.open(QIODevice::Append | QIODevice::Text))
              {

                 file.write(receiveArray);
                 file.write("\n");
                 file.flush();
                 file.close();
              }
          }
          if (QString(receiveArray)=="\r")
          messageBox->insertPlainText(time);
          }
          messageBox->moveCursor(QTextCursor::End);

      });

      //clear text
      connect(clearText,&DPushButton::clicked, messageBox, &DTextEdit::clear);
      connect(clearText,&DPushButton::clicked, filemessageBox, &DTextEdit::clear);


      //refresh button
       connect(refreshButton, &DPushButton::clicked, this, [ = ] {
           //serialport list refresh
           for (int index = 10;index >=0; index--) {

               setting1->removeItem(index);

           }

           foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
           {

               setting1->addItem(serialPortInfo.portName());
           }

       });

       //read button 将log文件内容按行发送给已连接串口
        connect(readButton, &DPushButton::clicked, this, [ = ] {

            QFile file("log.txt");
            static bool send_file = true,first_push = true;
             if(send_file==true&&first_push==true)
             {
                 first_push = false;
                 readButton->setText("取消发送");
             }
            else if(send_file==true&&first_push==false)
            {
            readButton->setText("恢复发送");
            send_file=false;
            }
            else
            {
            readButton->setText("取消发送");
            send_file=true;
            }
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                if(send_file==false) return;
                 while (!file.atEnd() && send_file == true)
                 {
                   QByteArray line = file.readLine();
                   int time =sendtime->currentText().toInt();
                   qDebug()<<"本次向串口发送的内容为："<<line;
                   qDebug()<<"本次向串口发送的内容为原始数据："<<QByteArray::fromHex(line);
                   filemessageBox->insertPlainText("\n本次向串口发送的内容为(hex)：");
//                   filemessageBox->insertPlainText(QString(line.toHex()));
                   filemessageBox->insertPlainText(line);
//                   filemessageBox->insertPlainText("\n本次向串口发送的内容为(原始数据)：");
//                   filemessageBox->insertPlainText(QByteArray::fromHex(line));
                   filemessageBox->moveCursor(QTextCursor::End);
                   global_port.write(QByteArray::fromHex(line));
//                   global_port.write("\n");
//                   QElapsedTimer t;
//                   t.start();
//                   while(t.elapsed()<1000);
                   qDebug()<<"time"<<time;
                   QEventLoop loop;
                   QTimer::singleShot(time,&loop,SLOT(quit()));
                   loop.exec();
                 }
//                 readButton->setText("发送结束");
                   file.close();
            }

        });


        //savebutton 保存串口打印日志
          connect(saveButton, &DPushButton::clicked, this, [ = ] {
              if(SaveLog==false)
              {
                SaveLog=true;
                saveButton->setText("取消保存");
              }
              else
              {
                SaveLog=false;
                saveButton->setText("保存日志");
              }

          });


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
