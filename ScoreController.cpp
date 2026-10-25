#include "ScoreController.h"
#include "ScoreWork.h"
#include "CourseWork.h"
#include <stdio.h>
#include <string.h>

void toDisplayAllScore(StudentNode *L){
	printf("====全部学生成绩====\n");
	Student tmp;
	displayScore(L,tmp,1);
}

void toDisplayScoreByClassName(StudentNode *L){
	char cls[20];
	Student tmp;
	printf("输入班级：");
	scanf("%s",cls);
	strcpy(tmp.className,cls);
	displayScore(L,tmp,2);
}

void toDisplayScoreById(StudentNode *L){
	int id;
	Student tmp;
	printf("输入学号：");
	scanf("%d",&id);
	tmp.id=id;
	displayScore(L,tmp,3);
}

void toDestroyScoreByStudent(StudentNode *&L,int id){
	destroyScoreByStudent(L,id);
}

void toDestroyAllScore(StudentNode *&L){
	destroyAllScore(L);
	printf("全部成绩已清空\n");
}

void toAddScoreByStudent(StudentNode*&L,CourseNode *LC){
	addScoreByStudent(L, LC);
}

void toAddScoreByCourse(StudentNode*&L,CourseNode *LC){
	int cid;
	printf("输入课程编号批量给所有学生录入：");
	scanf("%d",&cid);
	
	// 检查课程是否存在
	CourseNode* course = locateCourse(LC, cid);
	if (!course) {
		printf("课程不存在！\n");
		return;
	}
	
	// 遍历所有学生，逐个录入/更新成绩
	StudentNode* p = L;
	while (p) {
		int score;
		printf("学生 %d %s 分数：", p->stu.id, p->stu.name);
		scanf("%d", &score);
		
		// 核心：调用底层函数，自动处理【新增/修改】成绩
		addAScoreByStudent(L, p->stu.id, cid, LC, score);
		
		p = p->next;
	}
	printf("批量录入完成！\n");
}

void toAddAScoreByStudent(StudentNode*&L,CourseNode *LC){
	int id,cid,score;
	printf("输入学号、课程号、分数：");
	scanf("%d%d%d",&id,&cid,&score);
	addAScoreByStudent(L,id,cid,LC,score);
}

void toDeleteAScoreByStudent(StudentNode*&L,CourseNode *LC){
	int id,cid;
	printf("输入学号、待删课程号：");
	scanf("%d%d",&id,&cid);
	deleteScoreByStudent(L,id,cid,LC);
}

void controller_CalcCourseStat(StudentNode* L){
	int cid;
	printf("输入课程编号：");
	scanf("%d",&cid);
	calcCourseScoreStat(L,cid);
}

void controller_FilterScoreRange(StudentNode* L){
	int cid;
	printf("输入课程编号：");
	scanf("%d",&cid);
	filterScoreByRange(L,cid);
}
