#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtGui>
#include <QtOpenGL>
#include "process.h"
//! [0]

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
//! [0]


//! [1]

public slots:
	void GetFileNameOne(QString filename);
	void GetFileNameTwo(QString filename);
    void SetViewPort();
signals:
    //发出信号，旋转角度信号，被状态栏接收
    void RotationChangedText(QString text);//! [1]


//! [2]

protected:
    //设置渲染环境
    void initializeGL();
    //绘制窗口
    void paintGL();
    //响应窗口的大小变化
    void resizeGL( int width, int height );
    //鼠标拖动旋转量
    void mouseOperate();
    //绘制目标主体
    void MyPaint();
    //鼠标单击事件
    void mousePressEvent(QMouseEvent *event);
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event);
    //鼠标滚轮事件
    void wheelEvent(QWheelEvent *event);
//! [2]


//! [3]

private:
    //绕xyz轴的旋转弧度
    float xRot;
    float yRot;
    float zRot;
    //放缩比例
    float scale;
    //绘制坐标和分割线
    void PaintPartLine();
    //绘制主视口
    void PaintMainViewport();
    //绘制右侧上中下三个视口
    void PaintViewportX();
    void PaintViewportY();
    void PaintViewportZ();
	//定义总视口的宽和高
    int mywidth;
    int myheight;
    //判断鼠标是否点击在了左侧视口
    bool flag_in;
    //左侧视口的中心位置
    int centerX;
    int centerY;
    //模拟球半径
    int r;
    //记录旋转向量
    MyPoint vet;
    //四元数和旋转量
    MyPoint q;
    float qc;
    //旋转的累加，四元数的乘法运算
    void Quaternion(MyPoint v,float a);
    //向量单位化
    MyPoint Normal(MyPoint in);
	Process one;
	Process two;
	//判断是否显示
    bool flag_show;
};
//! [3]


#endif

