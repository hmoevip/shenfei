#include "process.h"
#include <QString>
#include <QMessageBox>//! [0]
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <map>
//using namespace std;
#include <QDebug>
#include <sys/time.h>

struct timeval tpstart,tpend;
float timeuse;


Process::Process()
{
}

Process::~Process()
{
    
}

bool Process::ValidFileName(string name)
{
	string last = "";
	int k = name.length();
	for(int i = k-3; i < k; i ++)
		last += name[i];
	if(last == "off")
		return true;
	else
		return false;
}

void Process::EliminatePreSpace(string &str)
{
	unsigned int i = 0;
	while (i < str.size())
	{
		if(str[i] == ' ' || str[i] == '\t')
		{
			str = str.substr(i + 1, str.size());
			i = 0; 
			continue;
		}
		else
			break;
	}
}

template <typename NumType>

void Process::ConvertString(string &str, NumType &number)
{
	EliminatePreSpace(str); //调用消除前置空格函数
	unsigned int i_len = 0;
	while (i_len < str.size())
	{
		if(str[i_len] == ' ' || str[i_len] == '\t')
			break;
		else
			i_len ++;
	}
	string num = "";
	for(unsigned int j = 0; j < i_len; j ++)
	{
		if(str[j]!=' ')
			num += str[j];
		else
			break;
	}
	if(i_len + 1 < str.size())
		str = str.substr(i_len+1 , str.size());
	const char *charnum = num.data();
	number = 0e-32;
	number = atof(charnum);
}

bool Process::GetFileContent(string fileName)
{
	long double sum_x;
	long double sum_y;
	long double sum_z;
	MyVector vet_;
	int size_;
	sum_x=0;
	sum_y=0;
	sum_z=0;
	PointSet.clear();
	FaceSet.clear();
	vector<Point_3> TempSet;
	TempSet.clear();
	/*打开文件并且开始读取*/
	ifstream infile(fileName.c_str(), ios::in);
	if(!ValidFileName(fileName)) //判断是否合法
	{
		cout<<"Filename is not .off file!"<<endl;
		return false;
	}
	if(!infile)
	{
		cout<<"Could not open it!"<<endl;
		return false;
	}
	else//文件打开正确
	{
		string getString="";
		int i_line = 0;
		int first = 0;
		int vertices = 0, faces = 0;
		int i_vertex = 0;
		int i_face = 0;

		/*解析文件*/
		while (getline(infile, getString))
		{
			getString.erase(getString.end()-1);
			if(i_line == 0 && (getString == "OFF" || getString == "OFF "))
			{
				i_line ++;
				getString = "";
				continue;
			}
			else if(i_line == 0 && (getString != "OFF"|| getString != "OFF "))
			{
				cout<<"Not a valid off file!"<<endl;
				break;
			}
			if(getString!= "")
			{
				if(getString[0] == '#' || getString == " ")
				{
					i_line ++; 
					getString = "";
					continue;
				}
				else
				{
					if (first == 0)
					{
						ConvertString(getString, vertices);
						ConvertString(getString, faces);
						cout<<"Vertices:"<<vertices<<"\tFaces:"<<faces<<endl;
						first = 1;
						getString = "";
					}
					else
					{
						//处理点,获取里面的点
						if(i_vertex < vertices)
						{
						    long double x =0e-32,y=0e-32,z=0e-32;
						    ConvertString(getString, x);
						    ConvertString(getString, y);
						    ConvertString(getString, z);
                            //Point_3为点类 点类填充点对象p
						    Point_3 temp(x,y,z,i_vertex);
							sum_x += x;
							sum_y += y;
							sum_z += z;
                            PointSet.push_back(temp);
							i_vertex ++;
							getString = "";
							continue;
						}
						//处理面，把三角面的关联点存起来
						if(i_vertex == vertices && i_face < faces)
						{
							int n=0,a=0,b=0,c=0;
							ConvertString(getString,n);
							ConvertString(getString,a);
							ConvertString(getString,b);
							ConvertString(getString,c);
							MyRelation mtemp(a,b,c);
							FaceSet.push_back(mtemp);
							++ i_face;
							getString = "";
							continue;
						}						
					}
				}
			}
			i_line ++;
		}
	}
	infile.close();
	size_ = PointSet.size();
	sum_x /= size_;
	sum_y /= size_;
	sum_z /= size_;
	if(size_ > 200000)
	{
		for(int i=0;i<size_;i=i+150)
		{
			TempSet.push_back(PointSet.at(i));
		}
		PointSet.clear();
		PointSet = TempSet;
	}
	//去除杂质面的干扰
/*	for(unsigned long i=0;i<FaceSet.size();++i)
	{
		if(FaceSet.at(i).a >= size_ || FaceSet.at(i).b >= size_ || FaceSet.at(i).c >= size_)
		{
			FaceSet.erase(FaceSet.begin()+i);
			i--;
		}
	}
	vet_ = ComU(PointSet,FaceSet);*/
	for(unsigned long i=0;i<PointSet.size();i++)
	{
		PointSet.at(i).x -= sum_x;//vet_.a;
		PointSet.at(i).y -= sum_y;//vet_.b;
		PointSet.at(i).z -= sum_z;//vet_.c;
	}
	cout<<"Reading data is completed!...."<<endl;
	return true;
}

