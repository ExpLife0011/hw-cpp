#ifndef LIST_H
#define LIST_H


/**
@class List
������� ����������� ����� �������
*/
class List
{
public:
    virtual ~List(){};
    /// ����� ��������� �������� � ����� ������
    virtual void addValue(int val) = 0;
    /// ����� ������� �������� �� ������
    virtual void removeValue(int val) = 0;
    /// ����� �������� � ������
    virtual bool find(int val) = 0;
    /// ������ ������
    virtual int size() = 0;
    /// �������� ������ �� ������������ �������
    virtual int get(int pos = 0) = 0;
};

#endif // LIST_H
