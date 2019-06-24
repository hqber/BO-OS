#include<iostream>
#include<string>
#include<list>
#include"shell.h"
#include"ProcessManager.h"
#include"ResoureManager.h"
#include"SchedulerManager.h"

using namespace std;


list<Ready> Priority_PID_List;//就绪队列
list<Block> Block_PID_List;//阻塞队列
list<RCB> Res_List;//资源链表
list<PCB> Pcb_List;//PCB链表


int main()
{
	ResoureManager RM;
	Shell shell;
	shell.Shell_Init();
	string Commands;
	while (getline(cin, Commands))
	{
		
		shell.sh(Commands);
		cin.sync();

	}
	return 0;
}