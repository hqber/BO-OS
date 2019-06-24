#pragma once
#include"RCB.h"
#include"PCB.h"
typedef int RID_TYPE;
typedef int PID_TYPE;

extern list<Ready> Priority_PID_List;
extern list<Block> Block_PID_List;
extern list<RCB> Res_List;
extern list<PCB> Pcb_List;

class ResoureManager
{
public:
	ResoureManager(){};

	~ResoureManager(){};

	void Request(RID_TYPE rid, unsigned int InitResNum);
	void Release(RID_TYPE rid, unsigned int InitResNum);
};

