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
    //�����źţ���ת�Ƕ��źţ���״̬������
    void RotationChangedText(QString text);//! [1]


//! [2]

protected:
    //������Ⱦ����
    void initializeGL();
    //���ƴ���
    void paintGL();
    //��Ӧ���ڵĴ�С�仯
    void resizeGL( int width, int height );
    //����϶���ת��
    void mouseOperate();
    //����Ŀ������
    void MyPaint();
    //��굥���¼�
    void mousePressEvent(QMouseEvent *event);
    //����ƶ��¼�
    void mouseMoveEvent(QMouseEvent *event);
    //����ͷ��¼�
    void mouseReleaseEvent(QMouseEvent *event);
    //�������¼�
    void wheelEvent(QWheelEvent *event);
//! [2]


//! [3]

private:
    //��xyz�����ת����
    float xRot;
    float yRot;
    float zRot;
    //��������
    float scale;
    //��������ͷָ���
    void PaintPartLine();
    //�������ӿ�
    void PaintMainViewport();
    //�����Ҳ������������ӿ�
    void PaintViewportX();
    void PaintViewportY();
    void PaintViewportZ();
	//�������ӿڵĿ�͸�
    int mywidth;
    int myheight;
    //�ж�����Ƿ�����������ӿ�
    bool flag_in;
    //����ӿڵ�����λ��
    int centerX;
    int centerY;
    //ģ����뾶
    int r;
    //��¼��ת����
    MyPoint vet;
    //��Ԫ������ת��
    MyPoint q;
    float qc;
    //��ת���ۼӣ���Ԫ���ĳ˷�����
    void Quaternion(MyPoint v,float a);
    //������λ��
    MyPoint Normal(MyPoint in);
	Process one;
	Process two;
	//�ж��Ƿ���ʾ
    bool flag_show;
};
//! [3]


#endif

