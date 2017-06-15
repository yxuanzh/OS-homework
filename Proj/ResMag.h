#include "Mag.h"
#include <iostream>
using namespace std;
class ResMag :public Mag
{
public:
	void init();
	void cr(char name, int prioriy);
	void de(char name);
	bool req(int RID, int num);
	void rel(int RID, int num);
	void to();
	void block(int RID, int unit);
	//void MarkSourceRequire(int PID, int RID, int unit);
private:
	RCB * pprev;
	RCB * pnew;
	void createRCB(int RID, int number);
	void FreeResource(int PID);              //free resource for porcesses
	bool getResource(int RID, int num);
	bool getResource(int PID);
	/*     get(num>0) or free(num<0) concrete resources. "1" represents	success and "0"	represents failure  */
	//void disp();
	//int RequiredResource[4];
	void SourceAllocate(int RID,int num);
};

