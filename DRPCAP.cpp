
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include "DLogger.h"

using namespace std;

bool g_MainLoopRun = true;

void siginthandler(int param)
{
	g_MainLoopRun = false;
}

int main()
{
	cout << "DR started" << endl;
	signal (SIGINT, siginthandler);

	DLogger* pDlogger = new DLogger();

	do
	{
	    usleep(500000); // 500 milliseconds (500,000 microseconds)
	    //as long as this value is true we keep running
	 }

	while(g_MainLoopRun == true);

	delete pDlogger;

	cout << "DR ended" << endl;

	return 0;
}
