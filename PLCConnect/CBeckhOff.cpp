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
	//�����ӿ�ͨѶ����
	long       nPort;	//����˿ڱ���
	m_pAddr = &m_Addr;
	nPort = AdsPortOpen();//��ͨѶ�˿�
	long      nErr = 0;
	nErr = AdsGetLocalAddress(m_pAddr);
	if (nErr)
	{
		std::cout << "Ads��ʼ��ʧ��\n";
		return;
	}
	m_pAddr->port = 851;

	m_isPLCOnLine = true;

}
void CBeckhOff::CloseAds()
{
	LONG nErr = AdsPortClose(); //�ر�ADSͨѶ�˿�
	if (nErr)
	{
		//���ر�ͨѶ�˿ڵĲ����Ƿ�ִ�гɹ�
		std::cout << "Ads�ر�ͨѶ�˿�ʧ��\n";
		return;
	}
}
bool CBeckhOff::ReadValue(unsigned long lHdlVar, unsigned long n, void*	pData)
{
	long nerr;
	//ͨ�������ȡ����
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
	//ͨ�������PLCд������
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

	//���¼���m_vetHadl��
	const int nlen = strlen(s)+1;
	if (nlen > 50)
	{
		return false;
	}

	char val[50];//�㹻��
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