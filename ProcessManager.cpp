#include"ProcessManager.h"
//检查是否有已存在的PCB
bool ProcessManager::Exist_PCB(PID_TYPE pid)
{ 
	bool flag = false;
	for (list<PCB>::iterator ite = Pcb_List.begin(); ite != Pcb_List.end(); ite++)
	{
		if ((ite->get_pid() == pid) && (ite->get_available() == true))//已存在且有效
		{
			flag=true;
		}
	}
	return flag;
}

bool Ascending(const Ready &Ready1, const Ready &Ready2)
{
	return (Ready1.Priority<Ready2.Priority);
}


//检查是否已存在优先级队列
bool  ProcessManager::Exist_Priority(PID_TYPE pid, int priority)
{
	bool P_FLAG = false;
	for (list<Ready>::iterator ite = Priority_PID_List.begin(); ite != Priority_PID_List.end(); ite++)
	{
		if (ite->Priority == priority && (ite->Priority_PID_Queue.begin()->PID != -1))//已存在的优先级队列,PID!=-1
		{
			PID_Node pid_Node;
			pid_Node.PID = pid;
			pid_Node.Available = true;
			ite->Priority_PID_Queue.push_back(pid_Node);
			P_FLAG = true;
			break;
		}
		else if (ite->Priority == priority && (ite->Priority_PID_Queue.begin()->PID == -1))//已存在的优先级队列,PID=-1
		{
			ite->Priority_PID_Queue.begin()->PID = pid;
			ite->Priority_PID_Queue.begin()->Available = true;
			P_FLAG = true;
			break;
		}
	}
	if (false == P_FLAG)//不存在的优先级队列
	{
		Ready Ready_List;
		Ready_List.Priority = priority;
		PID_Node pid_Node;
		pid_Node.PID = pid;
		pid_Node.Available = true;
		Ready_List.Priority_PID_Queue.push_back(pid_Node);//将pid加入到优先级队列
		Priority_PID_List.push_back(Ready_List);//将优先级队列加到链表里
		Priority_PID_List.sort(Ascending);
	}
	return true;
}

//检查是否是已存在的资源
bool  ProcessManager::Exist_RES(PID_TYPE pid,RID_TYPE NeedResID, unsigned int NeedRes_Num)
{
	bool R_FLAG = false;
	for (list<RCB>::iterator ite = Res_List.begin(); ite != Res_List.end(); ite++)
	{
		if (ite->get_rid() == NeedResID)//已存在的资源链表
		{
			Waiting_PID wp;
			wp.pid = pid;
			wp.NeedResNumber = NeedRes_Num;
			wp.Available = true;
			ite->add_WaitingList(wp);
			R_FLAG = true;
			break;
		}
	}
	if (false == R_FLAG)//不存在的资源链表
	{
		RCB tempRCB(pid, NeedRes_Num, NeedResID, NeedRes_Num);
		Res_List.push_back(tempRCB);

	}

	return true;
}


//从PCB链表中删除PCB
bool  ProcessManager::Del_PCB(PID_TYPE pid)
{
	bool flag = false;
	for (list<PCB>::iterator ite_pcb = Pcb_List.begin(); ite_pcb != Pcb_List.end(); ite_pcb++)
	{

		if ((ite_pcb->get_pid() == pid) && (ite_pcb->get_available() == true))//已存在且有效
		{
			Pcb_List.erase(ite_pcb);
			flag = true;
			break;
		}
		
	}
	return flag;
}

//从优先级表删除进程节点
bool ProcessManager::Del_PL_Proc_Node(PID_TYPE pid)
{
	bool flag=false;
	int priority=0;
	for (list<PCB>::iterator ite_pcb = Pcb_List.begin(); ite_pcb != Pcb_List.end(); ite_pcb++)
	{

		if ((ite_pcb->get_pid() == pid) && (ite_pcb->get_available() == true))//已存在且有效
		{
			priority = ite_pcb->get_priority();
			break;
		}

	}

	for (list<Ready>::iterator ite = Priority_PID_List.begin(); ite != Priority_PID_List.end(); ite++)
	{
		if (ite->Priority == priority)//已存在的优先级队列
		{
			for (list<PID_Node>::iterator ite_Queue_Node = (ite->Priority_PID_Queue).begin(); ite_Queue_Node != (ite->Priority_PID_Queue).end(); ite_Queue_Node++)
			{
				if ((ite_Queue_Node->PID == pid)&&(ite_Queue_Node->Available==true))
				{
					(ite->Priority_PID_Queue).erase(ite_Queue_Node);
					flag = true;
					break;
				}
			}
			break;
		}
	}
	return flag;
}

