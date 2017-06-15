#include "Mag.h"
#include <iostream>
using namespace std;
class ProcessMag :public Mag
{
public:
	void init();
	void cr(char name, int priority);
	void de(char name);
	bool req(int RID,int num);
	void rel(int RID, int num);
	void to();
	void block(int RID, int unit);
private:
	PCB * PCBpprev;
	PCB * PCBpnext;
	RL  * RLpprev;
	RL  * RLpnext;
	int insertPCB(char name, int priority);
	void insertRL(int PID, int priority);            //main insertRL
	void insertRL(int PID, RL * & queue);            //assist insertRL
	void scheduler();

};