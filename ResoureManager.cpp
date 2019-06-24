#include"ResoureManager.h"

void ResoureManager::Request( RID_TYPE rid, unsigned int InitResNum)
{
	for (list<RCB>::iterator ite=Res_List.begin();ite!= Res_List.end();ite++)
	{
		if (ite->get_rid() == rid)
		{
			cout << "资源已存在,无法申请"<<endl;
			return;
		}
	}
	//申请资源,将新申请的资源放入资源链表中
	RCB RCB_Block(rid, InitResNum);
	Res_List.push_back(RCB_Block);

}

void ResoureManager::Release(RID_TYPE rid, unsigned int InitResNum)
{
	for (list<RCB>::iterator ite = Res_List.begin(); ite != Res_List.end(); ite++)
	{
		if (ite->get_rid() == rid)
		{
			cout << "已成功释放资源" << endl;
			Res_List.erase(ite);
			return;
		}
	}
}