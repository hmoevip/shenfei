#include "compute.h"
#include <QString>
#include <QMessageBox>//! [0]

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
	PointSet.clear();
	order_xy.clear();
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
						    Point_3 temp(x,z,y,i_vertex);
                            PointSet.push_back(temp);
							i_vertex ++;
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
	cout<<"Reading data is completed!...."<<endl;
/*	for(int i=0;i<PointSet.size();i++)
	{
		cout<<PointSet[i].count <<PointSet[i].x <<PointSet[i].y <<PointSet[i].z <<endl;
	}
*/
	return true;
}

Point_3 Process::FindSmallest(int flag)
{
	Point_3 smallpoint;
	smallpoint = PointSet[0];
	switch(flag)
	{
		case 0:
			for(unsigned long i=1;i<PointSet.size();i++)
			{
				if(PointSet[i].x<smallpoint.x)
					smallpoint = PointSet[i];
			}
			break;
		case 1:
			for(unsigned long i=1;i<PointSet.size();i++)
			{
				if(PointSet[i].y<smallpoint.y)
					smallpoint = PointSet[i];
			}
			break;
		case 2:
			for(unsigned long i=1;i<PointSet.size();i++)
			{
				if(PointSet[i].z<smallpoint.z)
					smallpoint = PointSet[i];
			}
			break;
		default:
			cout<<"flag does not exit!"<<endl;
	}
	return smallpoint;
}

long double Process::ComputeAngle(Point_3 start,Point_3 end, Point_3 newend,int flag)
{
	long double angle;
	angle = 0;
	long double a,b,c,d,e;
	if(start==newend||end==newend)
	{
		angle = 0;
		return angle;
	}
	switch(flag)
	{
		case 0:
			a = end.x-start.x;
			b = end.y-start.y;
		    c = newend.x-start.x;
			d = newend.y-start.y;
			e = sqrt(a*a+b*b)*sqrt(c*c+d*d);
			angle = acos((a*c+b*d)/e);
			break;
		case 1:
			a = end.x-start.x;
			b = end.z-start.z;
		    c = newend.x-start.x;
			d = newend.z-start.z;
			e = sqrt(a*a+b*b)*sqrt(c*c+d*d);
			angle = acos((a*c+b*d)/e);
			break;
		case 2:
			a = end.z-start.z;
			b = end.y-start.y;
		    c = newend.z-start.z;
			d = newend.y-start.y;
			e = sqrt(a*a+b*b)*sqrt(c*c+d*d);
			angle = acos((a*c+b*d)/e);
			break;
		default:
			e = 0;
			break;
	}
		if(e==0)
		angle = 0;
	return angle;
}

long double Process::ComputeAngleB(Point_3 start,Point_3 end, Point_3 newend,int flag)
{
	long double angle;
	angle = 0;
	long double a,b,c,d,e;
	if(start==newend||end==newend)
	{
		angle = 0;
		return angle;
	}
	switch(flag)
	{
		case 0:
			a = end.x-start.x;
			b = end.y-start.y;
		    c = newend.x-end.x;
			d = newend.y-end.y;
			e = sqrt(a*a+b*b)*sqrt(c*c+d*d);
			angle = acos((a*c+b*d)/e);
			break;
		case 1:
			a = end.x-start.x;
			b = end.z-start.z;
		    c = newend.x-end.x;
			d = newend.z-end.z;
			e = sqrt(a*a+b*b)*sqrt(c*c+d*d);
			angle = acos((a*c+b*d)/e);
			break;
		case 2:
			a = end.z-start.z;
			b = end.y-start.y;
		    c = newend.z-end.z;
			d = newend.y-end.y;
			e = sqrt(a*a+b*b)*sqrt(c*c+d*d);
			angle = acos((a*c+b*d)/e);
			break;
		default:
			e=0;
			break;
	}
	if(e==0)
		angle = 0;
	return angle;
}

