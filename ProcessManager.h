#pragma once
#include"PCB.h"
#include"RCB.h"
#include"ResoureManager.h"

extern list<Ready> Priority_PID_List;
extern list<Block> Block_PID_List;
extern list<RCB> Res_List;
extern list<PCB> Pcb_List;


class ProcessManager
{
public:
	//创建进程
	bool Create(PID_TYPE pid, int priority, RID_TYPE NeedResID, unsigned int NeedRes_Num, PID_TYPE Parent_pid);
	//释放进程
	bool Destroy(PID_TYPE pid);
	//杀掉子进程
	bool KillTree(PID_TYPE pid);

	
	bool Exist_PCB(PID_TYPE pid);//检查是否有已存在的PCB
	bool Exist_Priority(PID_TYPE pid, int priority);//检查是否已存在优先级队列
	bool Exist_RES(PID_TYPE pid, RID_TYPE NeedResID, unsigned int NeedRes_Num);//检查是否是已存在的资源
	
	bool Del_PCB(PID_TYPE pid);//从PCB链表中删除PCB
	bool Del_PL_Proc_Node(PID_TYPE pid);//从优先级链表删除进程节点
	bool Del_BL_Proc_Node(PID_TYPE pid);//从等待队列删除进程节点
	bool Del_RCB_WaitingNode(PID_TYPE pid);//从资源队列删除进程节点
};
