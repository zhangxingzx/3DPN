#include "dianzulv.h"
#pragma execution_character_set("utf-8") //Qt中控件中文显示
#include <iostream>
#include "CBeckOffManage.h"   //PLC读写

using namespace std;
dianzulv* dianzulv::m_dianzulv = NULL;

void PLC()
{
	while(dianzulv::m_dianzulv->m_plcRun)
	{
		float Initialvalue[202];
		//获取ads是否通讯成功
		bool flag2 = CBeckOffManage::InitInstance()->GetPLCOnLine();
		//通过句柄读取结构体的值
		bool flag3 = CBeckOffManage::InitInstance()->ReadValue(dianzulv::m_dianzulv->lHdlVar1, sizeof(Initialvalue), &Initialvalue);
		//bool flag3 = CBeckOffManage::InitInstance()->ReadValue(dianzulv::m_dianzulv->lHdlVar1, sizeof(dianzulv::m_dianzulv->voltage), &dianzulv::m_dianzulv->voltage);
		if (Initialvalue[0] == 1)
		{
			emit dianzulv::m_dianzulv->SignPN();   //发送信号
			
		}
		if (Initialvalue[1] == 1)
		{
			for (int i = 0; i < 200; i++)
			{
				dianzulv::m_dianzulv->voltage[i] = Initialvalue[i+2];
			}

			emit dianzulv::m_dianzulv->SignDraw();   //发送信号
			dianzulv::m_dianzulv->find_U(dianzulv::m_dianzulv->voltage);  //电压函数赋值
			dianzulv::m_dianzulv->find_P(dianzulv::m_dianzulv->voltage);  //电阻率函数赋值
		} 
		//通过句柄写入结构体的值
		//bool flag4 = CBeckOffManage::InitInstance()->WriteValue(dianzulv::m_dianzulv->lHdlVar1, sizeof(Initialvalue), &Initialvalue);
	}
	//system("pause");
}

void dianzulv::PLCthread()   //PLC多线程
{
	m_plcRun = 1;
    t=std::thread(PLC);
}

void dianzulv::draw() //绘图
{
	series->setName("spline");
	series2->setName("spline");
	series->clear();
	series2->clear();
	for (int i = 0; i < 200; i++)
	{
	 series->append(i, voltage[i]);//读取电压数据，后面测量数据再运算得到电阻率
	}
	for (int i = 0; i < 90; i++)
	{
		series2->append(i, find_P(voltage)[i]);//读取电阻率数据
	}

	//PLC读取函数得到电压信号数组
	QString strMax_U = QString::number(find_U(voltage)[0], 'f', 4);//电压最大值
	QString strMin_U = QString::number(find_U(voltage)[1], 'f', 4);//电压最小值
	QString strAvg_U = QString::number(find_U(voltage)[2], 'f', 4);//电压平均值
	ui.lineEdit_max_U->setText(strMax_U);
	ui.lineEdit_min_U->setText(strMin_U);
	ui.lineEdit_avg_U->setText(strAvg_U);

	QString strMax_P = QString::number(find_P(voltage)[90], 'f', 4);//电阻率最大值
	QString strMin_P = QString::number(find_P(voltage)[91], 'f', 4);//电阻率最小值
	QString strAvg_P = QString::number(find_P(voltage)[92], 'f', 4);//电阻率平均值
	ui.lineEdit_max_P->setText(strMax_P);
	ui.lineEdit_min_P->setText(strMin_P);
	ui.lineEdit_avg_P->setText(strAvg_P);
}

float* dianzulv::find_U(float voltage[])//初始200个电压数据寻找最大最小值处理函数
{
	float min = voltage[0], max = voltage[0], sum = 0, avg = 0;//初始电压初始赋值
	float vecNum[3];                               //返回最大值、最小值、平均值
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
	vecNum[0] = max;       //最大值
	vecNum[1] = min;     //最小值
	vecNum[2] = sum / m; //平均数
	return vecNum;
}



float* dianzulv::find_P(float voltage[])//初始200个电压数据得到电阻率处理函数
{
	
	float sum_U = 0, sum_p = 0; //初始电压、电阻率值初始赋值
	float U1 = 3.52, p1 = 0.4, t1 = 180;//比较样本的初始电压差U1、电阻率p1、厚度t1；
	float U2, p2, t2=180;//比较样本的初始电压差U2、电阻率p2、厚度t2，实际厚度t2一直变化且通过基恩士传感器获取；
	float p[93];//选取硅片经过探头下方时的电压信号数目计算得到的电阻率数目基础上加上3个（最大值、最小值、平均值）
	for (int i = 0; i < 20; i++)//电阻率需要先采集硅片未经过探头下方时的初始电压（这里取20个电压信号）的平均数；
	{
		sum_U += voltage[i];
	}
	sum_U = sum_U / 20; //这里取20个电压信号
	
	for (int i = 0; i < 90; i++) //选择参与电阻率运算的电压信号区间30--120；这里取90个电压信号
	{
		U2 = voltage[i+30] - sum_U;//保留的参与电阻率运算的电压信号区间30--120的电压差△U；
		p2 = p1 * U1 / U2 * t2 / t1;//保留的参与电阻率运算的电压信号区间30--120的电阻率p2；
		p[i] = p2;   //所有的电阻率值都写入电阻率数组P中判断
	}
	float min = p[0], max = p[0];   //初始最大最小电阻率值初始赋值
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
	p[90] = max;       //最大值
	p[91] = min;       //最小值
	p[92] = sum_p / 90;//平均数
	return p;
}

