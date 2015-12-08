#define _STDCALL_SUPPORTED
#define _M_IX86
#define GLUT_DISABLE_ATEXIT_HACK

#include "glwidget.h"
#include <GLUT/glut.h>
#include "qevent.h"
#include "stdio.h"
//! [0]

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{
	xRot=0;
	yRot=0;
	zRot=0;
	q.x=0;
	q.y=0;
	q.z=0;
	mywidth = width();
    myheight = height();
    flag_in = false;
	flag_show = false;
    centerX = (int)(0.375*width());
    centerY = height()/2;
    r = centerX<centerY ? centerX:centerY;
	qc=1.0;
	scale=1;
    //qDebug( "my window handle = %d,%d,%d", centerX,centerY,r );
}

GLWidget::~GLWidget()
{
    
}


QSize GLWidget::minimumSizeHint() const
{
    return QSize(800, 600);
}


QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}


void GLWidget::GetFileNameOne(QString filename)
{	
	one.GetFileContent(filename.toStdString());
//	one.ComputeConvex();

	flag_show = true;
    updateGL();
}

void GLWidget::GetFileNameTwo(QString filename)
{	
	two.GetFileContent(filename.toStdString());
//	two.ComputeConvex();

	flag_show = true;
	

	one.Compute(two);
    updateGL();
}

void GLWidget::SetViewPort()
{
	xRot=0;
	yRot=0;
	zRot=0;
	updateGL();
}

void GLWidget::initializeGL()
{
    // 启用阴影平滑
    glShadeModel( GL_SMOOTH );
    // 黑色背景
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
    // 设置深度缓存
    glClearDepth( 1.0 );
     // 启用深度测试
    glEnable( GL_DEPTH_TEST );
    // 所作深度测试的类型
    glDepthFunc( GL_LEQUAL );
    // 告诉系统对透视进行修正
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}


void GLWidget::paintGL()
{
   // 清除屏幕和深度缓存
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    PaintPartLine();
    PaintMainViewport();
    PaintViewportX();
    PaintViewportY();
    PaintViewportZ();
    glFlush(); 
}


void GLWidget::resizeGL(int width, int height)
{
    // 防止窗口大小变为0
    if ( height == 0 )
    {
        height = 1;
    }
    mywidth = width;
    myheight = height;
    centerX = (int)(0.375*width);
    centerY = height/2;
    r = centerX<centerY ? centerX:centerY;
    

}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		if(event->x()<(3*mywidth/4) && event->y()<myheight)
			flag_in = true;
		if(flag_in)
		{
		    int a = event->x()-centerX;
		    int b = event->y()-centerY;
		    int c = a*a+b*b;
		    if(c>=r*r)
		       {
				vet.x = a*r/sqrt(c);
			   vet.y = b*r/sqrt(c);
			   vet.z = 0;
		       }else if(c<r*r)
		       {
			   vet.x = a;
			   vet.y = b;
			   vet.z = sqrt(r*r-c);
		       }
		vet = Normal(vet);  
		//qDebug( "my window handle = %f,%f,%f", vet.x,vet.y,vet.z );
		}		
	}    
}


void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(flag_in)
	{
		MyPoint new_vet;
		MyPoint new_rot;
		float temp;
		double temp1,temp2,temp3;
    		int a = event->x()-centerX;
		int b = event->y()-centerY;
		int c = a*a+b*b;
		if(c>=r*r)
		{
                   new_vet.x = a*r/sqrt(c);
		   new_vet.y = b*r/sqrt(c);
		   new_vet.z = 0;
		}else if(c<r*r)
		{
		   new_vet.x = a;
		   new_vet.y = b;
		   new_vet.z = sqrt(r*r-c);
		}
		new_vet = Normal(new_vet);
		
		temp1 = (new_vet.x-vet.x)*(new_vet.x-vet.x);
		temp2 = (new_vet.y-vet.y)*(new_vet.y-vet.y);
		temp3 = (new_vet.z-vet.z)*(new_vet.z-vet.z);
		temp = sqrt(temp1+temp2+temp3);
		
		
		new_rot.x = vet.y*new_vet.z-new_vet.y*vet.z;
		new_rot.y = vet.z*new_vet.x-new_vet.z*vet.x;
		new_rot.z = vet.x*new_vet.y-new_vet.x*vet.y;
		
		vet = new_vet;

    		if (event->buttons() & Qt::LeftButton) {
			Quaternion(new_rot,temp); 
			updateGL();
   		}
	}
}


