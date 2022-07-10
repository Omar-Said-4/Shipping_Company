#include<iostream>
#include<fstream>
#include"Company.h"
#include"PriorityQueue.h"
using namespace std;
int main()
{
	Company test("test5.txt");
	test.Update();
	return 0;

	
	//CARGOS
	//	------
	//	VIP(80cost + 50dist + (24days + hours))//
	//	LOADING -(loadstartdateinhours + maxloadingtime)//___________________________________
	//	MOVING -(movestartinhours + deldist/speed + loadingtime)//





	
	//	TRUCKS
	//	------
	//	CHECKUP -(starttimeinhours + maintinencetime)//
	//	LOADING -(loadstartdateinhours + maxloadingtime)//__________________________________

	//	MOVING -(movestartinhours + (2 * deldistmax)/speed + loadingtime(i >>> n))//
	//												_______

}