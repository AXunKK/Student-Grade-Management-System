#include "StudentController.h"
#include "StudentWork.h"
#include "ScoreWork.h"
#include <stdio.h>
#include <string.h>

void toInitStudent(StudentNode*& L){
	initStudent(L);
}

void toDisplayAllStudent(StudentNode*L){
	Student tmp;
	displayStudent(L,tmp,1);
}

void toDisplayStudentByClassName(StudentNode* L) {
	char buf[30];
	Student tmp;
	
	while (1) {
		printf("输入班级（输入0退出）：");
		scanf("%s", buf);
		
		if (strcmp(buf, "0") == 0) {
			printf("退出班级查询。\n");
			break;
		}
		
		strcpy(tmp.className, buf);
		
		int count = 0;
		StudentNode *p = L;
		while (p) {
			if (strcmp(p->stu.className, tmp.className) == 0) {
				count++;
			}
			p = p->next;
		}
		
		if (count == 0) {
			printf("班级 [%s] 不存在或无学生。\n", buf);
			continue;
		}
		
		printf("班级 [%s] 的学生信息：\n", buf);
		displayStudent(L, tmp, 2);
	}
}

void toDisplayStudentById(StudentNode* L) {
	int id;
	while (1) {
		printf("输入学号（输入0退出）：");
		scanf("%d", &id);
		
		if (id == 0) {
			printf("退出学号查询。\n");
			break;
		}
		
		StudentNode* p = locateStudent(L, id, 0);
		if (!p) {
			printf("学号 %d 不存在。\n", id);
			continue;
		}
		
		Student tmp;
		tmp.id = id;
		printf("学号 %d 的学生信息：\n", id);
		displayStudent(L, tmp, 3);
	}
}

void toAddStudent(StudentNode*&L){
	Student s;
	printf("学号 姓名 性别 班级：");
	scanf("%d %s", &s.id, s.name);
	getchar(); // 吸收换行，修复性别读取空值
	scanf("%c %s", &s.sex, s.className);
	s.LS=NULL;
	addStudent(L,s);
}

void toUpdateStudent(StudentNode*&L){
	int id;
	Student old,newStu;
	printf("输入原学号：");
	scanf("%d",&id);
	old.id=id;
	printf("新信息(姓名 性别 班级)：");
	scanf("%s", newStu.name);
	getchar();
	scanf("%c %s", &newStu.sex, newStu.className);
	newStu.id=id;
	newStu.LS=NULL;
	updateStudent(L,old,newStu);
}

void toDeleteStudent(StudentNode*&L){
	int id;
	Student s;
	printf("输入待删学号：");
	scanf("%d",&id);
	s.id=id;
	deleteStudent(L,s);
}

void toDestroyStudent(StudentNode*&L){
	destroyStudent(L);
}

void controller_SortStudentByTotalScore(StudentNode*& L)
{
	sortStudentByTotalScore(L);
}
