#include "Mag_API.h"
#include <iostream>
using namespace std;



void Mag_API::init()
{
	MagPoint = &ProcessControl;
	MagPoint->init();
	MagPoint = &ResControl;
	MagPoint->init();
	cout << "£ª	Process init is running " << endl;
	return;
}

void Mag_API::cr(char name, int priority)
{
	MagPoint = &ProcessControl;
	MagPoint->cr(name, priority);
	MagPoint = &ResControl;
	MagPoint->cr(name, priority);
	MagPoint->locate_tail();
	MagPoint->disp();
	return;
}

void Mag_API::de(char name)
{
	MagPoint = &ResControl;
	MagPoint->de(name);
	MagPoint = &ProcessControl;
	MagPoint->de(name);
	MagPoint->locate_tail();
	MagPoint->disp();
	return;
}

void Mag_API::req(int RID, int unit)
{
//	int RID;
	PCB * PCBpoint1;
	int PID= RunningQueueHead->RL_next->PID;
	bool flag;
	MagPoint = &ResControl;
	flag=MagPoint->req(RID, unit);
	if (!flag)// if resources are not enough
	{
		MagPoint = &ProcessControl;
		MagPoint->block(RID, unit);
		MagPoint = &ResControl;
		MagPoint->block(RID, unit);
	}
	else
	{
		MagPoint = &ProcessControl;
		MagPoint->req(RID, unit);
	}

	MagPoint->locate_tail();
	MagPoint->disp();
	return;
}

void Mag_API::rel(int RID, int unit)
{
	MagPoint = &ProcessControl;
	MagPoint->rel(RID, unit);
	MagPoint = &ResControl;
	MagPoint->rel(RID, unit);
	MagPoint->locate_tail();
	MagPoint->disp();
	return;
}

void Mag_API::to()
{
	MagPoint = &ResControl;
	MagPoint->to();
	MagPoint = &ProcessControl;
	MagPoint->to();
	MagPoint->locate_tail();
	MagPoint->disp();
	return;
}