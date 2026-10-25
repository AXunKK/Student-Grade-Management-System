#include "ScoreWork.h"
#include "StudentController.h"
#include "CourseController.h"
#include "StudentWork.h"
#include "CourseWork.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayScore(StudentNode *L, Student stu) {
	StudentNode *p = L;
	while (p) {
		if (!strcmp(p->stu.className, stu.className) || p->stu.id == stu.id) {
			showStudentScoreDetails(p->stu);
			ScoreNode *sc = p->stu.LS;
			while (sc) {
				printf("课程%d：%d分 ", sc->cId, sc->score);
				sc = sc->scNext;
			}
			putchar('\n');
		}
		p = p->next;
	}
}

bool destroyScoreByStudent(StudentNode *&L, int id) {
	StudentNode *s = locateStudent(L, id, 0);
	if (!s) return false;
	ScoreNode *p = s->stu.LS, *q;
	while (p) { q = p; p = p->scNext; free(q); }
	s->stu.LS = NULL;
	return true;
}

void destroyAllScore(StudentNode *&L) {
	StudentNode *p = L;
	while (p) { destroyScoreByStudent(L, p->stu.id); p = p->next; }
}

bool addScoreByStudent(StudentNode *&L, CourseNode *LC) {
	if (!LC) {
		printf("请先添加课程！\n");
		return false;
	}
	
	while (1) {
		int id;
		printf("\n请输入学生学号（输入 0 结束，返回菜单）：");
		scanf("%d", &id);
		
		if (id == 0) {
			printf("批量成绩录入结束！\n");
			break;
		}
		
		StudentNode *stu = locateStudent(L, id, 0);
		if (!stu) {
			printf("学号 %d 不存在！\n", id);
			continue;
		}
		
		printf("===== 正在录入学生 %d (%s) 的成绩 =====\n", stu->stu.id, stu->stu.name);
		CourseNode *cp = LC;
		while (cp) {
			int sc;
			printf("%s(%d)分数：", cp->cName, cp->cId);
			scanf("%d", &sc);
			
			addAScoreByStudent(L, id, cp->cId, LC, sc);
			cp = cp->cNext;
		}
		printf("学生 %d 的成绩录入完成！\n", id);
	}
	
	return true;
}

bool addScoreByCourse(StudentNode *&L, int cId, CourseNode *LC) {
	StudentNode *p = L;
	while (p) {
		int s;
		printf("学生%d %s分数：", p->stu.id, p->stu.name);
		scanf("%d", &s);
		addAScoreByStudent(L, p->stu.id, cId, LC, s);
		p = p->next;
	}
	return true;
}

int addAScoreByStudent(StudentNode *&L, int id, int cId, CourseNode *LC, int score) {
	StudentNode *s = locateStudent(L, id, 0);
	if (!s) return -1;
	
	ScoreNode *oldSc = locateStudentScore(L, id, cId);
	if (oldSc) {
		oldSc->score = score;
		return 1;
	}
	
	ScoreNode *sc = (ScoreNode *)malloc(sizeof(ScoreNode));
	if (!sc) return -1;
	sc->cId = cId;
	sc->score = score;
	sc->scNext = NULL;
	
	if (!s->stu.LS) {
		s->stu.LS = sc;
	} else {
		ScoreNode *p = s->stu.LS;
		while (p->scNext) p = p->scNext;
		p->scNext = sc;
	}
	sortStudentScoreByCid(s->stu.LS);
	return 1;
}

int deleteScoreByStudent(StudentNode *&L, int id, int cId, CourseNode *LC) {
	StudentNode *s = locateStudent(L, id, 0);
	if (!s) return -1;
	ScoreNode *p = s->stu.LS, *pre = NULL;
	while (p && p->cId != cId) { pre = p; p = p->scNext; }
	if (!p) return 0;
	if (!pre) s->stu.LS = p->scNext;
	else pre->scNext = p->scNext;
	free(p);
	return 1;
}

ScoreNode *locateStudentScore(StudentNode *L, int id, int cId) {
	StudentNode *s = locateStudent(L, id, 0);
	if (!s) return NULL;
	ScoreNode *p = s->stu.LS;
	while (p && p->cId != cId) p = p->scNext;
	return p;
}

void sortStudentScoreByCid(ScoreNode *&first) {
	if (!first || !first->scNext)return;
	for (ScoreNode *i = first; i->scNext; i = i->scNext) {
		for (ScoreNode *j = i; j->scNext; j = j->scNext) {
			if (j->cId > j->scNext->cId) {
				int t1 = j->cId, t2 = j->score;
				j->cId = j->scNext->cId; j->score = j->scNext->score;
				j->scNext->cId = t1; j->scNext->score = t2;
			}
		}
	}
}

void showStudentScoreDetails(Student stu) {
	printf("[%d %s %s]成绩：", stu.id, stu.name, stu.className);
}

