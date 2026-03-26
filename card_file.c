#include"menu.h"
#include"model.h"
#include"card_file.h"
extern CardNode* head;
#include<stddef.h>
#include"card_service.h"

//保存卡
void saveCard(CardNode* newnode) {
	FILE* fp = fopen("cards.txt", "a");
	if (fp == NULL) {
		printf("无法打开文件进行保存！\n");
		return;
	}
		char tstartstr[20], tendstr[20], tlaststr[20];
		struct tm* tStart = localtime(&newnode->data.tStart);
		strftime(tstartstr, sizeof(tstartstr), "%Y-%m-%d %H:%M:%S", tStart);
		struct tm* tEnd = localtime(&newnode->data.tEnd);
		strftime(tendstr, sizeof(tendstr), "%Y-%m-%d %H:%M:%S", tEnd);
		struct tm* tLast = localtime(&newnode->data.tLast);
		strftime(tlaststr, sizeof(tlaststr), "%Y-%m-%d %H:%M:%S", tLast);
		fprintf(fp, "%s##%s##%d##%s##%s##%.1f##%s##%d##%.1f##%d",
			newnode->data.aName,
			newnode->data.aPaws,
			newnode->data.nStatus,
			tstartstr,
			tendstr,
			newnode->data.fTotalUse,
			tlaststr,
			newnode->data.nUseCount,
			newnode->data.fBalance,
			newnode->data.nDel);
		fprintf(fp, "\n");
	fclose(fp);
}

////读取卡
//int  readcard() {
//	FILE* fp = fopen("cards.txt", "r");
//	if (fp == NULL){
//		printf("文件无法打开！\n");
//			return 0;
//		}
//	int count = 0;
//	char line[256];
//	while (fgets(line,sizeof(line),fp)!=NULL) {
//		CardNode* newnode = createnode();
//		printf("newnode = %p, aName = %p\n", (void*)newnode, (void*)newnode->data.aName);
//		if (newnode==NULL) {
//			fclose(fp);
//			return -1;
//		}
//		char name[20], paw[10], tstartstr[20], tendstr[20], tlaststr[20];
//		int nStatus, nUseCount, nDel;
//		float fTotalUse, fBalance;
//		int n = sscanf_s(line, "%19[^#]##%9[^#]##%d##%19[^#]##%19[^#]##%f##%19[^#]##%d##%f##%d",
//			name, (unsigned)_countof(name), paw, (unsigned)_countof(paw), &nStatus,
//			tstartstr, (unsigned)_countof(tstartstr), tendstr, (unsigned)_countof(tendstr),
//			&fTotalUse, tlaststr, (unsigned)_countof(tlaststr), &nUseCount, &fBalance, &nDel);
//		if (n == 10) {
//			printf("10项数据成功读取！\n");
//			strcpy_s(newnode->data.aName, sizeof(newnode->data.aName), name);
//			strcpy_s(newnode->data.aPaws, sizeof(newnode->data.aPaws), paw);
//			struct tm tstart = { 0 }, tend = { 0 }, tlast = { 0 };
//			sscanf_s(tstartstr, "%d-%d-%d %d:%d:%d", &tstart.tm_year, &tstart.tm_mon, &tstart.tm_mday, &tstart.tm_hour, &tstart.tm_min, &tstart.tm_sec);
//			sscanf_s(tendstr, "%d-%d-%d %d:%d:%d", &tend.tm_year, &tend.tm_mon, &tend.tm_mday, &tend.tm_hour, &tend.tm_min, &tend.tm_sec);
//			sscanf_s(tlaststr, "%d-%d-%d %d:%d:%d", &tlast.tm_year, &tlast.tm_mon, &tlast.tm_mday, &tlast.tm_hour, &tlast.tm_min, &tlast.tm_sec);
//			tstart.tm_year -= 1900; tend.tm_year -= 1900; tlast.tm_year -= 1900;
//			tstart.tm_mon -= 1; tend.tm_mon -= 1; tlast.tm_mon -= 1;
//			newnode->data.nStatus = nStatus;
//			newnode->data.tStart = mktime(&tstart);
//			newnode->data.tEnd = mktime(&tend);
//			newnode->data.fTotalUse = fTotalUse;
//			newnode->data.tLast = mktime(&tlast);
//			newnode->data.nUseCount = nUseCount;
//			newnode->data.fBalance = fBalance;
//			newnode->data.nDel = nDel;
//			addnode(newnode);
//			count++;
//		}
//		else {
//			printf("数据格式错误，无法正确读取！\n");
//			free(newnode);
//			newnode = NULL;
//		}
//	}
//	fclose(fp);
//	return count;
//}
void readcard() {
	FILE* fp = fopen("cards.txt", "r");
	if (fp == NULL) {
		printf("文件无法打开！\n");
		return;
	}
	char line[256];
	while (fgets(line, sizeof(line), fp) != NULL) {
		CardNode* newnode = createnode();
		if (newnode == NULL) {
			fclose(fp);
			return;
		}
		char name[20], paw[10], tstartstr[20], tendstr[20], tlaststr[20];
		int nStatus, nUseCount, nDel;
		float fTotalUse, fBalance;
		int n = sscanf_s(line, "%19[^#]##%9[^#]##%d##%19[^#]##%19[^#]##%f##%19[^#]##%d##%f##%d",
			name, (unsigned)_countof(name), paw, (unsigned)_countof(paw), &nStatus,
			tstartstr, (unsigned)_countof(tstartstr), tendstr, (unsigned)_countof(tendstr),
			&fTotalUse, tlaststr, (unsigned)_countof(tlaststr), &nUseCount, &fBalance, &nDel);
		if (n == 10) {
			strcpy_s(newnode->data.aName, sizeof(newnode->data.aName), name);
			strcpy_s(newnode->data.aPaws, sizeof(newnode->data.aPaws), paw);
			struct tm tstart = { 0 }, tend = { 0 }, tlast = { 0 };
			sscanf_s(tstartstr, "%d-%d-%d %d:%d:%d", &tstart.tm_year, &tstart.tm_mon, &tstart.tm_mday, &tstart.tm_hour, &tstart.tm_min, &tstart.tm_sec);
			sscanf_s(tendstr, "%d-%d-%d %d:%d:%d", &tend.tm_year, &tend.tm_mon, &tend.tm_mday, &tend.tm_hour, &tend.tm_min, &tend.tm_sec);
			sscanf_s(tlaststr, "%d-%d-%d %d:%d:%d", &tlast.tm_year, &tlast.tm_mon, &tlast.tm_mday, &tlast.tm_hour, &tlast.tm_min, &tlast.tm_sec);
			tstart.tm_year -= 1900; tend.tm_year -= 1900; tlast.tm_year -= 1900;
						tstart.tm_mon -= 1; tend.tm_mon -= 1; tlast.tm_mon -= 1;
						newnode->data.nStatus = nStatus;
						newnode->data.tStart = mktime(&tstart);
						newnode->data.tEnd = mktime(&tend);
						newnode->data.fTotalUse = fTotalUse;
						newnode->data.tLast = mktime(&tlast);
						newnode->data.nUseCount = nUseCount;
						newnode->data.fBalance = fBalance;
						newnode->data.nDel = nDel;
						addnode(newnode);
					}
					else {
						printf("数据格式错误，无法正确读取！\n");
						free(newnode);
						newnode = NULL;
					}
				}
				fclose(fp);
			}