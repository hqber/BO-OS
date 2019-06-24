#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<list>
#include"ProcessManager.h"
#include"ResoureManager.h"
#include"SchedulerManager.h"
using namespace std;

typedef int RID_TYPE;
typedef int PID_TYPE;

extern list<Ready> Priority_PID_List;
extern list<Block> Block_PID_List;
extern list<RCB> Res_List;
extern list<PCB> Pcb_List;

class Shell
{
public:
	std::vector<std::string>  MandatoryCommands;
	Shell();
	~Shell();

	//进程操作基本命令
	void Shell_Init();//初始化进程
	void Shell_Cr(PID_TYPE pid, int priority, RID_TYPE NeedResID, unsigned int NeedRes_Num, PID_TYPE Parent_pid);//创建进程
	void Shell_De(PID_TYPE pid);//删除进程
	void Shell_Req(RID_TYPE rid, unsigned int InitResNum);//获取资源
	void Shell_Rel(RID_TYPE rid, unsigned int InitResNum);//释放资源
	void Shell_To(PID_TYPE pid, int priority, int status);//时间片轮转
	
	//查看进程状态和资源的命令
	void Shell_ListReady();//查看就绪队列中所有进程
	void Shell_ListBlock();//查看阻塞队列中所有进程
	void Shell_ListRes();//查看所有可用资源
    
	//打印释放进程的PCB信息
	void Shell_Pr();

	void sh(string Commands);

};