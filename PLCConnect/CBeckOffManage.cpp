#include "CBeckOffManage.h"

CBeckOffManage * CBeckOffManage::gs_pBeckOffManage = NULL;

CBeckOffManage * CBeckOffManage::InitInstance()
{
	if (gs_pBeckOffManage == NULL)
	{
		gs_pBeckOffManage = new CBeckOffManage();
	}

	return gs_pBeckOffManage;
}

void CBeckOffManage::DestroyInstance()
{
	if (gs_pBeckOffManage != NULL)
	{
		delete gs_pBeckOffManage;
		gs_pBeckOffManage = NULL;
	}
}

CBeckOffManage::CBeckOffManage()
{
	m_pBeckhOff = NULL;
	m_pBeckhOff = new CBeckhOff();
}
CBeckOffManage::~CBeckOffManage()
{
	if (m_pBeckhOff != NULL)
	{
		delete m_pBeckhOff;
		m_pBeckhOff = NULL;
	}
}
bool CBeckOffManage::Connect(const char* s, unsigned long& lHdlVar)
{
	if (m_pBeckhOff)
	{
		return m_pBeckhOff->Connect(s, lHdlVar);
	}
}

//ͨѶ�Ƿ����ӳɹ�  ����1�����ӳɹ�   0��ʧ��
bool CBeckOffManage::GetPLCOnLine()
{
	if (m_pBeckhOff)
	{
		return m_pBeckhOff->GetPLCOnLine();
	}
}
//ˢ��ͨѶ�Ƿ����ӳɹ�  ����1�����ӳɹ�   0��ʧ��
bool CBeckOffManage::RefreshPLCOnLine()
{
	if (m_pBeckhOff)
	{
		return m_pBeckhOff->RefreshPLCOnLine();
	}
}

bool CBeckOffManage::ReadValue(unsigned long lHdlVar, unsigned long n, void*pData)
{
	if (m_pBeckhOff)
	{
		return m_pBeckhOff->ReadValue(lHdlVar, n, pData);
	}
}
bool CBeckOffManage::WriteValue(unsigned long lHdlVar, unsigned long n, void* pData)
{
	if (m_pBeckhOff)
	{
		return m_pBeckhOff->WriteValue(lHdlVar, n, pData);
	}
}
using namespace std;
void main()
{
	USHORT      nAdsState;	//����PLC����Ϣ
	USHORT      nDeviceState = 0;
	long        nErr, nPort;
	char         ch;
	void        *pData = NULL;
	AmsAddr     Addr;
	PAmsAddr    pAddr = &Addr;

	//�����ӿ�ͨѶ����
	nPort = AdsPortOpen();
	nErr = AdsGetLocalAddress(pAddr);
	if (nErr) cerr << "Error: AdsGetLocalAddress: " << nErr << '\n';

	pAddr->port = 851;

	//�����������
	cout << "(R) -> PLC Run\n";		//����'R'����PLC
	cout << "(S) -> PLC Stop\n";	//����'S'ֹͣPLC
	cout.flush();
	ch = getchar();
	ch = toupper(ch);
	//��������ָ��ı�PLC��״̬
	while ((ch == 'R') || (ch == 'S')) //ʵ��ѭ������
	{
		switch (ch)
		{
		case 'R':
			nAdsState = ADSSTATE_RUN;
			break;
		case 'S':
			nAdsState = ADSSTATE_STOP;
			break;
		}
		nErr = AdsSyncWriteControlReq(pAddr, nAdsState, nDeviceState, 0, pData);
		if (nErr) cerr << "Error: AdsSyncWriteControlReq: " << nErr << '\n';
		cin.ignore();
		ch = getchar();
		ch = toupper(ch);
	}

	//�رն˿�ͨѶ
	nErr = AdsPortClose();
	if (nErr) cerr << "Error: AdsPortClose: " << nErr << '\n';
}