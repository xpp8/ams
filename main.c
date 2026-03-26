#include"menu.h"
#include"model.h"
#include"card_service.h"
#include"card_file.h"
#include<stdio.h>


int main() {
	int choice;
	char c;
	while (1) {
		outputMenu();
		int res = scanf_s("%d%c", &choice, &c, 1);
		if (res == 2 && c == '\n') {
			if (choice == 0) {
				printf("退出系统，欢迎下次使用！\n");
				freelist();
				break;
			}
			else if (choice == 1) {
				add();
			}
			else if (choice == 2) {
				readcard();
				searchcard();
			}
			else if (choice == 3) {

			}
			else if (choice == 4) {

			}
			else if (choice == 5) {

			}
			else if (choice == 6) {

			}
			else if (choice == 7) {

			}
			else if (choice == 8) {

			}
			else if (choice == 9) {
				printf("菜单编号超过规定范围，请重新输入！\n");
			}
			else {
				printf("请输入有效的数字编号！\n");
			}
		}
		else {
			printf("请输入有效的数字编号！\n");
			while ((c = getchar()) != '\n' && c != EOF);
		}
	}
	return 0;
}