void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{

	if(event->button() == Qt::LeftButton)
	{
		flag_in = false;
	}
}
    
void GLWidget::wheelEvent(QWheelEvent *event)
{
	if(event->x()<(3*mywidth/4) && event->y()<myheight)
	{
		scale = scale +  0.05 * event->delta() / 120;
		if(scale<=0)
			scale = 0;
		updateGL();
	}
}

void GLWidget::mouseOperate()
{
	glRotatef(0,0,0,1);
	glRotatef(-40,0,1,0);
	glRotatef(-130,1,0,0);
	glScalef(scale,scale,scale);
	QString text = "Rotation Angle  x:"+(QString::number(-xRot*180/PI,'f',4)).rightJustified(9,' ')+
		"  y:"+(QString::number(yRot*180/PI,'f',4)).rightJustified(9,' ')+
		"  z:"+(QString::number(-zRot*180/PI,'f',4)).rightJustified(9,' ')+
		"  scale:"+(QString::number(scale,'f',2)).rightJustified(5,' ');
	emit RotationChangedText(text);
	
	
}
void GLWidget::MyPaint()
{
	mouseOperate();
	if(flag_show)
	{
		glColor3f(0,0,1);
		glBegin(GL_POINTS);
		for(unsigned long i=0; i<two.PointSet.size();i++)
		{
			glVertex3f(two.PointSet.at(i).x,two.PointSet.at(i).y,two.PointSet.at(i).z);
		}
		glEnd();
		glColor3f(1,0,0);
		glBegin(GL_POINTS);
		for(unsigned long i=0; i<one.PointSet.size();i++)
		{
			glVertex3f(one.PointSet.at(i).x,one.PointSet.at(i).y,one.PointSet.at(i).z);
		}
		glEnd();
		glBegin(GL_LINES);

/*		glColor3f(0.0,0.0,1.0);
//		glVertex3f(one.v1_[0].a*100, one.v1_[0].b*100,one.v1_[0].c*100);
//		glVertex3f(0,0,0);
		glColor3f(0.0,0.0,1.0);
		glVertex3f(one.v2_[0].a*100, one.v2_[0].b*100,one.v2_[0].c*100);
		glVertex3f(0,0,0);

		glColor3f(0.0,1.0,0.0);
//		glVertex3f(one.v1_[1].a*100, one.v1_[1].b*100,one.v1_[1].c*100);
//		glVertex3f(0,0,0);
		glColor3f(0.0,1.0,0.0);
		glVertex3f(one.v2_[1].a*100, one.v2_[1].b*100,one.v2_[1].c*100);
		glVertex3f(0,0,0);

		glColor3f(1.0,0.0,0.0);
//		glVertex3f(one.v1_[2].a*100, one.v1_[2].b*100,one.v1_[2].c*100);
//		glVertex3f(0,0,0);
		glColor3f(1.0,0.0,0.0);
		glVertex3f(one.v2_[2].a*100, one.v2_[2].b*100,one.v2_[2].c*100);
		glVertex3f(0,0,0);


		glColor3f(1.0,0.0,1.0);
		glVertex3f(one.outv1_.a, one.outv1_.b,one.outv1_.c);
		glVertex3f(0,0,0);
		glColor3f(1.0,0.0,1.0);
		glVertex3f(one.outv3_.a, one.outv3_.b,one.outv3_.c);
		glVertex3f(0,0,0);

		glColor3f(0.0,1.0,1.0);
		glVertex3f(one.outv2_.a, one.outv2_.b,one.outv2_.c);
		glVertex3f(0,0,0);
		glColor3f(0.0,1.0,1.0);
		glVertex3f(one.outv4_.a, one.outv4_.b,one.outv4_.c);
		glVertex3f(0,0,0);

/*		glColor3f(1.0,1.0,0.0);
		glVertex3f(one.v1_[2].a*100, one.v1_[2].b*100,one.v1_[2].c*100);
		glVertex3f(0,0,0);
		glColor3f(1.0,0.0,0.0);
		glVertex3f(one.v2_[2].a*100, one.v2_[2].b*100,one.v2_[2].c*100);
		glVertex3f(0,0,0);*/

		glEnd();


	}	 
}

