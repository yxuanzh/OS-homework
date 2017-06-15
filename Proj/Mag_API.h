#include <iostream>
//#include "user.h"
//#include "Mag.h"
#include "ProcessMag.h"
#include "ResMag.h"
using namespace std; 
class Mag_API                       //cover implement details to users
{
public:
	Mag * MagPoint;
	ProcessMag ProcessControl;
	ResMag ResControl;
	void init();
	void cr(char name,int priority);
	void de(char name);
	void req(int RID, int unit);
	void rel(int RID, int unit);
	void to();







};
