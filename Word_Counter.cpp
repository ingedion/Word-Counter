﻿/*
   **************************************************************************
   *                              Word_Counter V1.0                         *
   *                              Writen by Hong tao li                     *
   *                              April 15th   2018                         *
   *                                                                        *
   *                                                                        *
   **************************************************************************

*/

#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class WC
{
private:
	string filename;  //文件名
	string order[10]; //命令流
	int ordern;           //命令数 
	long charn;          //字符数
	int wordn;           //单词数
public:
	void Init(string* messagelist, int n);
	void Basecount();
	void Output();
};

void WC::Init(string* messagelist, int n)//n为messagelist的成员数
{
	int i, j;
	this->filename = messagelist[n - 1];//初始化文件名
	for (i = 1, j = 0; i < n - 1; i++, j++)
		this->order[j] = messagelist[i];    //初始化命令流
	ordern = j;                                         //初始化命令数
}

void WC::Basecount()
{
	//--------------初始化数据--------------------
	charn = 0;
	wordn = 0;
	//--------------打开文件-----------------------
	ifstream infile(filename, ios::ate);
	if (!infile)
	{
		cerr << "Open error! Please check the filename." << endl;
		exit(1);
	}
	//--------------------------------------------------
	charn = infile.tellg();     //文件字符数统计
	infile.seekg(0);               //把读指针定于文件开头
	for (int i = 0; i < ordern; i++)
	{
		//----------------单词统计-------------------
		if (order[i] == "-w" || order[i] == "-W")
		{
			string text;
			int e = 0;
			int b = 0;
			getline(infile, text);
			for (e = 0; e< charn; e++)
			{
				if ((text[e] == ' ' || text[e] == '.' || text[e] == '!' || text[e] == '?') && text[b] != ' ')
				{
					wordn++;
				}
				b = e;
			}
		}
		//------------------待扩展----------------------
		/*if ()
		{

		}*/
		//-------------------------------------------------
	}
}

void WC::Output()
{
	for (int i = 0; i < ordern; i++)
	{
		if (order[i] == "-c" || order[i] == "-C")
			cout << "Character number : " << charn << endl;
		else if (order[i] == "-w" || order[i] == "-W")
			cout << "Word number : " << wordn << endl;
		//------------------待扩展-------------------
		/*else if()
		*/
		//----------------------------------------------
	}
}

int Splitmessage(string*,string);//命令分割   返回命令数

int main()
{
	cout << "WORD COUNTER v1.0 "<< endl;   //标题
	string orderlist[10];                                         //最多存储十条命令
	string message="Begin";
	int n;														        //命令数
	while (1)                          
	{
		//cout << ">>";                                            //输入提示符
		WC file;
		getline(cin, message);
		if (message == "exit" || message == "quit") break;// 输入exit或quit退出程序
		n=Splitmessage(orderlist,message);
		file.Init(orderlist, n);
		file.Basecount();
		file.Output();
	}
    return 0;
}

int Splitmessage(string* orderlist, string message)
{
	int b=0;                   //命令长度
	int e=0;                   //开始字符
	int n=0;					//命令号
	int lenth = message.length();
	for (e = 0; e< lenth; e++)
	{
		if (message[e] != ' ')                    //遍历string寻找命令
		{
			while (message[e+b] != ' ')
			{
				b++;
				if (e+b>= lenth) break;
			}
			orderlist[n].assign(message, e, b);
			e = e + b;                                   //开始字符跳过已录入命令
			b =0;								          //命令长度置零
			n++;                                        //命令号加一
		}	
	}
	return n;
}
