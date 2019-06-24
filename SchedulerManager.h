#pragma once
#include"RCB.h"
#include"PCB.h"

extern list<Ready> Priority_PID_List;
extern list<Block> Block_PID_List;
extern list<RCB> Res_List;
extern list<PCB> Pcb_List;

class SchedulerManager
{
	PID_TYPE PID;
	int priority;
	int Status; //½ø³Ì×´Ì¬(0:ready 1:blocked 2:running)
public:
	void Scheduler();
	void time_out();
	

	SchedulerManager(PID_TYPE pid, int priority, int status)
	{
		this->PID = pid;
		this->priority = priority;
		this->Status = status;
	}
	void set_pid(PID_TYPE PID){ this->PID = PID; }
	void set_priority(int Priority){ this->priority = Priority; }
	void set_status(int Status){ this->Status = Status; }

	PID_TYPE get_pid(){ return PID; }
	int get_priority(){ return priority; }
	int get_status(){ return Status; }
};
