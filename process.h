#ifndef PROCESS_H
#define PROCESS_H

#include "MyClass.h"
#include "stdio.h"
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;
//! [0]

class Process
{
public:
    Process();
    ~Process();
	vector<Point_3> PointSet;
	vector<MyRelation> FaceSet;
	vector< vector<Point_3> > Q;
	vector<Point_3> midQ;
	vector<Point_3> myQ;
	vector<MyCube> Met;
	MyVector *v1_ = new MyVector[3];
	MyVector *v2_ = new MyVector[3];
	MyVector outv3_,outv4_;
	MyVector outv1_,outv2_;
	//读取文件内容
    bool GetFileContent(string fileName);
	void Compute(Process in);
	void Output(string str, vector<Point_3> in);
protected:
	//文件名是否合法
    bool ValidFileName(string name);
	//消除前置空格
	void EliminatePreSpace(string &str);
    //将字符转数字
	template <typename NumType>
    void ConvertString(string &str,NumType &number);
	MyCube OBBMet(vector<Point_3> point, vector<MyRelation> face);
	MyVector ComU(vector<Point_3> point, vector<MyRelation> face);
	bool JacbiCor(double * pMatrix,int nDim, double *pdblVects, double *pdbEigenValues, double dbEps,int nJt);
	MyCube Rotate(MyVector _i1, MyVector _i2, MyVector _j1, MyVector _j2);
	MyVector SurfaceV(MyVector tar, MyVector nor);
private:
	string InName;
};
//! [3]


#endif

