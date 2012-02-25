#include "stdafx.h"
#include "parser.h"

bool lvlPlusMinus(char *&c)
{
	delims(c); //���������� �������
	if (!lvlMulDiv(c)) //���������� �� ������� ���� �������� �� ������ ���������
		return false; //���� ������ 
	delims(c); //���������� �������
	while (*c == '+' || *c == '-') //��������� �� �������� � ���������
	{
		c++; //������� ������� � ������
		if (!lvlMulDiv(c)) //���������� �� ������� ���� ��� ����� �������� �� ��������� ���������
			return false; //���� ������
	}
	return true; //� ������ ������
}
bool lvlMulDiv(char *&c)
{
	delims(c); //���������� �������
	if (!lvlBrackNum(c)) //���������� �� ������� ���� �������� �� ������ ���������
		return false;
	delims(c); //���������� �������
	while (*c == '*' || *c == '/')
	{
		c++; //������� ������� � ������
		if (!lvlBrackNum(c)) //���������� �� ������� ���� ��� ����� �������� �� ��������� ���������
			return false;
	}
	return true; //�����
}
bool lvlBrackNum(char *&c)
{
	delims(c); //������� �������
	if (*c == '(') //���� ����������� �����
	{
		c++; //������� �������
		if (!lvlPlusMinus(c)) //��������� ���������� ������
			return false; //������
		if (delims(c)) //������� ������� � ��������� �� ����� ������
			return false;
		if (*c != ')') //���� ��� ����. ����� - ������
			return false;
		c++; //������� �������
		return true; //�����
	} else //if (isDig(*c))
		return isFloat(c);
	//else return false;

}

bool isDig(char c)
{
	return (c <= '9' && c >= '0');
}

bool isFloat(char *&c)
{
	int state = -1;
	if (isDig(*c))
		state = 0;
	else if (*c == '-')
		state = 10;
	else
		return false;
	c++;
	while (true)
	{
		switch (state)
		{
		    case 10:
				if (isDig(*c))
				{
					c++;
					state = 0;
				}
				else
					state = -1;
				break;
/* 0 */    	case 0: 
				if (isDig(*c))
					c++;
				else if (*c == '.')
				{
					state = 1;
					c++;
				} else if (*c == 'e')
				{
					state = 3;
					c++;
				} else if (*c == 0)
					return true;
				else
					return true;
				break;
/* 1 */		case 1:
				if (*c == 0)
					state = -1;
				else if (isDig(*c))
				{
					state = 2;
					c++;
				} else
					state = -1;
				break;
/* 2 */		case 2:
				if (*c == 0)
					return true;
				else if (isDig(*c))
					c++;
				else if (*c == 'e')
				{
					state = 3;
					c++;
				} else
					return true;
				break;
/* 3 */	    case 3:
				if (*c == 0)
					state = -1;
				else if (*c == '+' || *c == '-')
				{
					state = 4;
					c++;
				} else if (isDig(*c))
				{
					state = 5;
					c++;
				} else
					state = -1;
				break;
/* 4 */	  	case 4:
				if (*c == 0)
					state = -1;
				else if (isDig(*c))
				{
					state = 5;
					c++;
				} else 
					state = -1;
				break;
/* 5 */	  	case 5:
				if (*c == 0)
					return true;
				else if (isDig(*c))
					c++;
				else 
					return true;
				break;
/* -1 */  	case -1:
				return false;
		}
	}
}

bool parse(char *c)
{
	char *tmp = c;
	return lvlPlusMinus(tmp) && delims(tmp);
}

bool delims(char *&c)
{
	while (*c == ' ')
		c++;
	return (*c == 0);
}