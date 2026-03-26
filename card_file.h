#pragma once
#include"model.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//保存卡
void saveCard(CardNode* newmode);

//读取卡 
void readcard();

//检查卡号是否存在于文件中
int iscardexistinfile(char* cardnumber);
