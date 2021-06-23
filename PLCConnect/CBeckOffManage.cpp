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

//通讯是否连接成功  返回1：连接成功   0：失败
bool CBeckOffManage::GetPLCOnLine()
{
	if (m_pBeckhOff)
	{
		return m_pBeckhOff->GetPLCOnLine();
	}
}
//刷新通讯是否连接成功  返回1：连接成功   0：失败
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
	USHORT      nAdsState;	//包含PLC的信息
	USHORT      nDeviceState = 0;
	long        nErr, nPort;
	char         ch;
	void        *pData = NULL;
	AmsAddr     Addr;
	PAmsAddr    pAddr = &Addr;

	//建立接口通讯连接
	nPort = AdsPortOpen();
	nErr = AdsGetLocalAddress(pAddr);
	if (nErr) cerr << "Error: AdsGetLocalAddress: " << nErr << '\n';

	pAddr->port = 851;

	//输入控制命令
	cout << "(R) -> PLC Run\n";		//输入'R'启动PLC
	cout << "(S) -> PLC Stop\n";	//输入'S'停止PLC
	cout.flush();
	ch = getchar();
	ch = toupper(ch);
	//根据输入指令改变PLC的状态
	while ((ch == 'R') || (ch == 'S')) //实现循环控制
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

	//关闭端口通讯
	nErr = AdsPortClose();
	if (nErr) cerr << "Error: AdsPortClose: " << nErr << '\n';
}