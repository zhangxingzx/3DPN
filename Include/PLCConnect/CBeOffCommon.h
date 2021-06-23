#pragma once

#ifdef CBEOFF_EXPORTS
#define CBEOFF_API __declspec(dllimport)
#else
#define CBEOFF_API __declspec(dllexport)
#endif


struct PlcVarstruct1	//"CV_GVL.CV_FP"
{
	signed char sc64Cap;
	unsigned int ui64ID;
	double dXOffect;
	double dYOffect;
	double dROffect;
};

struct PlcVarstruct2	//"CV_GVL.CV_WDD"/"CV_GVL.CV_CP"/"CV_GVL.CV_SDD"
{
	unsigned char sc64Cap;
	unsigned int ui64ID;
};
