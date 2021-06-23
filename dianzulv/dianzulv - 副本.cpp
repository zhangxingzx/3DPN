#include "dianzulv.h"
#pragma execution_character_set("utf-8") //Qt�пؼ�������ʾ
#include <iostream>
#include "CBeckOffManage.h"   //PLC��д

using namespace std;
dianzulv* dianzulv::m_dianzulv = NULL;

void PLC()
{
	while(dianzulv::m_dianzulv->m_plcRun)
	{
		float Initialvalue[202];
		//��ȡads�Ƿ�ͨѶ�ɹ�
		bool flag2 = CBeckOffManage::InitInstance()->GetPLCOnLine();
		//ͨ�������ȡ�ṹ���ֵ
		bool flag3 = CBeckOffManage::InitInstance()->ReadValue(dianzulv::m_dianzulv->lHdlVar1, sizeof(Initialvalue), &Initialvalue);
		//bool flag3 = CBeckOffManage::InitInstance()->ReadValue(dianzulv::m_dianzulv->lHdlVar1, sizeof(dianzulv::m_dianzulv->voltage), &dianzulv::m_dianzulv->voltage);
		if (Initialvalue[0] == 1)
		{
			emit dianzulv::m_dianzulv->SignPN();   //�����ź�
			
		}
		if (Initialvalue[1] == 1)
		{
			for (int i = 0; i < 200; i++)
			{
				dianzulv::m_dianzulv->voltage[i] = Initialvalue[i+2];
			}

			emit dianzulv::m_dianzulv->SignDraw();   //�����ź�
			dianzulv::m_dianzulv->find_U(dianzulv::m_dianzulv->voltage);  //��ѹ������ֵ
			dianzulv::m_dianzulv->find_P(dianzulv::m_dianzulv->voltage);  //�����ʺ�����ֵ
		} 
		//ͨ�����д��ṹ���ֵ
		//bool flag4 = CBeckOffManage::InitInstance()->WriteValue(dianzulv::m_dianzulv->lHdlVar1, sizeof(Initialvalue), &Initialvalue);
	}
	//system("pause");
}

void dianzulv::PLCthread()   //PLC���߳�
{
	m_plcRun = 1;
    t=std::thread(PLC);
}

void dianzulv::draw() //��ͼ
{
	series->setName("spline");
	series2->setName("spline");
	series->clear();
	series2->clear();
	for (int i = 0; i < 200; i++)
	{
	 series->append(i, voltage[i]);//��ȡ��ѹ���ݣ������������������õ�������
	}
	for (int i = 0; i < 90; i++)
	{
		series2->append(i, find_P(voltage)[i]);//��ȡ����������
	}

	//PLC��ȡ�����õ���ѹ�ź�����
	QString strMax_U = QString::number(find_U(voltage)[0], 'f', 4);//��ѹ���ֵ
	QString strMin_U = QString::number(find_U(voltage)[1], 'f', 4);//��ѹ��Сֵ
	QString strAvg_U = QString::number(find_U(voltage)[2], 'f', 4);//��ѹƽ��ֵ
	ui.lineEdit_max_U->setText(strMax_U);
	ui.lineEdit_min_U->setText(strMin_U);
	ui.lineEdit_avg_U->setText(strAvg_U);

	QString strMax_P = QString::number(find_P(voltage)[90], 'f', 4);//���������ֵ
	QString strMin_P = QString::number(find_P(voltage)[91], 'f', 4);//��������Сֵ
	QString strAvg_P = QString::number(find_P(voltage)[92], 'f', 4);//������ƽ��ֵ
	ui.lineEdit_max_P->setText(strMax_P);
	ui.lineEdit_min_P->setText(strMin_P);
	ui.lineEdit_avg_P->setText(strAvg_P);
}

