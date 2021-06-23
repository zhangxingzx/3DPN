#pragma once
#include <iostream>	  //��׼�����������ͷ�ļ�
#include <conio.h>	  //����̨�������ͷ�ļ�
#include <windows.h>  //windowsAPI�ĺ��������ͺ�
#include "TcAdsDef.h" //�ṹ��ͳ���������
#include "TcAdsAPI.h" // ADS����������
#include "map"

class  CBeckhOff
{
public:
	//�ӿ�
	//�������ӷ�s��"CV_GVL.CV_FP"	����lHdlVar���   ����ֵ1�����ӳɹ�  0��ʧ��
	bool Connect(const char* s ,unsigned long& lHdlVar);   
	//ͨѶ�Ƿ����ӳɹ�  ����1�����ӳɹ�   0��ʧ��
	bool GetPLCOnLine();
	//ˢ��ͨѶ�Ƿ����ӳɹ�  ���ⲿ�½�һ���߳�ʱʱˢ�£� ����1�����ӳɹ�   0��ʧ��
	bool RefreshPLCOnLine();
	//��д ������  �����ṹ��
	bool ReadValue(unsigned long lHdlVar, unsigned long n, void* pData);
	bool WriteValue(unsigned long lHdlVar, unsigned long n, void* pData);

	CBeckhOff();
	~CBeckhOff();
private:

	static CBeckhOff * gs_pBeckhOff;
	PAmsAddr  m_pAddr;  	//����˿ڵ�ַ����
	AmsAddr   m_Addr;		//����AMS��ַ����  һ��Ҫ�����ȫ�ֱ���
	std::map<const char*, unsigned long> m_vetHadl;   //������
	bool m_isPLCOnLine;	//ͨѶ�Ƿ����ӳɹ�

	void InitAds();
	void CloseAds(); 
};

