#ifndef MYCLASS_H
#define MYCLASS_H
#include <QVector>
#define PI 3.1415926
#include <math.h>

class Point_3
{
public:
	Point_3(void){}
	Point_3(long double X, long double Y, long double Z, int num)
	{
    	x = X;
    	y = Y;
    	z = Z;
    	count = num;
	}

	~Point_3(void){}

public:
	Point_3 operator=(Point_3 p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		count = p.count;
		return *this;
	}

	Point_3 operator+(const Point_3 p)
	{
		Point_3 newPoint;
		newPoint.x = this->x + p.x;
		newPoint.y = this->y + p.y;
		newPoint.z = this->z + p.z;
		return newPoint;
	}
	bool operator==(const Point_3 p)
		{
			if(x == p.x && y == p.y && z == p.z && count == p.count)
				return true;
			return false;
		}
	bool operator!=(const Point_3 p)
		{
			if(x != p.x || y != p.y ||z != p.z || count != p.count)
				return true;
			return false;
		}

	Point_3 operator-(const Point_3 p)
		{
			Point_3 newPoint;
			newPoint.x = x - p.x;
			newPoint.y = y - p.y;
			newPoint.z = z - p.z;
			return newPoint;
		}
	float dis()
	{
		return sqrt(x*x+y*y+z*z);
	}

public:
	//对应的点在该图形中的位置
	int count;
	//x,y,z坐标
	long double x;
	long double y;
	long double z;
	
};

class MyRelation
{
	public:
	MyRelation(void){}
	MyRelation(int X, int Y, int Z)
	{
    	a = X;
    	b = Y;
    	c = Z;
	}

	~MyRelation(void){}

	public:
		int a;
		int b;
		int c;
};

class MyVector
{
public:
	double a;
	double b;
	double c;
	bool operator ==(MyVector s){
		if ((int)((s.a-a)*10000000)==0&&(int)((s.b-b)*10000000)==0&&(int)((s.c-c)*10000000)==0)
		{
			return true;
		}
		return false;
	}
	MyVector plus(MyVector s)
	{
		MyVector vet;
		vet.a = b*s.c-s.b*c;
		vet.b = c*s.a-s.c*a;
		vet.c = a*s.b-s.a*b;
		return vet;
	}
	void unit()
	{
		float nor_;
		nor_ = this->mod();
		a = a/nor_;
		b = b/nor_;
		c = c/nor_;
	}
	float dot(MyVector s)
	{
		return s.a*a+s.b*b+s.c*c;
	}
	float mod()
	{
		return sqrt(a*a+b*b+c*c);
	}	
};

class MyPoint
{
public:
	float x;
	float y;
	float z;
	//用于比较两个点是否相同;
	bool operator ==(MyPoint s){
		if ((int)((s.x-x)*10000000)==0&&(int)((s.y-y)*10000000)==0&&(int)((s.z-z)*10000000)==0)
		{
			return true;
		}
		return false;
	}
	bool operator !=(MyPoint s){
		if ((int)((s.x-x)*10000000)!=0||(int)((s.y-y)*10000000)!=0||(int)((s.z-z)*10000000)!=0)
		{
			return true;
		}
		return false;
	}
	float dis(MyPoint s)
	{
		return sqrt((s.x-x)*(s.x-x)+(s.y-y)*(s.y-y)+(s.z-z)*(s.z-z));
	}
       	MyVector vet(MyPoint s)
	{
		MyVector vet;
		vet.a = s.x-x;
		vet.b = s.y-y;
		vet.c = s.z-z;
		return vet;
	}
	MyPoint mus(MyPoint s)
	{
		MyPoint v;
		v.x = x-s.x;
		v.y = y-s.y;
		v.z = z-s.z;
		return v;
	}
	MyPoint add(MyPoint s)
	{
		MyPoint v;
		v.x = x+s.x;
		v.y = y+s.y;
		v.z = z+s.z;
		return v;
	}
	MyPoint toPoint_3(Point_3 s)
	{
		MyPoint v;
		v.x = s.x;
		v.y = s.y;
		v.z = s.z;
		return v;
	}
};



class MySide
{
public:
	MyPoint Mybegin;
	MyPoint Myend;
	bool operator ==(MySide s){
		if (s.Mybegin==Mybegin &&s.Myend==Myend)
		{
			return true;
		}
		return false;
	}
	bool operator !=(MySide s){
		if (s.Mybegin==Myend &&s.Myend==Mybegin)
		{
			return true;
		}
		return false;
	}
};

//面的定义，存三条边，加一条向量;
class MyFace
{
public:
	QVector <MySide> side;
	//Myvector v;
	int type;
};

class MyCube
{
	public:
	MyCube(void){}
	MyCube(long double A, long double B, long double C,long double D, long double E, long double F,long double G, long double H, long double I)
	{
    	a = A;
		b = B;
		c = C;
		d = D;
		e = E;
		f = F;
		g = G;
		h = H;
		i = I;
	}

	~MyCube(void){}
	public:
		double a,b,c,d,e,f,g,h,i;
};
#endif


