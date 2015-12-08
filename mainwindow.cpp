#include "mainwindow.h"
#include <QStatusBar>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    glWidget = new GLWidget();
    fullscreen = true;
	setGeometry(100,100,800,600);
    setWindowTitle(tr("Common View Framework"));
    setCentralWidget(glWidget);
    createActions();
    createMenus();
    QLabel *rototionangle = new QLabel( tr("Rotation Angle") );
    rototionangle->setMinimumSize( rototionangle->sizeHint() );
    QStatusBar *statusBar = this->statusBar();
    statusBar->addWidget( rototionangle );
    statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    connect(glWidget, SIGNAL(RotationChangedText(QString)), rototionangle,
		    SLOT(setText(QString)));
    connect(glWidget,SIGNAL(RecordParameter(float *)),this,SLOT(ResetTranslate(float *)));
	connect(this,SIGNAL(SendFileNameOne(QString)),glWidget,SLOT(GetFileNameOne(QString)));
	connect(this,SIGNAL(SendFileNameTwo(QString)),glWidget,SLOT(GetFileNameTwo(QString)));
}
MainWindow::~MainWindow()
{

}
void MainWindow::closeEvent(QCloseEvent *e)
{
//	if(odialog)
	{
//		odialog->accept();
	}
}
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch ( e->key() )
      {
      case Qt::Key_F2:
        fullscreen = !fullscreen;
        if ( fullscreen )
        {
          showFullScreen();
        }
        else
        {
          showNormal();
        }
      glWidget->updateGL();
        break;
      case Qt::Key_Escape:
       close();
        break;
     }
}
void MainWindow::createActions()
{
	Open = new QAction(tr("&OpenPointCloud"), this);
	Open->setShortcut(tr("Ctrl+P"));
	Open->setStatusTip(tr("Open a point cloud file"));
	connect(Open, SIGNAL(triggered()), this, SLOT(OpenPointFileOne()));
	New = new QAction(tr("&OpenCADPoint"), this);
	New->setShortcut(tr("Ctrl+C"));
	New->setStatusTip(tr("Open a CAD points file"));
	connect(New, SIGNAL(triggered()), this, SLOT(OpenPointFileTwo()));
	ZView = new QAction(tr("&ZView"),this);
	ZView->setShortcut(tr("Ctrl+Z"));
	ZView->setStatusTip(tr("View from Z axis"));
	connect(ZView,SIGNAL(triggered()),glWidget,SLOT(SetViewPort()));
}
void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&Files"));
	fileMenu->addAction(New);
	fileMenu->addAction(Open);
	//fileMenu->addAction(Save);
	//fileMenu->addAction(Close);
	fileMenu->setStatusTip(tr("Files"));
	fileMenu = menuBar()->addMenu(tr("&Operate"));
	fileMenu->addAction(ZView);
	fileMenu->setStatusTip(tr("Operations"));
}

void MainWindow::OriginalSettings()
{
}

void MainWindow::RollSettings()
{}
void MainWindow::OpenPointFileOne()
{
QFileDialog* fd = new QFileDialog(this);//创建对话框
fd->setWindowTitle(tr("Open Image")); 
fd->setDirectory("."); 
fd->resize(240,320);    //设置显示的大小
fd->setFilter( "Allfile(*.*);;mp3file(*.mp3);;wmafile(*.wma);;wavefile(*.wav)"); //设置文件过滤器
fd->setViewMode(QFileDialog::List);  //设置浏览模式，有 列表（list） 模式和 详细信息（detail）两种方式
fd->setFileMode( QFileDialog::ExistingFile ); 
if ( fd->exec() == QDialog::Accepted )   //如果成功的执行
{
filename = fd->selectedFiles()[0];      //返回文件列表的名称
emit SendFileNameOne(filename);
}
else
fd->close();
}
void MainWindow::OpenPointFileTwo()
{
QFileDialog* fd = new QFileDialog(this);//创建对话框
fd->setWindowTitle(tr("Open Image")); 
fd->setDirectory("."); 
fd->resize(240,320);    //设置显示的大小
fd->setFilter( "Allfile(*.*);;mp3file(*.mp3);;wmafile(*.wma);;wavefile(*.wav)"); //设置文件过滤器
fd->setViewMode(QFileDialog::List);  //设置浏览模式，有 列表（list） 模式和 详细信息（detail）两种方式
fd->setFileMode( QFileDialog::ExistingFile ); 
if ( fd->exec() == QDialog::Accepted )   //如果成功的执行
{
filename = fd->selectedFiles()[0];      //返回文件列表的名称
emit SendFileNameTwo(filename);
}
else
fd->close();
}

void MainWindow::ExtendSettings()
{}

void MainWindow::ResetTranslate(float *para)
{}


