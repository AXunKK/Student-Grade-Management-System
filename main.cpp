#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CourseController.h"
#include "StudentController.h"
#include "ScoreController.h"
#include "ScoreWork.h"

void testCourse(CourseNode*&LC){
	toCreateCourse(LC);
	toDisplayCourse(LC);
	toGetCourseName(LC);
}

void testStudent(StudentNode*&L,CourseNode*LC){
	toInitStudent(L);
	toDisplayAllStudent(L);
	toDisplayStudentByClassName(L);
	toDisplayStudentById(L);
	toAddStudent(L);
	toUpdateStudent(L);
	toDeleteStudent(L);
	toDestroyStudent(L);
}

void testScore(StudentNode*&L,CourseNode*LC){
	toAddScoreByStudent(L,LC);
	toDisplayAllScore(L);
}

void menu(){
	puts("\n==================学生成绩管理系统====================");
	puts("1.课程管理  2.学生管理  3.成绩管理  4.扩展功能  0.退出");
	puts("======================================================");
}

void courseMenu(CourseNode*&LC){
	int op;
	while(1){
		puts("\n【课程】1新建 2查看 3按编号查名 0返回主菜单");
		scanf("%d",&op);
		if(op==0) break;
		
		if(op==1) toCreateCourse(LC);
		else if(op==2) toDisplayCourse(LC);
		else if(op==3) toGetCourseName(LC);
		else puts("输入错误！");
		
		printf("\n按回车继续...");
		getchar();getchar();
	}
}

void studentMenu(StudentNode*&L){
	int op;
	while(1){
		puts("\n【学生】1初始化 2全查 3按班查 4按学号查 5新增 6修改 7删除 8清空 0返回主菜单");
		scanf("%d",&op);
		if(op==0) break;
		
		switch(op){
			case 1:toInitStudent(L); break;
			case 2:toDisplayAllStudent(L); break;
			case 3:toDisplayStudentByClassName(L); break;
			case 4:toDisplayStudentById(L); break;
			case 5:toAddStudent(L); break;
			case 6:toUpdateStudent(L); break;
			case 7:toDeleteStudent(L); break;
			case 8:toDestroyStudent(L); break;
			default: puts("输入错误！"); break;
		}
		printf("\n按回车继续...");
		getchar();
		getchar();
	}
}

void scoreMenu(StudentNode*&L,CourseNode*LC){
	int op;
	while(1){
		puts("\n【成绩】1全查 2按班查 3按学号查 4单个学生批量加分 5整门课批量加分 6单门加分 7单门删分 8清空一人成绩 9清空全部 0返回主菜单");
		scanf("%d",&op);
		if(op==0) break;
		
		switch(op){
			case 1:toDisplayAllScore(L);break;
			case 2:toDisplayScoreByClassName(L);break;
			case 3:toDisplayScoreById(L);break;
			case 4:toAddScoreByStudent(L,LC);break;
			case 5:toAddScoreByCourse(L,LC);break;
			case 6:toAddAScoreByStudent(L,LC);break;
			case 7:toDeleteAScoreByStudent(L,LC);break;
			case 8:{
				int id;
				printf("输入学号：");
				scanf("%d",&id);
				toDestroyScoreByStudent(L,id);
				break;
			}
			case 9:toDestroyAllScore(L);break;
			default: puts("输入错误！"); break;
		}
		printf("\n按回车继续...");
		getchar();
		getchar();
	}
}

// 完整实现扩展功能菜单（新增3个功能）
void expandMenu(StudentNode* L, CourseNode* LC) {
	int choice;
	do {
		printf("\n====扩展功能====\n");
		printf("1. 单科成绩统计\n");
		printf("2. 按分数区间筛选\n");
		printf("3. 学生总分排名\n");
		printf("4. 保存数据到文件\n");
		printf("5. 重复成绩拦截\n");
		printf("6. 读取存档数据\n");
		printf("7. 查看不及格学生\n");
		printf("8. 按班级总分排名\n");
		printf("0. 返回主菜单\n");
		printf("请选择：");
		scanf("%d", &choice);
		
		switch (choice) {
			case 1: {
			int cid;
			printf("输入课程编号：");
			scanf("%d", &cid);
			calcCourseScoreStat(L, cid);
			break;
		}
			case 2: {
				int cid;
				printf("输入课程编号：");
				scanf("%d", &cid);
				filterScoreByRange(L, cid);
				break;
			}
		case 3:
			studentTotalScoreRank(L);
			break;
		case 4:
			saveAllToFile(L, LC);
			break;
		case 5:
			printf("已开启重复成绩拦截校验\n");
			break;
			// 新增功能入口
		case 6:
			loadAllFromFile(L, LC);
			break;
		case 7:
			showFailedStudent(L);
			break;
		case 8:
			rankByClassAndTotal(L);
			break;
		case 0:
			printf("返回主菜单...\n");
			break;
		default:
			printf("输入无效，请重新输入！\n");
			break;
		}
		printf("\n按回车继续...");
		getchar();
		getchar();
	} while (choice != 0);
}

int main(){
	CourseNode *LC=NULL;
	StudentNode *L=NULL;
	int sel;
	while(1){
		menu();
		scanf("%d",&sel);
		if(sel==0){
			saveAllToFile(L,LC);
			break;
		}
		else if(sel==1) courseMenu(LC);
		else if(sel==2) studentMenu(L);
		else if(sel==3) scoreMenu(L,LC);
		else if(sel==4) expandMenu(L,LC);
	}
	return 0;
}
