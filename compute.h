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
	//计算凸包点
	void ComputeConvex();
	//读取文件内容
    bool GetFileContent(string fileName);
protected:
	//文件名是否合法
    bool ValidFileName(string name);
	//消除前置空格
	void EliminatePreSpace(string &str);
    //将字符转数字
	template <typename NumType>
    void ConvertString(string &str,NumType &number);
	//寻找最小点
	Point_3 FindSmallest(int flag);
	//计算两向量夹脚
	long double ComputeAngle(Point_3 start, Point_3 end, Point_3 newend,int flag);
	long double ComputeAngleB(Point_3 start, Point_3 end, Point_3 newend,int flag);
	//计算两点间距离
	long double Distance(Point_3 start,Point_3 end,int flag);
	void ComputeXYConvex();
	void ComputeXZConvex();	
	void ComputeYZConvex();


private:
	string InName;
};
//! [3]


#endif

