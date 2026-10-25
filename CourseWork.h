#ifndef COURSEWORK_H
#define COURSEWORK_H
#include "DataType.h"

void createCourse(CourseNode *&LC);
void displayCourse(CourseNode *LC);
bool getCourseName(CourseNode *LC, int cId, char cName[]);
CourseNode* locateCourse(CourseNode *LC, int cId);
int getCourseNumber(CourseNode *LC);
bool getCoursesAndNames(CourseNode* LC,int ids[],char names[][20],int len);

#endif