//从等待队列删除进程节点
bool ProcessManager::Del_BL_Proc_Node(PID_TYPE pid)
{
	bool flag = false;
	for (list<Block>::iterator ite = Block_PID_List.begin(); ite != Block_PID_List.end(); ite++)
	{
		if ((ite->PID == pid) && (ite->Available == true))//已存在且有效
		{
			Block_PID_List.erase(ite);
			flag = true;
			break;
		}
	}
	return flag;
}


//从资源队列删除进程节点
bool ProcessManager::Del_RCB_WaitingNode(PID_TYPE pid)
{
	list<PCB>::iterator ite_pcb;
	for (list<PCB>::iterator ite = Pcb_List.begin(); ite != Pcb_List.end(); ite++)
	{
		if ((ite->get_pid() == pid) && (ite->get_available() == true))//已存在且有效
		{
			ite_pcb = ite;
			break;
		}
	}

	for (list<RCB>::iterator ite = Res_List.begin(); ite != Res_List.end(); ite++)
	{
		for (vector<R_Node>::iterator ite_res_vec = (ite_pcb->get_ResNodeVec()).begin(); ite_res_vec != (ite_pcb->get_ResNodeVec()).end(); ite_res_vec++)
		{
			if (ite->get_rid() == ite_res_vec->ResID)//存在的资源ID
			{
				for (list<Waiting_PID>::iterator ite_res_Node = (ite->Waiting_List).begin(); ite_res_Node != (ite->Waiting_List).end(); ite_res_Node++)
				{
					if ((ite_pcb->get_pid() == ite_res_Node->pid)&&(ite_res_Node->Available==true))
					{
						(ite->Waiting_List).erase(ite_res_Node);
					}
				}
			}
		}

	}
	return true;
}


bool ProcessManager::Create(PID_TYPE pid, int priority, RID_TYPE NeedResID, unsigned int NeedRes_Num, PID_TYPE Parent_pid)
{
	//检查是否有已存在的PCB
    if (true == Exist_PCB(pid))
	{
		cout << "PCB Block已存在,请重新创建" << endl;
	}
	//新建进程，初始化PCB  
	PCB Proc(pid, NeedResID, NeedRes_Num, priority, Parent_pid);  
	Pcb_List.push_back(Proc);

	//检查是否已存在优先级队列
	Exist_Priority(pid, priority);
	
	//检查是否是已存在的资源
	Exist_RES(pid, NeedResID, NeedRes_Num);
	

	return true;
}

bool ProcessManager::Destroy(PID_TYPE pid)
{
	//从PCB表中删除PCB
	KillTree(pid);

	//从优先级表删除进程节点
	Del_PL_Proc_Node(pid);

	//从等待队列删除进程节点
	Del_BL_Proc_Node(pid);

	//从RCB表中删除等待进程节点
	Del_RCB_WaitingNode(pid);
	return true;
}

bool ProcessManager::KillTree(PID_TYPE pid)
{
	//从PCB链表中查找PCB block
	for (list<PCB>::iterator ite = Pcb_List.begin(); ite != Pcb_List.end(); ite++)
	{

		if ((ite->get_pid() == pid) && (ite->get_available() == true))//已存在且有效
		{
			for (list<PID_TYPE>::iterator ite_Child_Node = (ite->FCTree).Children_Node.begin(); ite_Child_Node != (ite->FCTree).Children_Node.end(); ite_Child_Node++)
			{
				if (-1 != (((ite->FCTree).Children_Node).front()))
				{
					for (list<PID_TYPE>::iterator ite_list = (((ite->FCTree).Children_Node).begin()); ite_list != (((ite->FCTree).Children_Node).end()); ite_list++)//如果有子节点树，先进行释放
					{
						KillTree(pid);
					}
				}
				
			}
			Del_PCB(pid);
			break;
		}
	}

	return true;
}