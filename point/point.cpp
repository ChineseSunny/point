#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


struct Point{
	string mName;//点名
	string qName;//映射点名
	string mTime;//时间间隔
};

int read_save()
{
	//open file
	FILE *fp = fopen("E:\\b.csv", "r");

	vector<Point> v;//点结构体
	vector<string> vq;//点名
	map<string, string> m;

	if (NULL == fp)
	{
		printf("file open err");
		return -1;
	}

	char buf[1024] = { 0 };
	//read the first line
	fgets(buf, sizeof(buf), fp);
	//fseek(fp, 0, SEEK_CUR);
	//cout << "first line: " << buf << '\n';
	//read file
	while (!feof(fp))
	{
		fgets(buf, sizeof(buf), fp);
		//read point
		char *pname = strtok(buf, ",");
		//cout << "pname = "<< pname << endl;

		char* ptime = NULL;
		for (int i = 0; i < 10; ++i)
		{
			ptime = strtok(NULL, ",");
		}
		//cout << "ptime = "<< ptime << endl;
		//insert Point into vector
		Point p;
		p.mName = pname;
		p.mTime = ptime;
		v.push_back(p);
	}

	//遍历点名 将映射点名放入 vector vq
	for (vector<Point>::iterator it = v.begin(); it != v.end(); ++it)
	{
		//cout <<"it->mName"<< it->mName << "  it->mTime" <<it->mTime << endl;
		//string to c_str
		//string name = it->mName;
		//cout << "name : " << name << endl;
		char c_str[20] = { 0 };
		//点名
		it->mName.copy(c_str, it->mName.length(), 0);
		//cout << "c_str" << c_str <<endl;
		//点名--> 设备名
		char * str = strtok(c_str, "_");
		//cout << "str = " << str << endl;
		//设备名
		string s_str = str;
		//转换为_Q的 映射点名
		string s_str_q = s_str + "_Q";

		//cout << "str = "<<s_str_q <<endl;
		//遍历找到映射点名
		for (vector<Point>::iterator itq = v.begin(); itq != v.end(); ++itq)
		{
			if (s_str_q == it->mName)
			{
				vq.push_back(s_str_q);
				break;
			}
		}
	}

	/* 映射点名测试
	for (vector<string>::iterator itq = vq.begin(); itq != vq.end(); ++itq)
	{
	cout << *itq << endl;
	}*/

	//遍历点
	for (vector<Point>::iterator it = v.begin(); it != v.end(); ++it)
	{
		char c_str[20] = { 0 };
		//点名
		it->mName.copy(c_str, it->mName.length(), 0);
		//cout << "c_str" << c_str <<endl;
		//点名--> 设备名
		char * str = strtok(c_str, "_");
		//cout << "str = " << str << endl;
		//设备名
		string s_str = str;
		//转换为_Q的 映射点名
		string s_str_q = s_str + "_Q";
		//遍历映射点
		for (vector<string>::iterator itq = vq.begin(); itq != vq.end(); ++itq)
		{
			if (s_str_q == *itq)
			{
				m.insert(pair<string, string>(it->mName, *itq));
			}
			break;
		}

		for (map<string, string>::iterator it = m.begin(); it != m.end(); ++it)
		{
			cout << it->first << "  " << it->second << endl;
		}


	}


	return 0;
}


int main()
{
	read_save();

	system("pause");
	return 0;
}
