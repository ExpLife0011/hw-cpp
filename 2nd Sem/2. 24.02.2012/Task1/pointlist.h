#ifndef POINTLIST_H
#define POINTLIST_H

#include "list.h"
/**
@class PointList
�����, ����������� �� List, ����������� �������� ��� ��������,
����������� �� ����������
*/
class PointList : public List
{
public:
    PointList();
    ~PointList();
    void addValue(int val);
    void removeValue(int val);
    bool find(int val);
    int size();
    int get(int pos = 0);
private:
    PointList *pNext;
    int value;
};

#endif // POINTLIST_H
