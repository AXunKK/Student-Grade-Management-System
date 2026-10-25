#ifndef STUDENTWORK_H
#define STUDENTWORK_H
#include "DataType.h"

void initStudent(StudentNode *&L);
void destroyStudent(StudentNode *&L);
void displayStudent(StudentNode *L,Student stu, int mode);
bool addStudent(StudentNode *&L, Student stu);
bool updateStudent(StudentNode *&L, Student oldStu, Student newStu);
bool deleteStudent(StudentNode *&L,Student stu);
StudentNode* locateStudent(StudentNode *L,int id, int mode);
void showStudentDetails(Student stu);
bool destroyScoreByStudent(StudentNode *&L,int id);
void sortStudentByTotalScore(StudentNode*& L);
void saveAllToFile(StudentNode* L, CourseNode* LC);
#endif
