#include "CourseWork.h"

void createCourse(CourseNode *&LC){
	LC=NULL;
	int n,i;
	printf("输入课程数量：");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		CourseNode *p=(CourseNode*)malloc(sizeof(CourseNode));
		printf("课程%d编号、名称：",i+1);
		scanf("%d%s",&p->cId,p->cName);
		p->cNext=NULL;
		if(LC==NULL) LC=p;
		else{
			CourseNode *q=LC;
			while(q->cNext) q=q->cNext;
			q->cNext=p;
		}
	}
}

void displayCourse(CourseNode *LC){
	if(!LC){printf("暂无课程\n");return;}
	CourseNode *p=LC;
	printf("课程编号\t课程名\n");
	while(p){
		printf("%d\t\t%s\n",p->cId,p->cName);
		p=p->cNext;
	}
}

bool getCourseName(CourseNode *LC, int cId, char cName[]){
	CourseNode *p=locateCourse(LC,cId);
	if(!p) return false;
	strcpy(cName,p->cName);
	return true;
}

CourseNode* locateCourse(CourseNode *LC, int cId){
	CourseNode *p=LC;
	while(p&&p->cId!=cId) p=p->cNext;
	return p;
}

int getCourseNumber(CourseNode *LC){
	int cnt=0;CourseNode*p=LC;
	while(p){cnt++;p=p->cNext;}
	return cnt;
}

bool getCoursesAndNames(CourseNode* LC,int ids[],char names[][20],int len){
	int i=0;CourseNode*p=LC;
	while(p&&i<len){
		ids[i]=p->cId;
		strcpy(names[i],p->cName);
		p=p->cNext;i++;
	}
	return i>0;
}
