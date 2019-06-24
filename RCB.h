#pragma once
#include<iostream>
#include<list>
#include<algorithm>
#include<string>
using namespace std;
typedef int RID_TYPE;
typedef int PID_TYPE;


class Waiting_PID
{
public:
	PID_TYPE pid;
	bool Available;
	int NeedResNumber;

	Waiting_PID()
	{
		pid = -1;
		Available = true;
		NeedResNumber = 0;
	}
};

class RCB
{
private:
	RID_TYPE RID;//资源ID
	unsigned int Init_Res_Number;//资源初始数量
	unsigned int Usable_Res_Number;//资源可用数量
	
public:
	std::list<Waiting_PID> Waiting_List;//资源等待链表
	RCB(RID_TYPE rid, unsigned int InitResNum)
	{
		RID = rid;
		Init_Res_Number = InitResNum;
		Usable_Res_Number = InitResNum;
		Waiting_PID wp;
		wp.pid = -1;
		wp.NeedResNumber = -1;
		wp.Available = false;
		Waiting_List.push_back(wp);
	}
	RCB(PID_TYPE pid, unsigned int NeedRes_Num, RID_TYPE rid, unsigned int InitResNum)
	{
		RID = rid;
		Init_Res_Number = InitResNum;
		Usable_Res_Number = InitResNum;
		Waiting_PID wp;
		wp.pid = pid;
		wp.NeedResNumber = NeedRes_Num;
		wp.Available = true;
		Waiting_List.push_back(wp);
	}
	RCB(PID_TYPE pid, unsigned int NeedRes_Num, bool Available, RID_TYPE rid, unsigned int InitResNum)
	{
		RID = rid;
		Init_Res_Number = InitResNum;
		Usable_Res_Number = InitResNum;
		Waiting_PID wp;
		wp.pid = pid;
		wp.Available = Available;
		wp.NeedResNumber = NeedRes_Num;
		Waiting_List.push_back(wp);
	}
	void set_rid(RID_TYPE RID){ this->RID = RID; }
	void set_InitResNumber(unsigned int Init_Res_Number){ this->Init_Res_Number = Init_Res_Number; }
	void set_UsableResNumber(unsigned int Usable_Res_Number){ this->Usable_Res_Number = Usable_Res_Number; }
	void add_WaitingList(Waiting_PID waitingNode){ Waiting_List.push_back(waitingNode); }

	RID_TYPE get_rid(){ return RID; }
	unsigned int get_InitResNumber(){ return Init_Res_Number; }
	unsigned int get_UsableResNumber(){ return Usable_Res_Number; }
	
};