void calcCourseScoreStat(StudentNode *L, int cid) {
	int max = -1, min = 999, cnt = 0;
	double sum = 0;
	StudentNode *s = L;
	while (s) {
		ScoreNode *sc = s->stu.LS;
		while (sc) {
			if (sc->cId == cid) {
				if (sc->score > max) max = sc->score;
				if (sc->score < min) min = sc->score;
				sum += sc->score;
				cnt++;
			}
			sc = sc->scNext;
		}
		s = s->next;
	}
	if (cnt == 0) { printf("暂无成绩\n"); return; }
	printf("课程%d统计：\n最高分：%d\n最低分：%d\n平均分：%.1f\n人数：%d\n",
		   cid, max, min, sum / cnt, cnt);
}

void filterScoreByRange(StudentNode *L, int cid) {
	StudentNode *s = L;
	puts("\n【不及格 <60】");
	while (s) {
		ScoreNode *sc = s->stu.LS;
		while (sc) {
			if (sc->cId == cid && sc->score < 60)
				printf("学号：%d 姓名：%s 分数：%d\n", s->stu.id, s->stu.name, sc->score);
			sc = sc->scNext;
		}
		s = s->next;
	}
	s = L;
	puts("\n【中等 60~80】");
	while (s) {
		ScoreNode *sc = s->stu.LS;
		while (sc) {
			if (sc->cId == cid && sc->score >= 60 && sc->score < 80)
				printf("学号：%d 姓名：%s 分数：%d\n", s->stu.id, s->stu.name, sc->score);
			sc = sc->scNext;
		}
		s = s->next;
	}
	s = L;
	puts("\n【优秀 >=80】");
	while (s) {
		ScoreNode *sc = s->stu.LS;
		while (sc) {
			if (sc->cId == cid && sc->score >= 80)
				printf("学号：%d 姓名：%s 分数：%d\n", s->stu.id, s->stu.name, sc->score);
			sc = sc->scNext;
		}
		s = s->next;
	}
}

void studentTotalScoreRank(StudentNode* L) {
	if (!L) {
		printf("暂无学生数据！\n");
		return;
	}
	
	int count = 0;
	StudentNode* p = L;
	while (p) {
		count++;
		p = p->next;
	}
	
	typedef struct {
		int id;
		char name[20];
		int total;
	} Rank;
	
	Rank* arr = (Rank*)malloc(count * sizeof(Rank));
	p = L;
	int i = 0;
	while (p) {
		arr[i].id = p->stu.id;
		strcpy(arr[i].name, p->stu.name);
		arr[i].total = 0;
		
		ScoreNode* sc = p->stu.LS;
		while (sc) {
			arr[i].total += sc->score;
			sc = sc->scNext;
		}
		i++;
		p = p->next;
	}
	
	for (int a = 0; a < count - 1; a++) {
		for (int b = 0; b < count - 1 - a; b++) {
			if (arr[b].total < arr[b + 1].total) {
				Rank t = arr[b];
				arr[b] = arr[b + 1];
				arr[b + 1] = t;
			}
		}
	}
	
	printf("\n===== 学生总分排名 =====\n");
	printf("排名\t学号\t姓名\t总分\n");
	for (int i = 0; i < count; i++) {
		printf("%d\t%d\t%s\t%d\n", i + 1, arr[i].id, arr[i].name, arr[i].total);
	}
	free(arr);
}

void saveAllToFile(StudentNode* L, CourseNode* LC) {
	FILE* f = fopen("data.txt", "w");
	if (!f) {
		printf("保存失败！\n");
		return;
	}
	
	CourseNode* c = LC;
	while (c) {
		fprintf(f, "C %d %s\n", c->cId, c->cName);
		c = c->cNext;
	}
	
	StudentNode* s = L;
	while (s) {
		fprintf(f, "S %d %s %s\n", s->stu.id, s->stu.name, s->stu.className);
		ScoreNode* sc = s->stu.LS;
		while (sc) {
			fprintf(f, "G %d %d %d\n", s->stu.id, sc->cId, sc->score);
			sc = sc->scNext;
		}
		s = s->next;
	}
	
	fclose(f);
	printf("数据已保存到 data.txt\n");
}

// 读取存档（已修复：不调用不存在的 addCourse / addStudent，手动创建链表节点）
void loadAllFromFile(StudentNode*& L, CourseNode*& LC){
	FILE* f = fopen("data.txt", "r");
	if (!f)
	{
		printf("未找到存档文件，暂无历史数据！\n");
		return;
	}
	
	char flag;
	while (fscanf(f, " %c", &flag) != EOF)
	{
		if (flag == 'C') 
		{
			int cid;
			char cname[30];
			fscanf(f, "%d %s", &cid, cname);
			// 手动新建课程节点，头插链表
			CourseNode* newCourse = (CourseNode*)malloc(sizeof(CourseNode));
			newCourse->cId = cid;
			strcpy(newCourse->cName, cname);
			newCourse->cNext = LC;
			LC = newCourse;
		}
		else if (flag == 'S')
		{
			int sid;
			char sname[20], cls[20];
			fscanf(f, "%d %s %s", &sid, sname, cls);
			Student tmpStu;
			tmpStu.id = sid;
			strcpy(tmpStu.name, sname);
			strcpy(tmpStu.className, cls);
			StudentNode* newStu = (StudentNode*)malloc(sizeof(StudentNode));
			newStu->stu = tmpStu;
			newStu->stu.LS = NULL;
			newStu->next = L;
			L = newStu;
		}
		else if (flag == 'G')
		{
			int sid, cid, score;
			fscanf(f, "%d %d %d", &sid, &cid, &score);
			addAScoreByStudent(L, sid, cid, LC, score);
		}
	}
	fclose(f);
	printf("数据读取完成！\n");
}

