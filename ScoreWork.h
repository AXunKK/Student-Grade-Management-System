#ifndef SCOREWORK_H
#define SCOREWORK_H
#include "DataType.h"
#include "StudentWork.h"

// 原有成绩基础功能
void displayScore(StudentNode *L, Student stu, int mode);
bool destroyScoreByStudent(StudentNode *&L,int id);
void destroyAllScore(StudentNode *&L);
bool addScoreByStudent(StudentNode*& L, CourseNode *LC);
bool addScoreByCourse(StudentNode*&L,int cId,CourseNode *LC);
int addAScoreByStudent(StudentNode*&L,int id,int cId,CourseNode *LC,int score);
int deleteScoreByStudent(StudentNode*&L,int id,int cId,CourseNode *LC);
ScoreNode* locateStudentScore(StudentNode*L,int id,int cId);
void sortStudentScoreByCid(ScoreNode *&first);
void showStudentScoreDetails(Student stu);

// 总分排名（和main.cpp调用名称统一）
void studentTotalScoreRank(StudentNode* L);

// 文件读写
void saveAllToFile(StudentNode* L,CourseNode* LC);
void loadAllFromFile(StudentNode*& L, CourseNode*& LC);

// 扩展统计功能
void calcCourseScoreStat(StudentNode* L, int cid);
void filterScoreByRange(StudentNode* L, int cid);
void showFailedStudent(StudentNode* L);
void rankByClassAndTotal(StudentNode* L);

#endif
