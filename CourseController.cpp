#include "CourseController.h"
#include "CourseWork.h"   // 新增这一行
void toCreateCourse(CourseNode *&LC){
	printf("====新建课程信息====\n");
	createCourse(LC);
}
void toDisplayCourse(CourseNode *LC){
	printf("====全部课程列表====\n");
	displayCourse(LC);
}
void toGetCourseName(CourseNode *LC){
	int id;char name[20];
	printf("输入待查课程编号：");
	scanf("%d",&id);
	if(getCourseName(LC,id,name)) printf("课程名称：%s\n",name);
	else printf("无该课程\n");
}