float* dianzulv::find_U(float voltage[])//��ʼ200����ѹ����Ѱ�������Сֵ������
{
	float min = voltage[0], max = voltage[0], sum = 0, avg = 0;//��ʼ��ѹ��ʼ��ֵ
	float vecNum[3];                               //�������ֵ����Сֵ��ƽ��ֵ
	for (int i = 0; i < m; i++)
	{
		sum += voltage[i];
		if (voltage[i] > max)
		{
			max = voltage[i];
			continue;
		}
		else if (voltage[i] < min)
		{
			min = voltage[i];
			continue;
		}
	}
	vecNum[0] = max;       //���ֵ
	vecNum[1] = min;     //��Сֵ
	vecNum[2] = sum / m; //ƽ����
	return vecNum;
}



float* dianzulv::find_P(float voltage[])//��ʼ200����ѹ���ݵõ������ʴ�����
{
	
	float sum_U = 0, sum_p = 0; //��ʼ��ѹ��������ֵ��ʼ��ֵ
	float U1 = 3.52, p1 = 0.4, t1 = 180;//�Ƚ������ĳ�ʼ��ѹ��U1��������p1�����t1��
	float U2, p2, t2=180;//�Ƚ������ĳ�ʼ��ѹ��U2��������p2�����t2��ʵ�ʺ��t2һֱ�仯��ͨ������ʿ��������ȡ��
	float p[93];//ѡȡ��Ƭ����̽ͷ�·�ʱ�ĵ�ѹ�ź���Ŀ����õ��ĵ�������Ŀ�����ϼ���3�������ֵ����Сֵ��ƽ��ֵ��
	for (int i = 0; i < 20; i++)//��������Ҫ�Ȳɼ���Ƭδ����̽ͷ�·�ʱ�ĳ�ʼ��ѹ������ȡ20����ѹ�źţ���ƽ������
	{
		sum_U += voltage[i];
	}
	sum_U = sum_U / 20; //����ȡ20����ѹ�ź�
	
	for (int i = 0; i < 90; i++) //ѡ��������������ĵ�ѹ�ź�����30--120������ȡ90����ѹ�ź�
	{
		U2 = voltage[i+30] - sum_U;//�����Ĳ������������ĵ�ѹ�ź�����30--120�ĵ�ѹ���U��
		p2 = p1 * U1 / U2 * t2 / t1;//�����Ĳ������������ĵ�ѹ�ź�����30--120�ĵ�����p2��
		p[i] = p2;   //���еĵ�����ֵ��д�����������P���ж�
	}
	float min = p[0], max = p[0];   //��ʼ�����С������ֵ��ʼ��ֵ
	for (int i = 0; i < 90; i++)
	{
		sum_p += p[i];
		if (p[i] > max)
		{
			max = p[i];
			continue;
		}
		else if (p[i] < min)
		{
			min = p[i];
			continue;
		}
	}
	p[90] = max;       //���ֵ
	p[91] = min;       //��Сֵ
	p[92] = sum_p / 90;//ƽ����
	return p;
}

void dianzulv::SlotDraw()  //��ͼ�ۺ���
{
	draw();  
}




void dianzulv::SlotPN()  //��ͼ�ۺ���
{
	ui.lineEditpn->setText("1");;
}