void GLWidget::PaintMainViewport()
{
    //设置主视口中物体的颜色
    glColor3f(1,0,0);
    //承接上一视口的观察矩阵  
    glLoadIdentity();
    //设置观察点在Z轴的正方向  
    gluLookAt(0,0,100,0,0,0,0,1,0);
    //设置投影矩阵  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //设置投影区域，数字选择参照红书，第二项比例为左侧主视口的比例  
    //gluPerspective(60, (GLfloat)mywidth*0.75/(GLfloat)myheight,0.1,10.0);  
    glOrtho(-200.0,200.0,-200.0,200.0,-300.0,300.0);
	//glOrtho(-100,200,-100,200,-100,100);
	glMatrixMode(GL_MODELVIEW);  
    //设置视口为左侧主视口  
    glViewport(0, 0, 3*mywidth/4, myheight);  
    //鼠标控制交互，保存上一时刻与下一时刻的位置
    glPushMatrix();
    //绘制实物
    MyPaint();
    glPopMatrix();
}

void GLWidget::PaintViewportX()
{
    //设置右下视口中物体的颜色
    glColor3f(1,0,0);
    //承接上一视口的观察矩阵  
    glLoadIdentity();
    //设置观察点在X轴的正方向  
    gluLookAt(5,0,0,0,0,0,0,0,1);
    //设置投影矩阵  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //设置投影区域，数字选择参照红书，第二项比例为右下视口的比例  
    gluPerspective(60, (GLfloat)mywidth*0.75/(GLfloat)myheight,0.1,10.0);  
    glMatrixMode(GL_MODELVIEW);  
    //设置视口为右下视口，前两个参数是起点位置，后两个参数是宽和高  
    glViewport(3*mywidth/4, 0, mywidth/4, myheight/3);  
    //鼠标控制交互，保存上一时刻与下一时刻的位置
    glPushMatrix();
    //绘制实物
	MyPaint();
    glPopMatrix();
}
void GLWidget::PaintViewportY()
{
    //设置右中视口中物体的颜色
    glColor3f(1,0,0);
    //承接上一视口的观察矩阵  
    glLoadIdentity();
    //设置观察点在Y轴的正方向  
    gluLookAt(0,5,0,0,0,0,1,0,0);
    //设置投影矩阵  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //设置投影区域，数字选择参照红书，第二项比例为右中视口的比例  
    gluPerspective(60, (GLfloat)mywidth*0.75/(GLfloat)myheight,0.1,10.0);      
    glMatrixMode(GL_MODELVIEW);  
    //设置视口为右中视口  
    glViewport(3*mywidth/4, myheight/3, mywidth/4, myheight/3);  
    //鼠标控制交互，保存上一时刻与下一时刻的位置
    glPushMatrix();
    //绘制实物
    MyPaint();
    glPopMatrix();
}
void GLWidget::PaintViewportZ()
{
    //设置右上视口中物体的颜色
    glColor3f(1,0,0);
    //承接上一视口的观察矩阵  
    glLoadIdentity();
    //设置观察点在Z轴的正方向  
    gluLookAt(0,0,5,0,0,0,0,1,0);
    //设置投影矩阵  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //设置投影区域，数字选择参照红书，第二项比例为右上视口的比例  
    gluPerspective(60, (GLfloat)mywidth*0.75/(GLfloat)myheight,0.1,10.0);  
    glMatrixMode(GL_MODELVIEW);  
    //设置视口为右上视口  
    glViewport(3*mywidth/4, 2*myheight/3, mywidth/4, myheight/3);  
    //鼠标控制交互，保存上一时刻与下一时刻的位置
    glPushMatrix();
    //绘制实物
    MyPaint();
    glPopMatrix();
}
void GLWidget::PaintPartLine()
{
    //设置绘制分割线的颜色为白色	
    glColor3f(1,1,1);
    //承接另外一视口绘制的观察矩阵
    glLoadIdentity();
    //选择投影矩阵   
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //将整个视口截取为按照长宽的大小
    gluOrtho2D( 0.0, mywidth, 0.0, myheight );
    // 选择模型观察矩阵，为下一视口绘制留下接口
    glMatrixMode( GL_MODELVIEW );
    
    //绘制四个视口的分割线，一竖两横
    glViewport( 0, 0, mywidth, myheight);
    glBegin(GL_LINES);
    glVertex2f(0.75*mywidth,0.0);
    glVertex2f(0.75*mywidth,myheight);
    glVertex2f(0.75*mywidth,myheight/3);
    glVertex2f(mywidth,myheight/3);
    glVertex2f(0.75*mywidth,2*myheight/3);
    glVertex2f(mywidth,2*myheight/3);
    glEnd();
    //绘制右下坐标系
    glBegin(GL_LINES);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/60,myheight/60);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/24,myheight/12);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/12,myheight/24);
    glEnd();
    glRasterPos2f(0.75*mywidth+3,3);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');
    glRasterPos2f(0.75*mywidth+myheight/24-4,myheight/12+4);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'z');
    glRasterPos2f(0.75*mywidth+myheight/12+1,myheight/24-4);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'y');
    //绘制右中坐标系
    glTranslatef(0.0,myheight/3,0.0);
    glBegin(GL_LINES);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/60,myheight/60);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/24,myheight/12);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/12,myheight/24);
    glEnd();
    glRasterPos2f(0.75*mywidth+3,3);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'y');
    glRasterPos2f(0.75*mywidth+myheight/24-4,myheight/12+4);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');
    glRasterPos2f(0.75*mywidth+myheight/12+1,myheight/24-4);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'z');
    //绘制右上坐标系
    glTranslatef(0.0,myheight/3,0.0);
    glBegin(GL_LINES);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/60,myheight/60);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/24,myheight/12);
    glVertex2f(0.75*mywidth+myheight/24,myheight/24);
    glVertex2f(0.75*mywidth+myheight/12,myheight/24);
    glEnd();
    glRasterPos2f(0.75*mywidth+3,3);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'z');
    glRasterPos2f(0.75*mywidth+myheight/24-4,myheight/12+4);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'y');
    glRasterPos2f(0.75*mywidth+myheight/12+1,myheight/24-4);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');
}

