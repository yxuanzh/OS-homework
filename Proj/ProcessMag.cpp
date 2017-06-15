#include "ProcessMag.h"
#include <iostream>
using namespace std;

int ProcessMag::insertPCB(char name, int priority)
{
	PCBpnext = new PCB;
	PCBpprev = PCB_tail;
	PCBpprev->PCBnext = PCBpnext;
	PCBpnext->PCBprevious = PCBpprev;
	PCBpnext->PID = PCBpprev->PID + 1;
	PCBpnext->PCBnext = NULL;
	PCBpnext->priority = priority;
	PCBpnext->name = name;
	PCBpnext->resource[0] = 0;
	PCBpnext->resource[1] = 0;
	PCBpnext->resource[2] = 0;
	PCBpnext->resource[3] = 0;
	PCBpnext->WaitResource[0] = 0;
	PCBpnext->WaitResource[1] = 0;
	PCBpnext->WaitResource[2] = 0;
	PCBpnext->WaitResource[3] = 0;
	PCB_tail = PCBpnext;
	return PCBpnext->PID;
}

void ProcessMag::insertRL(int PID, RL * & queuetail)          //assist insertRL
{
	RLpnext = new RL;
	RLpprev = queuetail;
	RLpprev->RL_next = RLpnext;
	RLpnext->PID = PID;
	RLpnext->RL_next = NULL;
	RLpnext->RL_prev = RLpprev;
	queuetail = RLpnext;
}

void ProcessMag::insertRL(int PID, int priority)              //main insertRL
{
	switch (priority)
	{

	case 0: insertRL(PID, RL_tail[0]);
		break;
	case 1: insertRL(PID, RL_tail[1]);
		break;
	case 2: insertRL(PID, RL_tail[2]);
		break;
	case 3: insertRL(PID, RL_tail[3]);
		break;
	}

}

void ProcessMag::init()
{
	int PID;
	/*******************                    PCB HEAD node init                      ******************/
	PCB_HEAD->PID = NULL;
	PCB_HEAD->PCBprevious = NULL;
	PCB_HEAD->PCBnext = NULL;
	PCB_HEAD->priority = NULL;
	PCB_HEAD->name = NULL;    //head node
	PCB_HEAD->resource[0] = NULL;
	PCB_HEAD->resource[1] = NULL;
	PCB_HEAD->resource[2] = NULL;
	PCB_HEAD->resource[3] = NULL;
	PCB_HEAD->WaitResource[0] = NULL;
	PCB_HEAD->WaitResource[1] = NULL;
	PCB_HEAD->WaitResource[2] = NULL;
	PCB_HEAD->WaitResource[3] = NULL;
	PCBpprev = PCB_HEAD;
	PCB_tail = PCBpprev;

	/*******************                    RL HEAD node init                      ******************/
	RL_HEAD[0]->PID = NULL;
	RL_HEAD[1]->PID = NULL;
	RL_HEAD[2]->PID = NULL;
	RL_HEAD[0]->RL_prev = NULL;
	RL_HEAD[1]->RL_prev = NULL;
	RL_HEAD[2]->RL_prev = NULL;
	RL_HEAD[0]->RL_next = NULL;
	RL_HEAD[1]->RL_next = NULL;
	RL_HEAD[2]->RL_next = NULL;
	RL_tail[0] = RL_HEAD[0];
	RL_tail[1] = RL_HEAD[1];
	RL_tail[2] = RL_HEAD[2];


	PID = insertPCB('R', 0);       //root process init
             
	insertRL(PID, 0);             //insert  root process in RL
	

}

void ProcessMag::cr(char name, int priority)
{
	int PID;
	PID = insertPCB(name, priority);
	insertRL(PID, priority);
	locate_tail();
	scheduler();
}

void ProcessMag::de(char name)
{
	PCB * PCBnode_point;
	RL * RLnode_point;
	BL * BLnode_point;
//	int PID;
	PCBnode_point = getPCBnode(name);
	RLnode_point  = getRLnode (name);
	BLnode_point  = getBLnode (name);
//	if (PCBnode_point->PID!=0 && PCBnode_point != NULL)	
	if (RLnode_point != NULL)
		DeleteNode(RLnode_point);
	if (BLnode_point != NULL)
		DeleteNode(BLnode_point);
	if (PCBnode_point != NULL)
		DeleteNode(PCBnode_point);
//	if (RLnode_point->PID != 0 && RLnode_point!=NULL)

//	if (BLnode_point->PID != 0 && BLnode_point != NULL)

	locate_tail();
	scheduler(); 

}

bool ProcessMag::req(int RID, int num)
{
	scheduler();
	return 1;
}

void ProcessMag::rel(int RID, int num)
{
	PCB * PCBp;
	BL * BLp = BL_HEAD->BL_next;
	BL * BLp2;
	while (BLp != NULL)
	{
		PCBp = getPCBnode(BLp->PID);
		BLp2 = BLp->BL_next;
		if (PCBp->WaitResource[RID - 1] == 0)
		{
			insertRL(PCBp->PID, PCBp->priority);
			DeleteNode(BLp);
		}
		BLp = BLp2;
	}
	locate_tail();
	scheduler();
}

void ProcessMag::to()
{
	locate_tail();
	if (RunningQueueHead->RL_next != NULL)
	{
		RunningQueueTail->RL_next = RunningQueueHead->RL_next;
		RunningQueueHead->RL_next = RunningQueueHead->RL_next->RL_next;
		RunningQueueTail->RL_next->RL_prev = RunningQueueTail;
		RunningQueueTail->RL_next->RL_next = NULL;
		RunningQueueHead->RL_next->RL_prev = RunningQueueHead;
		RunningQueueTail = RunningQueueTail->RL_next;
	}

}

void ProcessMag::scheduler()
{

	if (RL_HEAD[2]->RL_next != NULL)
	{
		RunningQueueHead = RL_HEAD[2];
		RunningQueueTail = RL_tail[2];
	}
	else if (RL_HEAD[1]->RL_next != NULL)
	{
		RunningQueueHead = RL_HEAD[1];
		RunningQueueTail = RL_tail[1];
	}

	else if (RL_HEAD[0]->RL_next != NULL)
	{
		RunningQueueHead = RL_HEAD[0];
		RunningQueueTail = RL_tail[0];
	}

	else
	{
		RunningQueueHead = NULL;
		RunningQueueTail = NULL;
	}



}




void ProcessMag::block(int RID, int unit)
{
	int PID;
	PID = RunningQueueHead->RL_next->PID;
	DeleteNode(getRLnode(PID));
	CreateBLNode(PID);
	locate_tail();
	scheduler();
}



