#include <iostream>
using namespace std;

class user                         //user-oriented API
{
protected:
	virtual void init();
	virtual void cr();
	virtual void de();
	virtual void req();
	virtual void rel();
	virtual void to();
};



class Mag                  //abstract to ProcessMag & ResMag
{
protected:                        //protected public and private?????difference
	struct PCB 
	{
		struct PCB * PCBpoint;

	} ;
	
	typedef struct RCB 
	{
		struct RCB * RCBpoint;
	};
public:
	virtual int init()=0;             //difference between virtual and abstract
	virtual int cr()=0;
	virtual int de()=0;
	virtual int req()=0;
	virtual int rel()=0;
	virtual int to()=0;
};


class ProcessMag:public Mag
{
protected:
	int init()
	{
		
	}

	int cr()
	{
	
	}

	int de()
	{
	
	}

	int req()
	{
	
	}

	int rel()
	{
	
	}

	int to()
	{
	
	}

};

class ResMag :public Mag
{
protected:
	int init()
	{

	}

	int cr()
	{

	}

	int de()
	{

	}

	int req()
	{

	}

	int rel()
	{

	}

	int to()
	{

	}

};