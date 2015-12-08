#ifndef COMPUTE_H
#define COMPUTE_H

#include "MyClass.h"
#include "stdio.h"
#include <math.h>
using namespace std;
//! [0]

class Process
{
public:
    Process();
    ~Process();
	vector<Point_3> order_xy;
	vector<Point_3> order_xz;
	vector<Point_3> order_yz;
	vector<Point_3> PointSet;
	//����͹����
	void ComputeConvex();
	//��ȡ�ļ�����
    bool GetFileContent(string fileName);
protected:
	//�ļ����Ƿ�Ϸ�
    bool ValidFileName(string name);
	//����ǰ�ÿո�
	void EliminatePreSpace(string &str);
    //���ַ�ת����
	template <typename NumType>
    void ConvertString(string &str,NumType &number);
	//Ѱ����С��
	Point_3 FindSmallest(int flag);
	//�����������н�
	long double ComputeAngle(Point_3 start, Point_3 end, Point_3 newend,int flag);
	long double ComputeAngleB(Point_3 start, Point_3 end, Point_3 newend,int flag);
	//������������
	long double Distance(Point_3 start,Point_3 end,int flag);
	void ComputeXYConvex();
	void ComputeXZConvex();	
	void ComputeYZConvex();


private:
	string InName;
};
//! [3]


#endif

