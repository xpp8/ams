#include"card_service.h"
#include"card_file.h"
CardNode* head = NULL;

//创建新节点
CardNode* createnode() {
	CardNode* newnode = (CardNode*)malloc(sizeof(CardNode));
	if (newnode == NULL) {
		printf("内存分配失败！\n");
		return NULL;
	}
	memset(newnode, 0, sizeof(CardNode));
	newnode->next = NULL;
	return newnode;
}

//添加节点到链表末尾
void addnode(CardNode* newnode) {
	if (newnode == NULL) {
		return;
	}
	if (head == NULL) {
		head = newnode;
		return;
	}
	CardNode* current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = newnode;
}

//根据节点查找卡号
CardNode* findcardbyname(char* name) {
	CardNode* current = head;
	while (current != NULL) {
		if (strcmp(current->data.aName, name) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

//删除节点
int deletenode(char* name) {
	if (head == NULL) {
		return 0;
	}
	//如果是头节点
	if (strcmp(head->data.aName, name) == 0) {
		CardNode* temp = head;
		head = head->next;
		free(temp);
		return 1;
	}
	//不是头节点
	CardNode* current = head;
	while (current->next != NULL) {
		if (strcmp(current->next->data.aName, name) == 0) {
			CardNode* temp = current->next;
			current->next = temp->next;
			free(temp);
			return 1;
		}
		current = current->next;
	}
	return 0;
}

//释放链表
void freelist() {
	CardNode* current = head;
	while (current != NULL) {
		CardNode* temp = current;
		current = current->next;
		free(temp);
	}
	head = NULL;
}

////添加卡
//void add() {
//	printf("-------添加卡-------\n");
//	if (cardcount >= 50) {
//		printf("存储已满，无法继续存储！\n");
//		return;
//	}
//	char name[20];
//	char paw[10];
//	while (1) {
//		printf("请输入要添加的卡号<1-18>:");
//
//		if (scanf_s("%19s", name, (unsigned)_countof(name)) != 1) { /* 处理输入错误 */ }
//
//		int len1 = strlen(name);
//		if (len1 < 1 || len1>18) {
//			printf("卡号长度不符合规定，请重新输入!\n");
//			while (getchar() != '\n');
//			continue;
//		}
//		if (findcardbyname(name) != NULL) {
//			printf("该卡号已存在，请重新输入！\n");
//				continue;
//		}
//		if (iscardexistinfile(name)) {
//			printf("卡号已存在于文件中，请重新输入！\n");
//			continue;
//		}
//		break;
//	}
//	while (1) {
//		printf("请输入密码<1-8>:");
//		scanf_s("%9s", paw, (unsigned)sizeof(paw));
//		int len2 = strlen(paw);
//		if (len2 >= 1 && len2 <= 8) {
//			break;
//		}
//		printf("密码长度不符合规定，请重新输入!\n");
//		while (getchar() != '\n');
//	}
//	CardNode* newnode = createnode();
//#if defined(_DEBUG)
//	if (!_CrtCheckMemory()) { printf("Heap corruption AFTER createnode in add()\n"); _CrtDbgBreak(); }
//#endif
//	if (newnode == NULL) {
//		return;
//	}
//
//	printf("请输入开卡金额:");
//
//	if (scanf_s("%f", &newnode->data.fBalance) != 1) { /* 处理输入错误 */ }
//
//#if defined(_DEBUG)
//	if (!_CrtCheckMemory()) { printf("Heap corruption AFTER reading balance in add()\n"); _CrtDbgBreak(); }
//#endif
//	newnode->data.nUseCount = 0;
//	newnode->data.fTotalUse = 0;
//	strcpy_s(newnode->data.aName, sizeof(newnode->data.aName), name);
//	strcpy_s(newnode->data.aPaws, sizeof(newnode->data.aPaws), paw);
//	newnode->data.nStatus = 0;
//	newnode->data.tStart = time(NULL);
//	newnode->data.tLast = newnode->data.tStart;
//	struct tm* t = localtime(&newnode->data.tStart);
//	t->tm_year += 1;
//	newnode->data.tEnd = mktime(t);
//#if defined(_DEBUG)
//	if (!_CrtCheckMemory()) { printf("Heap corruption BEFORE addnode in add()\n"); _CrtDbgBreak(); }
//#endif
//	addnode(newnode);
//}

//查询卡
void searchcard() {
	printf("-------查询卡-------\n");
	printf("请输入要查询的卡号:");
	char name[19];
	while (1) {
		scanf_s("%18s", name, (unsigned)sizeof(name));
		int len = strlen(name);
		if (len >= 1 && len <= 18) {
			break;
		}
		printf("卡号长度不符合规定，请重新输入");
	}
	CardNode* node = findcardbyname(name);
	if (node != NULL) {
		struct tm* t = localtime(&node->data.tLast);
		printf("%-20s %-6s %-8s %-12s %-10s %-18s\n", "卡号", "状态", "余额", "累计金额", "使用次数", "上次使用时间");
		printf("%-20s %-6d %-8.2f %-12.2f %-10d %-4d-%02d-%02d %02d:%02d:%02d\n", node->data.aName, node->data.nStatus, node->data.fBalance, node->data.fTotalUse, node->data.nUseCount, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	}
	else {
		printf("该卡号不存在\n");
	}
}



//添加卡
void add() {
	printf("-------添加卡-------\n");
	char name[20];
	char paw[10];
	while (1) {
		printf("请输入要添加的卡号<1-18>:");
		scanf_s("%19s", name, (unsigned)sizeof(name));
		int len1 = strlen(name);
		if (len1 < 1 || len1>18) {
			printf("卡号长度不符合规定，请重新输入!\n");
			while (getchar() != '\n');
			continue;
		}
		if (findcardbyname(name) != NULL) {
			printf("该卡号已存在，请重新输入!\n");
			continue;
		}
		if (iscardexistinfile(name)) {
			printf("卡号已存在于文件中，请重新输入!\n");
			continue;
		}
		break;
	}
	while (1) {
		printf("请输入密码<1-8>:");
		scanf_s("%9s", paw, (unsigned)sizeof(paw));
		int len2 = strlen(paw);
		if (len2 >= 1 && len2 <= 8) {
			break;
		}
		printf("密码长度不符合规定，请重新输入!\n");
		while (getchar() != '\n');
	}
	CardNode* newnode = createnode();
	printf("请输入开卡金额:");
	scanf_s("%f", &newnode->data.fBalance);
	newnode->data.nUseCount = 0;
	newnode->data.fTotalUse = 0;
	strcpy_s(newnode->data.aName, sizeof(newnode->data.aName), name);
	strcpy_s(newnode->data.aPaws, sizeof(newnode->data.aPaws), paw);
	newnode->data.nStatus = 0;
	newnode->data.tStart = time(NULL);
	newnode->data.tLast = newnode->data.tStart;
	struct tm* t = localtime(&newnode->data.tStart);
	t->tm_year += 1;
	newnode->data.tEnd = mktime(t);
	addnode(newnode);
	saveCard(newnode);
}


int iscardexistinfile(char* cardnumber) {
	FILE* fp = fopen("cards.txt", "r");
	if (fp == NULL) {
		return 0;
	}
	char line[256];
	char name[20];
	while (fgets(line, sizeof(line), fp)) {
		if (sscanf_s(line, "%19[^#]", name, (unsigned)_countof(name)) == 1) {
			if (strcmp(name, cardnumber) == 0) {
				fclose(fp);
				return 1;
			}
		}
	}
	fclose(fp);
	return 0;
}