void Process::Compute(Process in)
{
	MyCube M;
	gettimeofday(&tpstart,NULL);

	M = OBBMet(PointSet,FaceSet);
	double *A = new double[9];
	double *V = new double[9];
	double *L = new double[3];
	A[0] = M.a;
	A[1] = M.b;
	A[2] = M.c;

	A[3] = M.d;
	A[4] = M.e;
	A[5] = M.f;

	A[6] = M.g;
	A[7] = M.h;
	A[8] = M.i;

    for(int i=0;i<9;i++)
        V[i] = 1;
	for(int i=0;i<3;i++)
        L[i] = 1;

	if(JacbiCor(A, 3, V, L, 10, 1))		
/*		cout<<L[0]<<" "<<L[1]<<" "<<L[2]<<endl;

	cout<<V[0]<<" "<<V[1]<<" "<<V[2]<<endl;
	cout<<V[3]<<" "<<V[4]<<" "<<V[5]<<endl;
	cout<<V[6]<<" "<<V[7]<<" "<<V[8]<<endl;*/
	v1_[0].a = V[0];
	v1_[0].b = V[3];
	v1_[0].c = V[6];

	v1_[1].a = V[1];
	v1_[1].b = V[4];
	v1_[1].c = V[7];

	v1_[2].a = V[2];
	v1_[2].b = V[5];
	v1_[2].c = V[8];

	
	float intmp1_,intmp2_,abs;
	float inang_;
	MyVector inv_;
	intmp1_ = 0;
	intmp2_ = 0;
	for(int i=0; i<PointSet.size();++i)
	{
		inv_.a = PointSet.at(i).x;
		inv_.b = PointSet.at(i).y;
		inv_.c = PointSet.at(i).z;
		inang_ = fabs(inv_.dot(v1_[1]));
//		inv_.a -= v1_[1].a*inang_;
//		inv_.b -= v1_[1].b*inang_;
//		inv_.c -= v1_[1].c*inang_;
//		abs = inv_.mod();
		if(intmp1_ < inang_)
		{
			intmp1_ = inang_;
			outv1_.a = inv_.dot(v1_[1])*v1_[1].a;
			outv1_.b = inv_.dot(v1_[1])*v1_[1].b;
			outv1_.c = inv_.dot(v1_[1])*v1_[1].c;
		}
		inv_.a = PointSet.at(i).x;
		inv_.b = PointSet.at(i).y;
		inv_.c = PointSet.at(i).z;
		inang_ = fabs(inv_.dot(v1_[2]));
//		inv_.a -= v1_[2].a*inang_;
//		inv_.b -= v1_[2].b*inang_;
//		inv_.c -= v1_[2].c*inang_;
//		abs = inv_.mod();
		if(intmp2_ < inang_)
		{
			intmp2_ = inang_;
			outv2_.a = inv_.dot(v1_[2])*v1_[2].a;
			outv2_.b = inv_.dot(v1_[2])*v1_[2].b;
			outv2_.c = inv_.dot(v1_[2])*v1_[2].c;
		}

	}

	M = OBBMet(in.PointSet,in.FaceSet);
	A[0] = M.a;
	A[1] = M.b;
	A[2] = M.c;

	A[3] = M.d;
	A[4] = M.e;
	A[5] = M.f;

	A[6] = M.g;
	A[7] = M.h;
	A[8] = M.i;

	if(JacbiCor(A, 3, V, L, 10, 1))		
/*		cout<<L[0]<<" "<<L[1]<<" "<<L[2]<<endl;

	cout<<V[0]<<" "<<V[1]<<" "<<V[2]<<endl;
	cout<<V[3]<<" "<<V[4]<<" "<<V[5]<<endl;
	cout<<V[6]<<" "<<V[7]<<" "<<V[8]<<endl;*/
	v2_[0].a = V[0];
	v2_[0].b = V[3];
	v2_[0].c = V[6];

	v2_[1].a = V[1];
	v2_[1].b = V[4];
	v2_[1].c = V[7];

	v2_[2].a = V[2];
	v2_[2].b = V[5];
	v2_[2].c = V[8];

/*	for(int i=0;i<3;++i)
	{
		x = v2_[i].a;
		y = v2_[i].b;
		z = v2_[i].c;
		v2_[i].a = M.a*x+M.d*y+M.g*z;//M.a*x + M.b*y + M.c*z;
		v2_[i].b = M.b*x+M.e*y+M.h*z;//M.d*x + M.e*y + M.f*z;
		v2_[i].c = M.c*x+M.f*y+M.i*z;
	}*/

//	float intmp1_,intmp2_,abs;
//	float inang_;
	
	intmp1_ = 0;
	intmp2_ = 0;
	for(int i=0; i<in.PointSet.size();++i)
	{
		inv_.a = in.PointSet.at(i).x;
		inv_.b = in.PointSet.at(i).y;
		inv_.c = in.PointSet.at(i).z;
		inang_ = fabs(inv_.dot(v2_[1]));
//		inv_.a -= v2_[1].a*inang_;
//		inv_.b -= v2_[1].b*inang_;
//		inv_.c -= v2_[1].c*inang_;
//		abs = inv_.mod();
		if(intmp1_ < inang_)
		{
			intmp1_ = inang_;
			outv3_.a = inv_.dot(v2_[1])*v2_[1].a;
			outv3_.b = inv_.dot(v2_[1])*v2_[1].b;
			outv3_.c = inv_.dot(v2_[1])*v2_[1].c;
		}
		inv_.a = in.PointSet.at(i).x;
		inv_.b = in.PointSet.at(i).y;
		inv_.c = in.PointSet.at(i).z;
		inang_ = fabs(inv_.dot(v2_[2]));
//		inv_.a -= v2_[2].a*inang_;
//		inv_.b -= v2_[2].b*inang_;
//		inv_.c -= v2_[2].c*inang_;
//		abs = inv_.mod();
		if(intmp2_ < inang_)
		{
			intmp2_ = inang_;
			outv4_.a = inv_.dot(v2_[2])*v2_[2].a;
			outv4_.b = inv_.dot(v2_[2])*v2_[2].b;
			outv4_.c = inv_.dot(v2_[2])*v2_[2].c;
		}

	}
//	cout<<v2_[1].a<<" "<<v2_[1].b<<" "<<v2_[1].c<<endl;
//	cout<<v2_[2].a<<" "<<v2_[2].b<<" "<<v2_[2].c<<endl;
//	cout<<v1_[1].a<<" "<<v1_[1].b<<" "<<v1_[1].c<<endl;
//	cout<<v1_[2].a<<" "<<v1_[2].b<<" "<<v1_[2].c<<endl;
	cout<<outv1_.a<<" "<<outv1_.b<<" "<<outv1_.c<<endl;
	cout<<outv2_.a<<" "<<outv2_.b<<" "<<outv2_.c<<endl;
	cout<<outv3_.a<<" "<<outv3_.b<<" "<<outv3_.c<<endl;
	cout<<outv4_.a<<" "<<outv4_.b<<" "<<outv4_.c<<endl;


//	M = Rotate(v1_[1],v1_[2],v2_[1],v2_[2]);


	M = Rotate(outv1_,outv2_,outv3_,outv4_);

//gettimeofday(&tpend,NULL);
//timeuse=(1000000*(tpend.tv_sec-tpstart.tv_sec) + tpend.tv_usec-tpstart.tv_usec)/1000000.0;

//cout<<timeuse<<"s";

	float x,y,z;

	Point_3 temp_;
	ofstream outfile("./after/result.off");
	if(!outfile)
	{
		cout<<"can not creat the file"<<endl;
		//break;
	}else{
		cout<<"test.off is writting."<<endl;
		outfile<<"OFF "<<endl;
		outfile<<in.PointSet.size()<<" "<<in.PointSet.size()<<endl;
		for(unsigned long j=0; j<in.PointSet.size(); j++)
		{
		x = in.PointSet.at(j).x;
		y = in.PointSet.at(j).y;
		z = in.PointSet.at(j).z;
		temp_.x = M.a*x+M.d*y+M.g*z ;//M.a*x + M.b*y + M.c*z;
        temp_.y = M.b*x+M.e*y+M.h*z ;//M.d*x + M.e*y + M.f*z;
        temp_.z = M.c*x+M.f*y+M.i*z ;//M.g*x + M.h*y + M.i*z;
		outfile<<temp_.x<<" "<<temp_.y<<" "<<temp_.z<<endl;
		}
		for(unsigned long j=0; j<in.FaceSet.size(); j++)
		{
			outfile<<"3 "<<in.FaceSet.at(j).a<<" "<<in.FaceSet.at(j).b<<" "<<in.FaceSet.at(j).c<<endl;
		}
		cout<<"finish!"<<endl;
	}
	outfile.close();
	
}

