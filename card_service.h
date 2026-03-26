#pragma once
#include"model.h"
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
//添加卡
void add();

//查询卡
void searchcard();

//检查卡号是否存在于文件中
int iscardexistinfile(char* cardnumber);

//创建新节点
CardNode* createnode();

//添加节点到链表末尾
void addnode(CardNode* newnode);

//根据节点查找卡号
CardNode* findcardbyname(char* name);

//删除节点
int deletenode(char* name);

//释放链表
void freelist();