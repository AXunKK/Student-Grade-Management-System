#ifndef STUDENTCONTROLLER_H
#define STUDENTCONTROLLER_H
#include "StudentWork.h"

void toInitStudent(StudentNode *&L);
void toDisplayAllStudent(StudentNode *L);
void toDisplayStudentByClassName(StudentNode *L);
void toDisplayStudentById(StudentNode *L);
void toAddStudent(StudentNode *&L);
void toUpdateStudent(StudentNode *&L);
void toDeleteStudent(StudentNode *&L);
void toDestroyStudent(StudentNode *&L);

void controller_SortStudentByTotalScore(StudentNode*& L);
void saveAllToFile(StudentNode* L,CourseNode* LC);
#endif