void dianzulv::SlotDraw()  //绘图槽函数
{
	draw();  
}




void dianzulv::SlotPN()  //绘图槽函数
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
	//获得句柄  句柄不需要释放
	bool flag1 = CBeckOffManage::InitInstance()->Connect("GVL.Array6", lHdlVar1);//

	//实例化画线的对象                       //电压
	series = new QSplineSeries();
	chart = new QChart();

	chart->legend()->hide();//隐藏图例
	chart->addSeries(series);//添加数据
	chart->setTitle("硅片电压信号");//标题
	//chart->setAnimationOptions(QChart::SeriesAnimations);//设置曲线呈动画显示

	QValueAxis *axisX = new QValueAxis;//X 轴
	axisX->setRange(0, 200);//设置X坐标轴范围
	axisX->setTitleText("扫描点数");//标题
	axisX->setLabelFormat("%.0f"); //标签格式：每个单位保留0位小数
	axisX->setTickCount(11); //主分隔个数：0到200分成11个单位
	axisX->setMinorTickCount(0); //每个单位之间绘制了0虚网线
	//axisX->setGridLineVisible(false);//决定是否显示网格线

	QValueAxis *axisY = new QValueAxis; //Y 轴
	axisY->setRange(-3.5, 0.5);//设置Y坐标轴范围

	axisY->setTitleText("电压（V)");//标题
	axisY->setLabelFormat("%.4f"); //标签格式：每个单位保留4位小数
	axisY->setTickCount(9);//主分隔个数：-3.5到0.5分成9个单位
	axisY->setMinorTickCount(0);//每个单位之间绘制了0虚网线
	//axisY->setGridLineVisible(false);//决定是否显示网格线
	series->setPen(QPen(QBrush(Qt::red), 2, Qt::SolidLine));//设置线条的宽度和颜色以及实线显示
	//设置图形的最小宽高
	chart->setMinimumWidth(400);//宽
	chart->setMinimumHeight(280);//高

	chart->setAxisX(axisX, series);//为序列设置X坐标轴显示
	chart->setAxisY(axisY, series);//为序列设置Y坐标轴显示
	chart->setAutoFillBackground(true);//设置窗体自动填充背景
	ui.widget->setChart(chart);//添加到显示widget

	//实例化画线的对象                       //电阻率
	series2 = new QSplineSeries();
	chart2 = new QChart();

	chart2->legend()->hide();//隐藏图例
	chart2->addSeries(series2);//添加数据
	chart2->setTitle("硅片电阻率");//标题
	chart2->setAnimationOptions(QChart::SeriesAnimations);//设置曲线呈动画显示

	QValueAxis *axisX2 = new QValueAxis;//X 轴
	axisX2->setRange(0, 100);//设置X坐标轴范围
	axisX2->setTitleText("扫描点数");//标题
	axisX2->setLabelFormat("%.0f"); //标签格式：每个单位保留0位小数
	axisX2->setTickCount(11); //主分隔个数：0到100分成11个单位
	axisX2->setMinorTickCount(0); //每个单位之间绘制了0虚网线
	//axisX->setGridLineVisible(false);//决定是否显示网格线

	QValueAxis *axisY2 = new QValueAxis; //Y 轴
	axisY2->setRange(0, 6);//设置Y坐标轴范围
	axisY2->setTitleText("电阻率（Ω.cm）");//标题
	axisY2->setLabelFormat("%.4f"); //标签格式：每个单位保留4位小数
	axisY2->setTickCount(7);//主分隔个数：0到6分成7个单位
	axisY2->setMinorTickCount(0);//每个单位之间绘制了0虚网线
	//axisY2->setGridLineVisible(false);//决定是否显示网格线
	series2->setPen(QPen(QBrush(Qt::red), 2, Qt::SolidLine));//设置线条的宽度和颜色以及实线显示
	//设置图形的最小宽高
	chart2->setMinimumWidth(400);//宽
	chart2->setMinimumHeight(280);//高

	chart2->setAxisX(axisX2, series2);//为序列设置X坐标轴显示
	chart2->setAxisY(axisY2, series2);//为序列设置Y坐标轴显示
	chart2->setAutoFillBackground(true);//设置窗体自动填充背景
	ui.widget_2->setChart(chart2);//添加到显示widget_2


	PLCthread();
}

dianzulv::~dianzulv()
{
	m_plcRun = 0;  //等待线程ID
	if (t.joinable())
	{
		t.join();//等待子线程结束
	}
}