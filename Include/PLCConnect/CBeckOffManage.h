#pragma once
#include "CBeOffCommon.h"

#ifdef CBEOFF_EXPORTS
#define CBEOFF_API __declspec(dllimport)
#else
#define CBEOFF_API __declspec(dllexport)
#endif
class CBEOFF_API CBeckOffManage
{
public:
	// 获取单例
	static CBeckOffManage* InitInstance();
	static void DestroyInstance();

	//接口
	//传入连接符s："CV_GVL.CV_FP"	传出lHdlVar句柄   返回值1：连接成功  0：失败
	bool Connect(const char* s, unsigned long& lHdlVar);

	//通讯是否连接成功  返回1：连接成功   0：失败
	bool GetPLCOnLine();
	//刷新通讯是否连接成功  （外部新建一个线程时时刷新） 返回1：连接成功   0：失败
	bool RefreshPLCOnLine();

	//读写 传入句柄  传出结构体
	bool ReadValue(unsigned long lHdlVar, unsigned long n, void*	pData);
	bool WriteValue(unsigned long lHdlVar, unsigned long n, void* pData);

};

