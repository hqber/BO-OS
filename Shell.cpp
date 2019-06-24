#include"shell.h"


Shell::Shell()
{
	MandatoryCommands.push_back("init");
	MandatoryCommands.push_back("cr");
	MandatoryCommands.push_back("de");
	MandatoryCommands.push_back("req");
	MandatoryCommands.push_back("rel");
	MandatoryCommands.push_back("to");

	MandatoryCommands.push_back("list ready");
	MandatoryCommands.push_back("list block");
	MandatoryCommands.push_back("list res");

	MandatoryCommands.push_back("pr");

}


Shell::~Shell(){}


void Shell::Shell_Init()
{
	ProcessManager p;
	Shell_Req(1, 8);
	Shell_Req(2, 9);
	Shell_Req(3, 10);
	Shell_Req(4, 11);
	Shell_Cr(0, 0, 1, 1, -1);
	cout << "init process is running"<<endl;
	
}

void Shell::Shell_Cr(PID_TYPE pid, int priority, RID_TYPE NeedResID, unsigned int NeedRes_Num, PID_TYPE Parent_pid)
{
	ProcessManager p;
	p.Create(pid, priority, NeedResID, NeedRes_Num, Parent_pid);
}
void Shell::Shell_De(PID_TYPE pid)
{
	ProcessManager p;
	p.Destroy(pid);
	

}
void Shell::Shell_Req(RID_TYPE rid, unsigned int InitResNum)
{
	ResoureManager r;
	r.Request(rid, InitResNum);
}
void Shell::Shell_Rel(RID_TYPE rid, unsigned int InitResNum)
{
	ResoureManager r;
	r.Release(rid,InitResNum);
}
void Shell::Shell_To(PID_TYPE pid, int priority, int status)
{
	SchedulerManager s(pid,priority,status);
	s.time_out();
}


void Shell::Shell_ListReady()
{
	std::cout << "====等待队列====" << endl;
	for (list<Ready>::iterator ite = Priority_PID_List.begin(); ite != Priority_PID_List.end(); ite++)
	{
		std::cout <<"优先级为:" <<ite->Priority<<endl;
		for (list<PID_Node>::iterator ites = ite->Priority_PID_Queue.begin(); ites != ite->Priority_PID_Queue.end(); ites++)
		{
			std::cout <<"PID:"<< ites->PID <<" Available:"<<ites->Available<<endl;
		}
	}

}
void Shell::Shell_ListBlock()
{
	std::cout << "====阻塞队列====" << endl;
	for (list<Block>::iterator ite = Block_PID_List.begin(); ite != Block_PID_List.end(); ite++)
	{
		std::cout << "PID:" << ite->PID << " Available:" << ite->Available << endl;	
	}

}
void Shell::Shell_ListRes()
{
	std::cout << "====资源列表====" << endl;
	for (list<RCB>::iterator ite = Res_List.begin(); ite != Res_List.end(); ite++)
	{
		std::cout << "资源ID:" << ite->get_rid() << "  等待队列:" << endl;
		
		for (list<Waiting_PID>::iterator waiting_ites = ite->Waiting_List.begin(); waiting_ites != ite->Waiting_List.end(); waiting_ites++)
		{
			std::cout << "PID:" << (ite->Waiting_List).begin()->pid << " Available:" << (ite->Waiting_List).begin()->Available << " 需要资源数:" << (ite->Waiting_List).begin()->NeedResNumber << endl;
		}
		
	}

}

void Shell::Shell_Pr()
{
	int i = 0;
	std::cout << "====所有的PCB====" << endl;
	for (list<PCB>::iterator ite = Pcb_List.begin(); ite != Pcb_List.end(); ite++)
	{
		i++;
		std::cout << "====PCB"<<i<<"====" << endl;
		std::cout << "PID:" << ite->get_pid() << " Available:" << ite->get_available() << endl;
		std::cout << "状态:" << ite->get_status() << " 优先级:" << ite->get_priority() << endl;
		std::cout << "父进程:" << ite->FCTree.Parent_Node << endl;
		std::cout << "子进程:" ;
		for (list<PID_TYPE>::iterator ites = ite->FCTree.Children_Node.begin(); ites != (ite->FCTree.Children_Node).end(); ites++)
		{
			std::cout<< *ites<< endl;
		}
		std::cout << "资源:" ;
		for (int i = 0; i<ite->get_ResNodeVec().size(); i++)
		{
			std::cout << "资源ID:" << (ite->get_ResNodeVec())[i].ResID << " 需资源数:" << (ite->get_ResNodeVec())[i].Res_Num << endl;
		}
		std::cout << "====无屎分割线====" << endl;
	}

}