void GLWidget::Quaternion(MyPoint v,float a)
{
	//float norm;
	MyPoint u;
	float b,t;
	u = q;
	b = qc;
	t = cos(a/2);
        v = Normal(v);	
	
	v.x = v.x*sin(a/2);
	v.y = v.y*sin(a/2);
	v.z = v.z*sin(a/2);

	qc = b*t-v.x*u.x-v.y*u.y-v.z*u.z;
	q.x = t*u.x+b*v.x-u.y*v.z+v.y*u.z;
	q.y = t*u.y+b*v.y-u.z*v.x+v.z*u.x;
	q.z = t*u.z+b*v.z-u.x*v.y+v.x*u.y;

	xRot = atan2(2*(qc*q.x+q.y*q.z),1-2*(q.x*q.x+q.y*q.y));
	yRot = asin(2*(qc*q.y-q.x*q.z));
	zRot = atan2(2*(qc*q.z+q.x*q.y),1-2*(q.y*q.y+q.z*q.z));


}

MyPoint GLWidget::Normal(MyPoint in)
{
	float norm;
	MyPoint v;
	v = in;
	norm = sqrt((v.x)*(v.x)+(v.y)*(v.y)+(v.z)*(v.z));
	if(norm>0)
	{
		v.x = v.x/norm;
		v.y = v.y/norm;
		v.z = v.z/norm;
	}
	return v;
}