dianzulv::dianzulv(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	dianzulv::m_dianzulv = this;

	connect(this, SIGNAL(SignDraw()), this, SLOT(SlotDraw()),Qt::BlockingQueuedConnection);
	connect(this, SIGNAL(SignPN()), this, SLOT(SlotPN()), Qt::BlockingQueuedConnection);
	//��þ��  �������Ҫ�ͷ�
	bool flag1 = CBeckOffManage::InitInstance()->Connect("GVL.Array6", lHdlVar1);//

	//ʵ�������ߵĶ���                       //��ѹ
	series = new QSplineSeries();
	chart = new QChart();

	chart->legend()->hide();//����ͼ��
	chart->addSeries(series);//�������
	chart->setTitle("��Ƭ��ѹ�ź�");//����
	//chart->setAnimationOptions(QChart::SeriesAnimations);//�������߳ʶ�����ʾ

	QValueAxis *axisX = new QValueAxis;//X ��
	axisX->setRange(0, 200);//����X�����᷶Χ
	axisX->setTitleText("ɨ�����");//����
	axisX->setLabelFormat("%.0f"); //��ǩ��ʽ��ÿ����λ����0λС��
	axisX->setTickCount(11); //���ָ�������0��200�ֳ�11����λ
	axisX->setMinorTickCount(0); //ÿ����λ֮�������0������
	//axisX->setGridLineVisible(false);//�����Ƿ���ʾ������

	QValueAxis *axisY = new QValueAxis; //Y ��
	axisY->setRange(-3.5, 0.5);//����Y�����᷶Χ

	axisY->setTitleText("��ѹ��V)");//����
	axisY->setLabelFormat("%.4f"); //��ǩ��ʽ��ÿ����λ����4λС��
	axisY->setTickCount(9);//���ָ�������-3.5��0.5�ֳ�9����λ
	axisY->setMinorTickCount(0);//ÿ����λ֮�������0������
	//axisY->setGridLineVisible(false);//�����Ƿ���ʾ������
	series->setPen(QPen(QBrush(Qt::red), 2, Qt::SolidLine));//���������Ŀ�Ⱥ���ɫ�Լ�ʵ����ʾ
	//����ͼ�ε���С���
	chart->setMinimumWidth(400);//��
	chart->setMinimumHeight(280);//��

	chart->setAxisX(axisX, series);//Ϊ��������X��������ʾ
	chart->setAxisY(axisY, series);//Ϊ��������Y��������ʾ
	chart->setAutoFillBackground(true);//���ô����Զ���䱳��
	ui.widget->setChart(chart);//��ӵ���ʾwidget

	//ʵ�������ߵĶ���                       //������
	series2 = new QSplineSeries();
	chart2 = new QChart();

	chart2->legend()->hide();//����ͼ��
	chart2->addSeries(series2);//�������
	chart2->setTitle("��Ƭ������");//����
	chart2->setAnimationOptions(QChart::SeriesAnimations);//�������߳ʶ�����ʾ

	QValueAxis *axisX2 = new QValueAxis;//X ��
	axisX2->setRange(0, 100);//����X�����᷶Χ
	axisX2->setTitleText("ɨ�����");//����
	axisX2->setLabelFormat("%.0f"); //��ǩ��ʽ��ÿ����λ����0λС��
	axisX2->setTickCount(11); //���ָ�������0��100�ֳ�11����λ
	axisX2->setMinorTickCount(0); //ÿ����λ֮�������0������
	//axisX->setGridLineVisible(false);//�����Ƿ���ʾ������

	QValueAxis *axisY2 = new QValueAxis; //Y ��
	axisY2->setRange(0, 6);//����Y�����᷶Χ
	axisY2->setTitleText("�����ʣ���.cm��");//����
	axisY2->setLabelFormat("%.4f"); //��ǩ��ʽ��ÿ����λ����4λС��
	axisY2->setTickCount(7);//���ָ�������0��6�ֳ�7����λ
	axisY2->setMinorTickCount(0);//ÿ����λ֮�������0������
	//axisY2->setGridLineVisible(false);//�����Ƿ���ʾ������
	series2->setPen(QPen(QBrush(Qt::red), 2, Qt::SolidLine));//���������Ŀ�Ⱥ���ɫ�Լ�ʵ����ʾ
	//����ͼ�ε���С���
	chart2->setMinimumWidth(400);//��
	chart2->setMinimumHeight(280);//��

	chart2->setAxisX(axisX2, series2);//Ϊ��������X��������ʾ
	chart2->setAxisY(axisY2, series2);//Ϊ��������Y��������ʾ
	chart2->setAutoFillBackground(true);//���ô����Զ���䱳��
	ui.widget_2->setChart(chart2);//��ӵ���ʾwidget_2


	PLCthread();
}

dianzulv::~dianzulv()
{
	m_plcRun = 0;  //�ȴ��߳�ID
	if (t.joinable())
	{
		t.join();//�ȴ����߳̽���
	}
}