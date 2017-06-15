#ifndef MAG
#define MAG

extern struct PCB;
extern struct RCB;
extern struct BL;
extern struct RL * RL_HEAD[3];               //ready list queue
extern struct BL * BL_HEAD;            //blocked list queue
extern struct RL * RL_tail[3];
extern struct BL * BL_tail;
extern struct PCB * PCB_HEAD;
extern struct PCB * PCB_tail;
extern struct RCB * RCB_HEAD;
extern struct RCB * RCB_tail;
extern RL * RunningQueueHead;
extern RL * RunningQueueTail;

struct PCB
{
	int PID;
	char name;
	PCB * PCBnext;
	PCB * PCBprevious;
	int resource[4];
	int WaitResource[4];
	int priority;
};

struct RCB                                       //obiligate for resource allocation in block list
{
	int RID;
	int status;
	RCB * RCBnext;
	RCB * RCBprevious;
};

struct RL                //ready list         run only acording to priority
{
	int PID;
	RL * RL_prev;
	RL * RL_next;
};

struct BL                //block list   interact with RCB
{
	int PID;
	BL * BL_prev;
	BL * BL_next;
};


class Mag                  //abstract to ProcessMag & ResMag
{
protected:

	char getProcessName(int PID);
	int  getPID(char name);
	PCB * getPCBnode(int PID);
	PCB * getPCBnode(char name);
	RCB * getRCBnode(int PID);
	RL * getRLnode(int PID);
	BL * getBLnode(int PID);
	RL * getRLnode(char name);
	BL * getBLnode(char name);
	void CreateBLNode(int PID);
	void DeleteNode(PCB * p);
	void DeleteNode(RL * p);
	void DeleteNode(BL * p);


	//virtual void disp() = 0;

public:
	virtual void init() = 0;
	virtual void cr(char name,  int priority)   = 0;
	virtual void de(char name)   = 0;
	virtual bool req(int PID, int num)  = 0;
	virtual void rel(int PID, int num)  = 0;
	virtual void to()   = 0;
	virtual void block(int RID,int unit)=0;
	void locate_tail();
	void disp();
};

#endif