void Shell::sh(string Commands)
{
	PID_TYPE pid;
	int priority;
	RID_TYPE NeedResID;
	unsigned int NeedRes_Num;
	PID_TYPE Parent_pid;
	RID_TYPE rid;
	unsigned int InitResNum;
	int status;
	
	MandatoryCommands.push_back("de");
	MandatoryCommands.push_back("req");
	MandatoryCommands.push_back("rel");
	MandatoryCommands.push_back("to");

	MandatoryCommands.push_back("list ready");
	MandatoryCommands.push_back("list block");
	MandatoryCommands.push_back("list res");

	MandatoryCommands.push_back("pr");

	


	if (Commands == MandatoryCommands[0])
	{
		Shell_Init();//初始化进程
	}
	else if (Commands == MandatoryCommands[1])
	{
		

		cout << "====创建进程===="<<endl;
		//PID_TYPE pid, int priority, RID_TYPE NeedResID, unsigned int NeedRes_Num, PID_TYPE Parent_pid
		cout << "输入进程ID&优先级|资源ID|资源数|父ID:";
		cin >> pid >> priority >> NeedResID >> NeedRes_Num >> Parent_pid;
		Shell_Cr(pid, priority, NeedResID, NeedRes_Num, Parent_pid);//创建进程
		cout << "====创建进程成功====" << endl;
	}
	else if (Commands == MandatoryCommands[2])
	{
		cout << "====删除进程====" << endl;
		cout << "输入进程ID:";
		cin >> pid;
		Shell_De(pid);//删除进程
		cout << "====删除进程成功====" << endl;
		
	}

	else if (Commands == MandatoryCommands[3])
	{
		cout << "====获取资源====" << endl;
		cout << "输入资源ID&资源初始值:";
		cin >> rid >> InitResNum;
		Shell_Req(rid, InitResNum);//获取资源
		cout << "====获取资源成功====" << endl;
	}

	else if (Commands == MandatoryCommands[4])
	{
		cout << "====释放资源====" << endl;
		cout << "输入资源ID&资源初始值:";
		cin >> rid >> InitResNum;
		Shell_Rel(rid,InitResNum);//释放资源
		cout << "====释放资源成功====" << endl;
	}
	else if (Commands == MandatoryCommands[5])
	{
		cout << "====时间片轮转====" << endl;
		cout << "输入进程ID&进程优先级&进程状态:";
		cin >> pid >> priority >> status;
		Shell_To(pid, priority, status);//时间片轮转
		cout << "====时间片轮转成功====" << endl;
	}
	else if (Commands == MandatoryCommands[6])
	{
		cout << "====查看就绪队列中所有进程====" << endl;
		Shell_ListReady();//查看就绪队列中所有进程
		cout << "====查看就绪队列中所有进程成功====" << endl;
	}
	else if (Commands == MandatoryCommands[7])
	{
		cout << "====查看阻塞队列中所有进程====" << endl;
		Shell_ListBlock();//查看阻塞队列中所有进程
		cout << "====查看阻塞队列中所有进程成功====" << endl;
	}
	else if (Commands == MandatoryCommands[8])
	{
		cout << "====查看所有可用资源====" << endl;
		Shell_ListRes();//查看所有可用资源
		cout << "====查看所有可用资源成功====" << endl;
	}
	else if (Commands == MandatoryCommands[9])
	{
		cout << "====打印释放进程的PCB信息====" << endl;
		Shell_Pr();//打印释放进程的PCB信息
		cout << "====打印释放进程的PCB信息成功====" << endl;
	}
	else
	{
		cout << "请重新输入   作者:世至其美" << endl;
	}

}
