#include "StudentWork.h"
#include "ScoreWork.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initStudent(StudentNode *&L) {
	L = NULL;
	
	printf("\n===== 手动录入学生信息（初始化）=====\n");
	printf("提示：输入学号为 0 时结束录入\n\n");
	
	while (1) {
		Student stu;
		stu.LS = NULL;
		
		printf("请输入学号（输入0结束）：");
		scanf("%d", &stu.id);
		if (stu.id == 0) {
			break;
		}
		
		printf("请输入姓名：");
		scanf("%s", stu.name);
		printf("请输入性别（M/F）：");
		scanf(" %c", &stu.sex);
		printf("请输入班级：");
		scanf("%s", stu.className);
		
		StudentNode *p = (StudentNode*)malloc(sizeof(StudentNode));
		p->stu = stu;
		p->next = NULL;
		p->stu.LS = NULL;
		
		if (!L) {
			L = p;
		} else {
			StudentNode *q = L;
			while (q->next) q = q->next;
			q->next = p;
		}
		printf("OK：学生 %d %s added\n\n", stu.id, stu.name);
	}
	printf("Student initialization finished.\n");
}

void destroyStudent(StudentNode *&L){
	StudentNode *p=L,*q;
	while(p){
		destroyScoreByStudent(L,p->stu.id);
		q=p;p=p->next;free(q);
	}
	L=NULL;
	printf("所有学生已清空\n");
}

void displayStudent(StudentNode *L,Student stu, int mode){
	if(!L){printf("无学生数据\n");return;}
	StudentNode*p=L;
	printf("学号\t姓名\t性别\t班级\n");
	while(p){
		if(mode==1||
		   (mode==2&&!strcmp(p->stu.className,stu.className))||
		   (mode==3&&p->stu.id==stu.id)){
			printf("%d\t%s\t%c\t%s\n",p->stu.id,p->stu.name,p->stu.sex,p->stu.className);
		}
		p=p->next;
	}
}

bool addStudent(StudentNode *&L, Student stu){
	StudentNode*p=(StudentNode*)malloc(sizeof(StudentNode));
	p->stu=stu;p->next=NULL;p->stu.LS=NULL;
	if(!L){L=p;return true;}
	StudentNode*q=L;
	while(q->next) q=q->next;
	q->next=p;
	return true;
}

bool updateStudent(StudentNode *&L, Student oldStu, Student newStu){
	StudentNode*p=locateStudent(L,oldStu.id,0);
	if(!p) return false;
	p->stu=newStu;
	return true;
}

bool deleteStudent(StudentNode *&L,Student stu){
	StudentNode *pre=locateStudent(L,stu.id,1),*cur;
	if(!pre){
		cur=L;L=L->next;
	}else{
		cur=pre->next;pre->next=cur->next;
	}
	destroyScoreByStudent(L,cur->stu.id);
	free(cur);
	return true;
}

StudentNode* locateStudent(StudentNode *L,int id, int mode){
	if(!L)return NULL;
	StudentNode*p=L,*pre=NULL;
	while(p&&p->stu.id!=id){pre=p;p=p->next;}
	if(!p)return NULL;
	return mode==0?p:pre;
}

void showStudentDetails(Student stu){
	printf("【%d %s %c %s】\n",stu.id,stu.name,stu.sex,stu.className);
}

void sortStudentByTotalScore(StudentNode*& L) {
	if (!L || !L->next) return;
	
	for (StudentNode* p = L; p->next; p = p->next) {
		for (StudentNode* q = p->next; q; q = q->next) {
			int totalP = 0, totalQ = 0;
			ScoreNode* scP = p->stu.LS;
			ScoreNode* scQ = q->stu.LS;
			
			while (scP) { totalP += scP->score; scP = scP->scNext; }
			while (scQ) { totalQ += scQ->score; scQ = scQ->scNext; }
			
			if (totalQ > totalP) {
				Student temp = p->stu;
				p->stu = q->stu;
				q->stu = temp;
			}
		}
	}
	
	printf("\n===== 学生总分排名 =====\n");
	StudentNode* t = L;
	int rank = 1;
	while (t) {
		int total = 0;
		ScoreNode* sc = t->stu.LS;
		while (sc) { total += sc->score; sc = sc->scNext; }
		printf("%d\t%d\t%s\t总分：%d\n", rank++, t->stu.id, t->stu.name, total);
		t = t->next;
	}
}

