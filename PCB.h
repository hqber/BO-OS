#pragma once

#include<iostream>
#include<list>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
typedef int PID_TYPE;
typedef int RID_TYPE;


class P_Tree
{
public:
	PID_TYPE Parent_Node;
	list<PID_TYPE> Children_Node;
};
class R_Node
{
public:
	RID_TYPE ResID;//需要申请的资源
	unsigned int Res_Num;//需要申请的资源

	R_Node()
	{
		ResID = -1;
		Res_Num = 0;
	} 
};

class PID_Node
{
public:
	PID_TYPE PID;
	bool Available;//是否有效
	PID_Node()
	{
		PID = -1;
		Available = true;
	}
};

class Block
{
public:
	PID_TYPE PID;
	bool Available;//是否有效
	Block()
	{
		PID = -1;
		Available = true;
	}
};

class Ready
{
public:
	int Priority;
	list<PID_Node> Priority_PID_Queue;
};

class PCB
{
private:
	PID_TYPE PID;//进程id
	bool Available;//是否有效
	vector<R_Node> Res_Node_vec;
	int Status; //进程状态(0:ready 1:blocked 2:running)
	
	int Priority;//优先级

public:
	P_Tree FCTree;//父子树
	PCB(PID_TYPE pid, int priority)
	{
		PID = pid;
		Available = true;
		R_Node tempRN;
		Res_Node_vec.push_back(tempRN);
		Status = 0;
		FCTree.Parent_Node = -1;
		FCTree.Children_Node.push_back(-1);
		Priority = priority;

	}
	PCB(PID_TYPE pid, RID_TYPE resId, int priority)
	{
		PID = pid;
		Available = true;
		R_Node tempRN;
		tempRN.ResID = resId;
		Res_Node_vec.push_back(tempRN);
		Status = 0;
		FCTree.Parent_Node = -1;
		FCTree.Children_Node.push_back(-1);
		Priority = priority;
		
	}
	PCB(PID_TYPE pid, RID_TYPE resId, int resNum, int priority)
	{
		PID = pid;
		Available = true;
		R_Node tempRN;
		tempRN.ResID = resId;
		tempRN.Res_Num = resNum;
		Res_Node_vec.push_back(tempRN);
		Status = 0;
		FCTree.Parent_Node = -1;
		FCTree.Children_Node.push_back(-1);
		Priority = priority;

	}
	PCB(PID_TYPE pid, RID_TYPE resId, int resNum, int priority, PID_TYPE Parent_pid)
	{
		PID = pid;
		Available = true;
		R_Node tempRN;
		tempRN.ResID = resId;
		tempRN.Res_Num = resNum;
		Res_Node_vec.push_back(tempRN);
		Status = 0;
		FCTree.Parent_Node = Parent_pid;
		FCTree.Children_Node.push_back(-1);
		Priority = priority;

	}
	~PCB(){}

	void set_pid(PID_TYPE PID){ this->PID = PID; }
	void set_available(bool Available){ this->Available = Available; }
	void add_ResNodeVec(R_Node Res_Node){ this->Res_Node_vec.push_back(Res_Node); }
	void set_status(int Status){ this->Status = Status; }
	void set_FCTree(P_Tree FCTree){ this->FCTree = FCTree; }
	void set_priority(int Priority){ this->Priority = Priority; }

	PID_TYPE get_pid(){ return PID; }
	bool get_available(){ return Available; }
	vector<R_Node> get_ResNodeVec(){ return Res_Node_vec; }
	int get_status(){ return Status; }
	
	int get_priority(){ return Priority; }

};