long double Process::Distance(Point_3 start, Point_3 end,int flag)
{
	long double distance;
	switch(flag)
	{
		case 0:
			distance = sqrt((start.x-end.x)*(start.x-end.x)+(start.y-end.y)*(start.y-end.y));
			break;
		case 1:
			distance = sqrt((start.x-end.x)*(start.x-end.x)+(start.z-end.z)*(start.z-end.z));
            break;
		case 2:
			distance = sqrt((start.z-end.z)*(start.z-end.z)+(start.y-end.y)*(start.y-end.y));
            break;
		default:
			distance = 0;
			break;
	}
	return distance;
}

void Process::ComputeXYConvex()
{
	Point_3 start,temp_point,next_point,stop_flag;
	long double angle,temp_angle;
	unsigned long safe;
	long double distance_temp,same_temp,d_temp;
	int ff;
	ff=0;
	angle=PI;
	distance_temp=0;
	same_temp=0;
	safe = 0;
	start = FindSmallest(1);
	order_xy.push_back(start);
	temp_point = start;
	stop_flag = start;
    temp_point.x = start.x+0.001;
//	temp_point.y = start.y-0.001;
	for(unsigned long i=0;i<PointSet.size();i++)
	{
		temp_angle=ComputeAngle(start,temp_point,PointSet[i],0);
		//cout<<i<<" temp_angle: "<<temp_angle<<endl;
		if(temp_angle<0.0001)
		{
			d_temp = Distance(start,PointSet[i],0);
		//	cout<<d_temp<<" "<<distance_temp<<endl;
			if(d_temp>distance_temp)
			{
				angle = 0;
				distance_temp = d_temp;
				next_point = PointSet[i];
			}
		}else if(angle-temp_angle>0.001)
		{
			angle = temp_angle;
			next_point = PointSet[i];
		}
		//cout<<i<<" angle: "<<angle<<endl;
	}
    order_xy.push_back(next_point);
	temp_point = next_point;
	while(next_point!=stop_flag)
	{
		safe++;
		angle = PI;
		distance_temp = Distance(start,temp_point,0);
		for(unsigned long i=0;i<PointSet.size();i++)
		{
			temp_angle = ComputeAngleB(start,temp_point,PointSet[i],0);
			if(temp_angle==0)
			{
				d_temp = Distance(start,PointSet[i],0);
				if(d_temp>distance_temp)
				{	
					angle = 0;
					distance_temp = d_temp;
					next_point = PointSet[i];
					order_xy.pop_back();
					order_xy.push_back(next_point);
				}
			}else if(angle>temp_angle)
			{
				angle = temp_angle;
				next_point = PointSet[i];
			}
		}
		if(angle!=0)
		{
			order_xy.push_back(next_point);
		}
		start = order_xy[order_xy.size()-2];
		temp_point = order_xy.back();
		if(safe>PointSet.size())
			break;
	}
	order_xy.pop_back();
	cout<<order_xy.size()<<endl;
}

