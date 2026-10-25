#ifndef SCORECONTROLLER_H
#define SCORECONTROLLER_H

#include "ScoreWork.h"

void toDisplayAllScore(StudentNode *L);
void toDisplayScoreByClassName(StudentNode *L);
void toDisplayScoreById(StudentNode *L);

void toDestroyScoreByStudent(StudentNode *&L, int id);
void toDestroyAllScore(StudentNode *&L);

void toAddScoreByStudent(StudentNode *&L, CourseNode *LC);
void toAddScoreByCourse(StudentNode *&L, CourseNode *LC);
void toAddAScoreByStudent(StudentNode *&L, CourseNode *LC);

void toDeleteAScoreByStudent(StudentNode *&L, CourseNode *LC);
void addCourse(CourseNode*& LC, int cid, char* cname);
void controller_CalcCourseStat(StudentNode *L);
void controller_FilterScoreRange(StudentNode *L);

#endif