MyCube Process::Rotate(MyVector _i1, MyVector _i2, MyVector _j1, MyVector _j2)
{
	MyVector v2_,v_;
	MyCube met_,met1_,met2_;
	float angle,temp;
	float x,y,z;
	temp = _i1.mod()*_j1.mod();
//	cout<<temp<<endl;
	if(temp != 0)
		angle = acos(_i1.dot(_j1)/temp);
	else
		angle = PI/2;
	v_ = (_i1.plus(_j1));
	v_.unit();
	met_.a = cos(angle) + v_.a*v_.a*(1-cos(angle));
	met_.b = v_.a*v_.b*(1-cos(angle))-v_.c*sin(angle);
	met_.c = v_.b*sin(angle)+v_.a*v_.c*(1-cos(angle));

	met_.d = v_.c*sin(angle) + v_.a*v_.b*(1-cos(angle));
	met_.e = cos(angle) + v_.b*v_.b*(1-cos(angle));
	met_.f = v_.b*v_.c*(1-cos(angle))-v_.a*sin(angle);

	met_.g = v_.a*v_.c*(1-cos(angle))-v_.b*sin(angle);
	met_.h = v_.a*sin(angle) + v_.b*v_.c*(1-cos(angle));
	met_.i = cos(angle) + v_.c*v_.c*(1-cos(angle));

	x = _j2.a;
	y = _j2.b;
	z = _j2.c;
	v2_.a = met_.a*x+met_.d*y+met_.g*z;//M.a*x + M.b*y + M.c*z;
    v2_.b = met_.b*x+met_.e*y+met_.h*z;//M.d*x + M.e*y + M.f*z;
    v2_.c = met_.c*x+met_.f*y+met_.i*z;
	temp = _i2.mod()*v2_.mod();
	if(temp != 0)
		angle = acos(_i2.dot(v2_)/temp);
	else
		angle = PI/2;
	v_ = (_i2.plus(v2_));
	v_.unit();
    met1_.a = cos(angle) + v_.a*v_.a*(1-cos(angle));
	met1_.b = v_.a*v_.b*(1-cos(angle))-v_.c*sin(angle);
	met1_.c = v_.b*sin(angle)+v_.a*v_.c*(1-cos(angle));

	met1_.d = v_.c*sin(angle) + v_.a*v_.b*(1-cos(angle));
	met1_.e = cos(angle) + v_.b*v_.b*(1-cos(angle));
	met1_.f = v_.b*v_.c*(1-cos(angle))-v_.a*sin(angle);

	met1_.g = v_.a*v_.c*(1-cos(angle))-v_.b*sin(angle);
	met1_.h = v_.a*sin(angle) + v_.b*v_.c*(1-cos(angle));
	met1_.i = cos(angle) + v_.c*v_.c*(1-cos(angle));

	met2_.a = met_.a*met1_.a+met_.b*met1_.d+met_.c*met1_.g;
	met2_.b = met_.a*met1_.b+met_.b*met1_.e+met_.c*met1_.h;
	met2_.c = met_.a*met1_.c+met_.b*met1_.f+met_.c*met1_.i;

	met2_.d = met_.d*met1_.a+met_.e*met1_.d+met_.f*met1_.g;
	met2_.e = met_.d*met1_.b+met_.e*met1_.e+met_.f*met1_.h;
	met2_.f = met_.d*met1_.c+met_.e*met1_.f+met_.f*met1_.i;

	met2_.g = met_.g*met1_.a+met_.h*met1_.d+met_.i*met1_.g;
	met2_.h = met_.g*met1_.b+met_.h*met1_.e+met_.i*met1_.h;
	met2_.i = met_.g*met1_.c+met_.h*met1_.f+met_.i*met1_.i;


	return met2_;

}



