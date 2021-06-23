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
	// ��ȡ����
	static CBeckOffManage* InitInstance();
	static void DestroyInstance();

	//�ӿ�
	//�������ӷ�s��"CV_GVL.CV_FP"	����lHdlVar���   ����ֵ1�����ӳɹ�  0��ʧ��
	bool Connect(const char* s, unsigned long& lHdlVar);

	//ͨѶ�Ƿ����ӳɹ�  ����1�����ӳɹ�   0��ʧ��
	bool GetPLCOnLine();
	//ˢ��ͨѶ�Ƿ����ӳɹ�  ���ⲿ�½�һ���߳�ʱʱˢ�£� ����1�����ӳɹ�   0��ʧ��
	bool RefreshPLCOnLine();

	//��д ������  �����ṹ��
	bool ReadValue(unsigned long lHdlVar, unsigned long n, void*	pData);
	bool WriteValue(unsigned long lHdlVar, unsigned long n, void* pData);

};