void displayScore(StudentNode *L, Student stu, int mode)
{
	StudentNode *p = L;
	if(mode == 1)
	{
		// 打印全部学生成绩
		printf("====所有学生成绩信息====\n");
		while(p != NULL)
		{
			printf("学号：%d 姓名：%s 班级：%s\n",p->stu.id,p->stu.name,p->stu.className);
			ScoreNode *sc = p->stu.LS;
			if(sc == NULL)
			{
				printf("  暂无成绩\n");
			}
			while(sc != NULL)
			{
				printf("  课程%d：%d分\n",sc->cId,sc->score);
				sc = sc->scNext;
			}
			p = p->next;
		}
	}
	else if(mode == 2)
	{
		// 按班级筛选打印
		printf("====班级【%s】学生成绩====\n",stu.className);
		while(p != NULL)
		{
			if(strcmp(p->stu.className, stu.className) == 0)
			{
				printf("学号：%d 姓名：%s\n",p->stu.id,p->stu.name);
				ScoreNode *sc = p->stu.LS;
				if(sc == NULL)
				{
					printf("  暂无成绩\n");
				}
				while(sc != NULL)
				{
					printf("  课程%d：%d分\n",sc->cId,sc->score);
					sc = sc->scNext;
				}
			}
			p = p->next;
		}
	}
	else if(mode == 3)
	{
		// 按学号打印单个学生
		while(p != NULL)
		{
			if(p->stu.id == stu.id)
			{
				printf("====学号%d 成绩信息====\n",p->stu.id);
				printf("姓名：%s 班级：%s\n",p->stu.name,p->stu.className);
				ScoreNode *sc = p->stu.LS;
				if(sc == NULL)
				{
					printf("  暂无成绩\n");
				}
				while(sc != NULL)
				{
					printf("  课程%d：%d分\n",sc->cId,sc->score);
					sc = sc->scNext;
				}
				break;
			}
			p = p->next;
		}
	}
}

// 查看不及格学生
void showFailedStudent(StudentNode* L)
{
	if (!L)
	{
		printf("暂无数据！\n");
		return;
	}
	int hasFailed = 0;
	StudentNode* p = L;
	printf("\n===== 不及格学生名单 =====\n");
	while (p)
	{
		ScoreNode* sc = p->stu.LS;
		while (sc)
		{
			if (sc->score < 60)
			{
				printf("学号：%d  姓名：%s  课程编号：%d  分数：%d\n",
					   p->stu.id, p->stu.name, sc->cId, sc->score);
				hasFailed = 1;
			}
			sc = sc->scNext;
		}
		p = p->next;
	}
	if (!hasFailed)
	{
		printf("恭喜！暂无不及格学生\n");
	}
}

// 按班级总分排名
void rankByClassAndTotal(StudentNode* L)
{
	if (!L)
	{
		printf("暂无学生数据！\n");
		return;
	}
	char targetClass[20];
	printf("请输入班级名称：");
	scanf("%s", targetClass);
	
	int count = 0;
	StudentNode* p = L;
	while (p)
	{
		if (strcmp(p->stu.className, targetClass) == 0)
			count++;
		p = p->next;
	}
	if (count == 0)
	{
		printf("未找到该班级！\n");
		return;
	}
	
	typedef struct
	{
		int id;
		char name[20];
		int total;
	} ClassRank;
	ClassRank* arr = (ClassRank*)malloc(count * sizeof(ClassRank));
	
	p = L;
	int idx = 0;
	while (p)
	{
		if (strcmp(p->stu.className, targetClass) == 0)
		{
			arr[idx].id = p->stu.id;
			strcpy(arr[idx].name, p->stu.name);
			arr[idx].total = 0;
			ScoreNode* sc = p->stu.LS;
			while (sc)
			{
				arr[idx].total += sc->score;
				sc = sc->scNext;
			}
			idx++;
		}
		p = p->next;
	}
	
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - 1 - i; j++)
		{
			if (arr[j].total < arr[j + 1].total)
			{
				ClassRank t = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = t;
			}
		}
	}
	
	printf("\n===== %s 班级总分排名 =====\n", targetClass);
	printf("排名\t学号\t姓名\t总分\n");
	for (int i = 0; i < count; i++)
	{
		printf("%d\t%d\t%s\t%d\n", i + 1, arr[i].id, arr[i].name, arr[i].total);
	}
	free(arr);
}
