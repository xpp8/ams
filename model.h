#pragma once
#include<time.h>
//卡信息
typedef struct Card
{
	char aName[20];		//卡号
	char aPaws[10];		//密码
	int nStatus;		//卡的状态（0-未上机；1-正在上机；2；已注销；3-失效）
	time_t tStart;		//开卡时间
	time_t tEnd;		//卡的截止时间
	float fTotalUse;	//累计金额
	time_t tLast;		//最后使用时间
	int nUseCount;		//使用次数
	float fBalance;		//余额
	int nDel;			//删除表示标识 0-未删除，1-删除
}Card;

//链表节点定义
typedef struct CardNode {
	struct CardNode* next;
	Card data;
}CardNode;

extern CardNode* head;