void Process::ComputeXZConvex()
{
	Point_3 start,temp_point,next_point,stop_flag;
	long double angle,temp_angle;
	unsigned long safe;
	long double distance_temp,same_temp,d_temp;
	angle=PI;
	distance_temp=0;
	same_temp=0;
	safe = 0;
	start = FindSmallest(2);
	order_xz.push_back(start);
	temp_point = start;
	stop_flag = start;
    temp_point.x = start.x+0.001;
//	temp_point.y = start.y-0.001;
	for(unsigned long i=0;i<PointSet.size();i++)
	{
		temp_angle=ComputeAngle(start,temp_point,PointSet[i],1);
		//cout<<i<<" temp_angle: "<<temp_angle<<endl;
		if(temp_angle<0.0001)
		{
			d_temp = Distance(start,PointSet[i],1);
		//	cout<<d_temp<<" "<<distance_temp<<endl;
			if(d_temp>distance_temp)
			{
				angle = 0;
				distance_temp = d_temp;
				next_point = PointSet[i];
			}
		}else if(angle-temp_angle>0.001)
		{
			angle = temp_angle;
			next_point = PointSet[i];
		}
		//cout<<i<<" angle: "<<angle<<endl;
	}
    order_xz.push_back(next_point);
	temp_point = next_point;
	while(next_point!=stop_flag)
	{
		safe++;
		angle = PI;
		distance_temp = Distance(start,temp_point,1);
		for(unsigned long i=0;i<PointSet.size();i++)
		{
			temp_angle = ComputeAngleB(start,temp_point,PointSet[i],1);
			if(temp_angle==0)
			{
				d_temp = Distance(start,PointSet[i],1);
				if(d_temp>distance_temp)
				{	
					angle = 0;
					distance_temp = d_temp;
					next_point = PointSet[i];
					order_xz.pop_back();
					order_xz.push_back(next_point);
				}
			}else if(angle>temp_angle)
			{
				angle = temp_angle;
				next_point = PointSet[i];
			}
		}
		if(angle!=0)
		{
			order_xz.push_back(next_point);
		}
		start = order_xz[order_xz.size()-2];
		temp_point = order_xz.back();
		if(safe>PointSet.size())
			break;
	}
	order_xz.pop_back();
	cout<<order_xz.size()<<endl;
}

void Process::ComputeConvex()
{
	ComputeXYConvex();
	ComputeXZConvex();
	ComputeYZConvex();

}
void Process::ComputeYZConvex()
{
	Point_3 start,temp_point,next_point,stop_flag;
	long double angle,temp_angle;
	unsigned long safe;
	long double distance_temp,same_temp,d_temp;
	int ff;
	ff=0;
	angle=PI;
	distance_temp=0;
	same_temp=0;
	safe = 0;
	start = FindSmallest(2);
	order_yz.push_back(start);
	temp_point = start;
	stop_flag = start;
    temp_point.y = start.y+0.001;
//	temp_point.y = start.y-0.001;
	for(unsigned long i=0;i<PointSet.size();i++)
	{
		temp_angle=ComputeAngle(start,temp_point,PointSet[i],2);
		//cout<<i<<" temp_angle: "<<temp_angle<<endl;
		if(temp_angle<0.0001)
		{
			d_temp = Distance(start,PointSet[i],2);
		//	cout<<d_temp<<" "<<distance_temp<<endl;
			if(d_temp>distance_temp)
			{
				angle = 0;
				distance_temp = d_temp;
				next_point = PointSet[i];
			}
		}else if(angle-temp_angle>0.001)
		{
			angle = temp_angle;
			next_point = PointSet[i];
		}
		//cout<<i<<" angle: "<<angle<<endl;
	}
    order_yz.push_back(next_point);
	temp_point = next_point;
	while(next_point!=stop_flag)
	{
		safe++;
		angle = PI;
		distance_temp = Distance(start,temp_point,2);
		for(unsigned long i=0;i<PointSet.size();i++)
		{
			temp_angle = ComputeAngleB(start,temp_point,PointSet[i],2);
			if(temp_angle==0)
			{
				d_temp = Distance(start,PointSet[i],2);
				if(d_temp>distance_temp)
				{	
					angle = 0;
					distance_temp = d_temp;
					next_point = PointSet[i];
					order_yz.pop_back();
					order_yz.push_back(next_point);
				}
			}else if(angle>temp_angle)
			{
				angle = temp_angle;
				next_point = PointSet[i];
			}
		}
		if(angle!=0)
		{
			order_yz.push_back(next_point);
		}
		start = order_yz[order_yz.size()-2];
		temp_point = order_yz.back();
		if(safe>PointSet.size())
			break;
	}
	order_yz.pop_back();
	cout<<order_yz.size()<<endl;
}

