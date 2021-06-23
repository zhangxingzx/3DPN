#pragma once
#include <iostream>	  //标准的输入输出流头文件
#include <conio.h>	  //控制台输入输出头文件
#include <windows.h>  //windowsAPI的函数声明和宏
#include "TcAdsDef.h" //结构体和常量的声明
#include "TcAdsAPI.h" // ADS函数的声明
#include "map"

class  CBeckhOff
{
public:
	//接口
	//传入连接符s："CV_GVL.CV_FP"	传出lHdlVar句柄   返回值1：连接成功  0：失败
	bool Connect(const char* s ,unsigned long& lHdlVar);   
	//通讯是否连接成功  返回1：连接成功   0：失败
	bool GetPLCOnLine();
	//刷新通讯是否连接成功  （外部新建一个线程时时刷新） 返回1：连接成功   0：失败
	bool RefreshPLCOnLine();
	//读写 传入句柄  传出结构体
	bool ReadValue(unsigned long lHdlVar, unsigned long n, void* pData);
	bool WriteValue(unsigned long lHdlVar, unsigned long n, void* pData);

	CBeckhOff();
	~CBeckhOff();
private:

	static CBeckhOff * gs_pBeckhOff;
	PAmsAddr  m_pAddr;  	//定义端口地址变量
	AmsAddr   m_Addr;		//定义AMS地址变量  一定要定义成全局变量
	std::map<const char*, unsigned long> m_vetHadl;   //保存句柄
	bool m_isPLCOnLine;	//通讯是否连接成功

	void InitAds();
	void CloseAds(); 
};

