//#include "user.h"
#include "Mag_API.h"
#include <iostream>
using namespace std;

void main()
{
	Mag_API Mag;
	char command[8] = {0};
	char name;
	int ID;
	int num;
	int priority;
	Mag.init();
	while (1)
	{

		cin >> command;
		if (command[0] == 'c' && command[1] == 'r' && command[2] == '\0')
		{
			cin >> name;
			cin >> priority;
			Mag.cr(name, priority);
			name = NULL;
			priority = NULL;
		}
		else if (command[0] == 't' && command[1] == 'o'&& command[2] == '\0')
		{
			Mag.to();
		}

		else if (command[0] == 'd' && command[1] == 'e' && command[2] == '\0')
		{
			cin >> name;
			Mag.de(name);
			name = NULL;
		}

		else if (command[0] == 'r' && command[1] == 'e' && command[2] == 'q'&& command[3] == '\0')
		{
			cin >> ID;
			cin >> num;
			Mag.req(ID, num);
			ID = NULL;
			num = NULL;
		}

		else if (command[0] == 'r' && command[1] == 'e' && command[2] == 'l'&& command[3] == '\0')
		{
			cin >> ID;
			cin >> num;
			Mag.rel(ID, num);
			ID = NULL;
			num = NULL;
		}
		command[0] = NULL;
		command[1] = NULL;
		command[2] = NULL;
		command[3] = NULL;
		command[4] = NULL;
		command[5] = NULL;
		command[6] = NULL;
		command[7] = NULL;


	}

}