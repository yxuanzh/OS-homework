#include <iostream>
#include "ResMag.h"

using namespace std;

void ResMag::createRCB(int RID, int number)
{
	pnew = new RCB;
	pprev->RCBnext = pnew;
	pnew->RCBprevious = pprev;
	pnew->RCBnext = NULL;
	pnew->RID = RID;
	pnew->status = number;
	pprev = pnew;



}


void ResMag::init()
{
	RCB_HEAD->RCBprevious = NULL;     //just used for a head without any concrete function
	RCB_HEAD->RCBnext = NULL;
	RCB_HEAD->RID = 0;
	RCB_HEAD->status = 0;
	pprev = RCB_HEAD;
	createRCB(1, 1);
	createRCB(2, 2);
	createRCB(3, 3);
	createRCB(4, 4);
}

void ResMag::cr(char name, int priority)
{
	//int PID;
	//bool flag;
	//PID=getPID(name);
	//flag = getResource(PID);
	//return flag;
}

void ResMag::de(char name)
{
	FreeResource(getPID(name));
}

bool ResMag::req(int RID, int num)
{
	bool flag;
	PCB * p;
	flag=getResource(RID, num);
	if (flag)
	{
		p=getPCBnode(RunningQueueHead->RL_next->PID);
		p->resource[RID - 1] += num;
	}
	//else
	//	p->resource[RID - 1] -= num

	return flag;
}

void ResMag::rel(int RID, int num)
{
	PCB * p;
	getResource(RID,-1* num);
	p = getPCBnode(RunningQueueHead->PID);
	p->resource[RID - 1] += num;
	getRCBnode(RID)->status += num;
	SourceAllocate(RID, num);
}


void ResMag::SourceAllocate(int RID,int num)
{
	PCB * PCBp;
	BL * BLp = BL_HEAD->BL_next;
	int PID;
	while (BLp != NULL)
	{
		PCBp=getPCBnode(BLp->PID);
		if (PCBp->WaitResource[RID - 1] < 0)
		{
			PCBp->WaitResource[RID - 1]+=num;
			getRCBnode(RID)->status -= num;
			if (PCBp->WaitResource[RID - 1] < 0)
			{
				break;
			}
			else
			{
				num = PCBp->WaitResource[RID - 1];
				PCBp->WaitResource[RID - 1] = 0;
				getRCBnode(RID)->status += num;
			}
		
		}
		BLp = BLp->BL_next;
	
	}

}

void ResMag::to()
{
	RL * p= RunningQueueHead;
	//FreeResource(p->RL_next->PID);
}


void ResMag::FreeResource(int PID)
{
	PCB * PCBnode_point;
	PCBnode_point=getPCBnode(PID);
	getResource(1, -1 * PCBnode_point->resource[0]);
	getResource(2, -1 * PCBnode_point->resource[1]);
	getResource(3, -1 * PCBnode_point->resource[2]);
	getResource(4, -1 * PCBnode_point->resource[3]);
}

bool ResMag::getResource(int PID)
{
	PCB * PCBnode_point;
	bool b1, b2, b3, b4;
	PCBnode_point = getPCBnode(PID);

	b1=getResource(1, PCBnode_point->resource[0]);
	b2=getResource(2, PCBnode_point->resource[1]);
	b3=getResource(3, PCBnode_point->resource[2]);
	b4=getResource(4, PCBnode_point->resource[3]);
	return b1*b2*b3*b4;
}

bool ResMag::getResource(int RID, int num)
{
	RCB * p = getRCBnode(RID);
	int status= p->status;
	if (num <= p->status)
	{

		p->status = status- num;
		return 1;
	}
	else
		return 0;
}


//void ResMag::disp()
//{
//
//
//}

void ResMag::block(int RID, int unit)
{
	BL * BLp;
	PCB *PCBp;
	int PID;
	PID = RunningQueueHead->PID;
	BLp = getBLnode(PID);
	PCBp = getPCBnode(PID);
	PCBp->WaitResource[RID - 1] -= unit;
	//MarkSourceRequire(PID, RID, unit);
	locate_tail();
}

//void ResMag::MarkSourceRequire(int PID, int RID, int unit)
//{
//	PCB * PCBpoint=getPCBnode(PID);
//	PCBpoint->resource[RID - 1] = -1 * unit;
//
//}