/**
* @brief 求实对称矩阵的特征值及特征向量的雅克比法 
* 利用雅格比(Jacobi)方法求实对称矩阵的全部特征值及特征向量 
* @param pMatrix				长度为n*n的数组，存放实对称矩阵
* @param nDim					矩阵的阶数 
* @param pdblVects				长度为n*n的数组，返回特征向量(按列存储) 
* @param dbEps					精度要求 
* @param nJt					整型变量，控制最大迭代次数 
* @param pdbEigenValues			特征值数组
* @return 
*/
bool Process::JacbiCor(double * pMatrix,int nDim, double *pdblVects, double *pdbEigenValues, double dbEps,int nJt)
{
	for(int i = 0; i < nDim; i ++) 
	{   
		pdblVects[i*nDim+i] = 1.0f; 
		for(int j = 0; j < nDim; j ++) 
		{ 
			if(i != j)   
				pdblVects[i*nDim+j]=0.0f; 
		} 
	} 

	int nCount = 0;		//迭代次数
	while(1)
	{
		//在pMatrix的非对角线上找到最大元素
		double dbMax = pMatrix[1];
		int nRow = 0;
		int nCol = 1;
		for (int i = 0; i < nDim; i ++)			//行
		{
			for (int j = 0; j < nDim; j ++)		//列
			{
				double d = fabs(pMatrix[i*nDim+j]); 

				if((i!=j) && (d> dbMax)) 
				{ 
					dbMax = d;   
					nRow = i;   
					nCol = j; 
				} 
			}
		}

		if(dbMax < dbEps)     //精度符合要求 
			break;  

		if(nCount > nJt)       //迭代次数超过限制
			break;

		nCount++;

		double dbApp = pMatrix[nRow*nDim+nRow];
		double dbApq = pMatrix[nRow*nDim+nCol];
		double dbAqq = pMatrix[nCol*nDim+nCol];

		//计算旋转角度
		double dbAngle = 0.5*atan2(-2*dbApq,dbAqq-dbApp);
		double dbSinTheta = sin(dbAngle);
		double dbCosTheta = cos(dbAngle);
		double dbSin2Theta = sin(2*dbAngle);
		double dbCos2Theta = cos(2*dbAngle);

		pMatrix[nRow*nDim+nRow] = dbApp*dbCosTheta*dbCosTheta + 
			dbAqq*dbSinTheta*dbSinTheta + 2*dbApq*dbCosTheta*dbSinTheta;
		pMatrix[nCol*nDim+nCol] = dbApp*dbSinTheta*dbSinTheta + 
			dbAqq*dbCosTheta*dbCosTheta - 2*dbApq*dbCosTheta*dbSinTheta;
		pMatrix[nRow*nDim+nCol] = 0.5*(dbAqq-dbApp)*dbSin2Theta + dbApq*dbCos2Theta;
		pMatrix[nCol*nDim+nRow] = pMatrix[nRow*nDim+nCol];

		for(int i = 0; i < nDim; i ++) 
		{ 
			if((i!=nCol) && (i!=nRow)) 
			{ 
				int u = i*nDim + nRow;	//p  
				int w = i*nDim + nCol;	//q
				dbMax = pMatrix[u]; 
				pMatrix[u]= pMatrix[w]*dbSinTheta + dbMax*dbCosTheta; 
				pMatrix[w]= pMatrix[w]*dbCosTheta - dbMax*dbSinTheta; 
			} 
		} 

		for (int j = 0; j < nDim; j ++)
		{
			if((j!=nCol) && (j!=nRow)) 
			{ 
				int u = nRow*nDim + j;	//p
				int w = nCol*nDim + j;	//q
				dbMax = pMatrix[u]; 
				pMatrix[u]= pMatrix[w]*dbSinTheta + dbMax*dbCosTheta; 
				pMatrix[w]= pMatrix[w]*dbCosTheta - dbMax*dbSinTheta; 
			} 
		}

		//计算特征向量
		for(int i = 0; i < nDim; i ++) 
		{ 
			int u = i*nDim + nRow;		//p   
			int w = i*nDim + nCol;		//q
			dbMax = pdblVects[u]; 
			pdblVects[u] = pdblVects[w]*dbSinTheta + dbMax*dbCosTheta; 
			pdblVects[w] = pdblVects[w]*dbCosTheta - dbMax*dbSinTheta; 
		} 

	}

	//对特征值进行排序以及重新排列特征向量,特征值即pMatrix主对角线上的元素
	std::map<double,int> mapEigen;
	for(int i = 0; i < nDim; i ++) 
	{   
		pdbEigenValues[i] = pMatrix[i*nDim+i];

		mapEigen.insert(make_pair( pdbEigenValues[i],i ) );
	} 

	double *pdbTmpVec = new double[nDim*nDim];
	std::map<double,int>::reverse_iterator iter = mapEigen.rbegin();
	for (int j = 0; iter != mapEigen.rend(),j < nDim; ++iter,++j)
	{
		for (int i = 0; i < nDim; i ++)
		{
			pdbTmpVec[i*nDim+j] = pdblVects[i*nDim + iter->second];
		}

		//特征值重新排列
		pdbEigenValues[j] = iter->first;
	}

	//设定正负号
	for(int i = 0; i < nDim; i ++) 
	{
		double dSumVec = 0;
		for(int j = 0; j < nDim; j ++)
			dSumVec += pdbTmpVec[j * nDim + i];
		if(dSumVec<0)
		{
			for(int j = 0;j < nDim; j ++)
				pdbTmpVec[j * nDim + i] *= -1;
		}
	}

	memcpy(pdblVects,pdbTmpVec,sizeof(double)*nDim*nDim);
	delete []pdbTmpVec;

	return 1;
}
void Process::Output(string str, vector<Point_3> in)
{
	cout<<str<<endl;
	cout<<"num: "<<in.size()<<endl;
	for(unsigned long i=0;i<in.size();i++)
	{
		cout<<"x: "<<in.at(i).x<<" y: "<<in.at(i).y<<" z: "<<in.at(i).z<<endl;
	}
	cout<<""<<endl;
}

