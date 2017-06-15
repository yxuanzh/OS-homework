#include "Mag.h"
#include <iostream>
using namespace std;

RL * RL_HEAD[3] = { new RL{ NULL },new RL{ NULL },new RL{ NULL } };
RL * RL_tail[3] = { new RL{NULL},new RL{ NULL },new RL{ NULL } };
struct BL * BL_HEAD = new BL{NULL};
struct BL * BL_tail = new BL{NULL};
struct PCB * PCB_HEAD =new PCB{ NULL };
struct PCB * PCB_tail = new PCB{ NULL };
struct RCB * RCB_HEAD = new RCB{ NULL };
struct RCB * RCB_tail = new RCB{ NULL };
RL * RunningQueueHead = NULL;
RL * RunningQueueTail = NULL;


char Mag::getProcessName(int PID)
{
	PCB * p = PCB_HEAD;
	while (p->PID != PID  && p->PCBnext != NULL)
	{
		p = p->PCBnext;
	}
	return p->name;
}

int Mag::getPID(char name)
{
	PCB * p = PCB_HEAD;
	while (p->name != name && p->PCBnext != NULL)
	{
		p = p->PCBnext;
	}
	return p->PID;
}


PCB * Mag::getPCBnode(int PID)
{
	PCB * p = PCB_HEAD;
	while ( p->PID != PID && p->PCBnext !=NULL)
	{
		p = p->PCBnext;
	}
	return p;

}

RCB * Mag::getRCBnode(int RID)
{
	RCB * p = RCB_HEAD;
	while (p->RID != RID && p->RCBnext != NULL)
	{
		p = p->RCBnext;
	}
	if (p->RID == RID)
		return p;
	else
		return NULL;

}

PCB * Mag::getPCBnode(char name)
{
	PCB * p = PCB_HEAD;
	while (p->name != name  && p->PCBnext != NULL)
	{
		p = p->PCBnext;
	}
	if (p->name == name)
		return p;
	else
		return NULL;
}



RL * Mag::getRLnode(int PID)
{
	RL * p = RL_HEAD[2];
	while (p->PID != PID  && p->RL_next != NULL)
	{
		p = p->RL_next;
	}
	if(p->PID==PID)
		return p;


	p = RL_HEAD[1];
	while (p->PID != PID  && p->RL_next != NULL)
	{
		p = p->RL_next;
	}
	if (p->PID == PID)
		return p;


	p = RL_HEAD[0];
	while (p->PID != PID  && p->RL_next != NULL)
	{
		p = p->RL_next;
	}
	if (p->PID == PID)
		return p;
	else
		return NULL;
}


BL * Mag::getBLnode(int PID)
{
	BL * p = BL_HEAD;
	while (p->PID != PID  && p->BL_next != NULL)
	{
		p = p->BL_next;
	}
	if (p->PID == PID)
		return p;
	else
		return NULL;

}

RL * Mag::getRLnode(char name)
{
	int PID;
	PID = getPID(name);
	return getRLnode(PID);
}

BL * Mag::getBLnode(char name)
{
	int PID;
	PID = getPID(name);
	return getBLnode(PID);
}

void Mag::DeleteNode(PCB * p)
{
	p->PCBprevious->PCBnext = p->PCBnext;
	if (p->PCBnext != NULL)
		p->PCBnext->PCBprevious = p->PCBprevious;
	delete p;

	return;
}


void Mag::DeleteNode(RL * p)
{
	if (p != NULL)
	{
		p->RL_prev->RL_next = p->RL_next;
		if (p->RL_next != NULL)
			p->RL_next->RL_prev = p->RL_prev;
		delete p;
	}

	return;
}


void Mag::DeleteNode(BL * p)
{
	p->BL_prev->BL_next = p->BL_next;
	if (p->BL_next != NULL)
		p->BL_next->BL_prev = p->BL_prev;

	delete p;
	return;
}

void Mag::CreateBLNode(int PID)
{
	BL * p;
	p = new BL;
	p->BL_next = NULL;
	BL_tail->BL_next=p;
	p->BL_prev = BL_tail;
	p->PID = PID;
	BL_tail = p;

}


void Mag::locate_tail()
{
	RL *  RL_p= RL_HEAD[0];
	BL *  BL_p=BL_HEAD;
	PCB * PCB_p=PCB_HEAD;
	while (RL_p->RL_next != NULL)
		RL_p = RL_p->RL_next;
	RL_tail[0] = RL_p;


	RL_p = RL_HEAD[1];
	while (RL_p->RL_next != NULL)
		RL_p = RL_p->RL_next;
	RL_tail[1] = RL_p;


	RL_p = RL_HEAD[2];
	while (RL_p->RL_next != NULL)
		RL_p = RL_p->RL_next;
	RL_tail[2] = RL_p;
	
	while (BL_p->BL_next != NULL)
		BL_p = BL_p->BL_next;
	BL_tail= BL_p;

	while (PCB_p->PCBnext != NULL)
		PCB_p = PCB_p->PCBnext;
	PCB_tail = PCB_p;

}

void Mag::disp()
{
	int RunningProcessID;
	char RunningProcessName;
	RunningProcessID = RunningQueueHead->RL_next->PID;
	RunningProcessName = getProcessName(RunningProcessID);
	cout << "Process " << RunningProcessName << " is running" << endl;
}