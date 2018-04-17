/*
   *****************************************************
   *                                  Word_Counter V1.1                                          *
   *                                 Writen by Hong tao li                                       *
   *                                     April 15th   2018                                            *
   *                                                                                                              *
   *                                                                                                              *
   *****************************************************

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
	string filename;             //文件名
	vector <string> text;    //全文存储器
	vector <string> order; //命令流
	int ordern;                     //命令数 
	long charn;                   //字符数
	int linen;                      //行数
	int wordn;                    //单词数
public:
	void Init(vector<string>& messagelist);  //wc初始化操作
	void Basecount();                                    //wc统计操作
	void Output();                                          //wc输出操作
};
//---------------------------------wc初始化操作-----------------------------------
void WC::Init(vector<string>& messagelist)//n为messagelist的成员数
{
	int n = messagelist.size();
	this->filename = messagelist[n - 1];//初始化文件名
	for (int i = 1 ; i < n - 1; i++)
		this->order.push_back( messagelist[i]) ;    //初始化命令流
	ordern = order.size();                                             //初始化命令数
	//--------------初始化数据--------------------
	charn = 0;
	wordn = 0;
	linen = 0;
	//--------------打开文件-----------------------
	ifstream infile(filename, ios::ate);
	if (!infile)
	{
		cerr << "Open error! Please check the filename." << endl;
		exit(1);
	}
	//--------------------------------------------------
	charn = infile.tellg();     //文件字符数统计
	//-------------------记录全文-------------------
	infile.seekg(0);   //把读指针定于文件开头
	string line; 
	while (getline(infile, line))
	{
		text.push_back(line);
		linen++;//同时完成总行数统计
	}
	//-------------------关闭文件--------------------
	infile.close();
	//--------------------------------------------------
}
//----------------------------------wc统计操作--------------------------------------
void WC::Basecount()
{
	//----------------单词统计-------------------
	string line;  
	for (int l = 0; l < linen; l++)
	{
		line = text[l];
		int e = 0;                   //读指针当前位置
		int b = 0;                  //读指针上次位置
		for (e = 0; e < line.length(); e++)
		{
			if ((line[e] == ' ' || line[e] == '.' || line[e] == '!' || line[e] == '?') && line[b] != ' ')
			{
				wordn++;
			}
			b = e;
		}
	}
	//------------------待扩展----------------------
	
	//-------------------------------------------------
}
//-----------------------------wc输出操作----------------------------------------
void WC::Output()
{
	for (int i = 0; i < ordern; i++)
	{
		//----------------输出字符数-----------------
		if (order[i] == "-c" || order[i] == "-C")
			cout << "Character number : " << charn << endl;
		//----------------输出字数--------------------
		else if (order[i] == "-w" || order[i] == "-W")
			cout << "Word number : " << wordn << endl;
		//----------------输出行数-------------------
		else if(order[i] == "-l" || order[i] == "-L")
			cout << "Line number : " << linen << endl;
		//-----------------待扩展-------------------

		//---------------------------------------------
	}
}
//----------------------------------------------------------------------------------
void Splitmessage(vector<string>&,string);//命令分割   返回命令数

int main()
{
	cout << "WORD COUNTER v1.0 "<< endl;   //标题
	vector <string> orderlist;
	string message="Begin";
	int n;														        //命令数
	while (1)                          
	{
		WC file;
		getline(cin, message);
		if (message == "exit" || message == "quit") break;// 输入exit或quit退出程序
		Splitmessage(orderlist,message);
		file.Init(orderlist);
		file.Basecount();
		file.Output();
	}
    return 0;
}

void Splitmessage(vector <string>&orderlist, string message)
{
	int b=0;                   //命令长度
	int e=0;                   //开始字符
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
			string x;
			x.assign(message, e, b);
			orderlist.push_back(x);
			e = e + b;                                   //开始字符跳过已录入命令
			b =0;								          //命令长度置零
		}	
	}
}