MyVector Process::ComU(vector<Point_3> point, vector<MyRelation> face)
{
	MyVector vet_;
	int faceNum;
	int pointNum;
	int p_,q_,r_;
	float x_,y_,z_;
	x_=y_=z_=0;
	faceNum = face.size();
	pointNum = point.size();
	//cout<<faceNum<<endl;
	for(int i=0;i<faceNum;++i)
	{
		p_ = face.at(i).a;
		q_ = face.at(i).b;
		r_ = face.at(i).c;
		x_ = x_ + point.at(p_).x+point.at(q_).x+point.at(r_).x;
		y_ = y_ + point.at(p_).y+point.at(q_).y+point.at(r_).y;
		z_ = z_ + point.at(p_).z+point.at(q_).z+point.at(r_).z;
	}
	vet_.a = x_ / (3*faceNum);
	vet_.b = y_ / (3*faceNum);
	vet_.c = z_ / (3*faceNum);
	return vet_;

}
MyCube Process::OBBMet(vector<Point_3> point, vector<MyRelation> face)
{
	MyCube mCMet(0,0,0,0,0,0,0,0,0);
	int faceNum;
	int pointNum;
	int p_,q_,r_;
	faceNum = face.size();
	pointNum = point.size();
	//cout<<faceNum<<endl;
	for(int i=0;i<pointNum;++i)
	{
		//改进方法，与面无关，仅与点有关
		mCMet.a += point.at(i).x*point.at(i).x;
		mCMet.b += point.at(i).x*point.at(i).y;
		mCMet.c += point.at(i).x*point.at(i).z;
		mCMet.e += point.at(i).y*point.at(i).y;
		mCMet.f += point.at(i).y*point.at(i).z;
		mCMet.i += point.at(i).z*point.at(i).z;
	}
/*	for(int i=0;i<faceNum;++i)
	{
		//面片上的3个点求obb
		p_ = face.at(i).a;
		q_ = face.at(i).b;
		r_ = face.at(i).c;
		mCMet.a = mCMet.a + point.at(p_).x*point.at(p_).x + point.at(q_).x*point.at(q_).x + point.at(r_).x*point.at(r_).x;
		mCMet.b = mCMet.b + point.at(p_).x*point.at(p_).y + point.at(q_).x*point.at(q_).y + point.at(r_).x*point.at(r_).y;
		mCMet.c = mCMet.c + point.at(p_).x*point.at(p_).z + point.at(q_).x*point.at(q_).z + point.at(r_).x*point.at(r_).z;
		mCMet.e = mCMet.e + point.at(p_).y*point.at(p_).y + point.at(q_).y*point.at(q_).y + point.at(r_).y*point.at(r_).y;
        mCMet.f = mCMet.f + point.at(p_).y*point.at(p_).z + point.at(q_).y*point.at(q_).z + point.at(r_).y*point.at(r_).z;
		mCMet.i = mCMet.i + point.at(p_).z*point.at(p_).z + point.at(q_).z*point.at(q_).z + point.at(r_).z*point.at(r_).z;
	}*/
	mCMet.a = mCMet.a/(3*faceNum);
	mCMet.b = mCMet.b/(3*faceNum);
	mCMet.c = mCMet.c/(3*faceNum);
	mCMet.d = mCMet.b;
	mCMet.e = mCMet.e/(3*faceNum);
	mCMet.f = mCMet.f/(3*faceNum);
	mCMet.g = mCMet.c;
	mCMet.h = mCMet.f;
	mCMet.i = mCMet.i/(3*faceNum);

	return mCMet;
}

MyVector Process::SurfaceV(MyVector tar, MyVector nor)
{
	float l;
	MyVector out;
	l = tar.dot(nor);
	out.a = tar.a - l*nor.a;
	out.b = tar.b - l*nor.b;
	out.c = tar.c - l*nor.c;
	return out;
}


