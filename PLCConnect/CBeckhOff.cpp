#include "CBeckhOff.h"
#include <string>


CBeckhOff::CBeckhOff()
{
	m_isPLCOnLine = false;
	InitAds();
}
CBeckhOff::~CBeckhOff()
{
	CloseAds();
}
void CBeckhOff::InitAds()
{
	//建立接口通讯连接
	long       nPort;	//定义端口变量
	m_pAddr = &m_Addr;
	nPort = AdsPortOpen();//打开通讯端口
	long      nErr = 0;
	nErr = AdsGetLocalAddress(m_pAddr);
	if (nErr)
	{
		std::cout << "Ads初始化失败\n";
		return;
	}
	m_pAddr->port = 851;

	m_isPLCOnLine = true;

}
void CBeckhOff::CloseAds()
{
	LONG nErr = AdsPortClose(); //关闭ADS通讯端口
	if (nErr)
	{
		//检查关闭通讯端口的操作是否执行成功
		std::cout << "Ads关闭通讯端口失败\n";
		return;
	}
}
bool CBeckhOff::ReadValue(unsigned long lHdlVar, unsigned long n, void*	pData)
{
	long nerr;
	//通过句柄读取数组
	nerr = AdsSyncReadReq(m_pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, n, pData);
	if (nerr)
	{
		return false;
	}
	return true;
	
}
bool CBeckhOff::WriteValue(unsigned long lHdlVar, unsigned long n, void* pData)
{
	long nerr;
	//通过句柄向PLC写入数组
	nerr = AdsSyncWriteReq(m_pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, n, pData);
	if (nerr)
	{
		return false;
	}
	return true;
}

bool CBeckhOff::Connect(const char* s ,unsigned long& lHdlVar)
{
	if (m_vetHadl.find(s) != m_vetHadl.end())
	{
		lHdlVar = m_vetHadl[s];
		return true;
	}

	//重新加入m_vetHadl中
	const int nlen = strlen(s)+1;
	if (nlen > 50)
	{
		return false;
	}

	char val[50];//足够长
	strncpy_s(val, s,nlen);

	long      nErr = 0;
	//char val1[] = { "CV_GVL.CV_FP" };
	nErr = AdsSyncReadWriteReq(m_pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar), &lHdlVar, sizeof(val), val);

	if (nErr)
	{
		return false;
	}
	m_vetHadl[s] = lHdlVar;
	return true;
}

bool CBeckhOff::GetPLCOnLine()
{
	return m_isPLCOnLine;
}

bool CBeckhOff::RefreshPLCOnLine()
{
	long      nErr = 0;
	nErr = AdsGetLocalAddress(m_pAddr);
	if (nErr)
	{
		m_isPLCOnLine = false;
		return m_isPLCOnLine;
	}
	else
	{
		m_isPLCOnLine = true;
		return m_isPLCOnLine;
	}
}