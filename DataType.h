#ifndef DATATYPE_H
#define DATATYPE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct ScNode{
	int cId;
	int score;
	struct ScNode *scNext;
}ScoreNode;

typedef struct{
	int id;
	char name[20];
	char sex; 
	char className[20];
	ScoreNode *LS;
}Student;

typedef struct SNode{
	Student stu;
	struct SNode *next;
}StudentNode;

typedef struct Cnode{
	int cId;
	char cName[20];
	struct Cnode *cNext;
}CourseNode;

#endif
