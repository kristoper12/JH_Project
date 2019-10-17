#pragma once
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
class node
{
private:
	node *m_pPrevious;											//	����� ���� ���
	node *m_pNext;												//	����� ���� ���
	int m_iObject;												//	����� ��
public:
	node(int);
	~node();

	node* GetNext() { return m_pNext; }							//
	void SetNext(node* pNode) { m_pNext = pNode; }				//
	node* GetPrevious() { return m_pPrevious; }					//
	void SetPrevious(node* pNode) { m_pPrevious = pNode; }		//
	int GetiObject() { return m_iObject; }						//
	void SetiObject(int _iObject) { m_iObject = _iObject; }		//
	node *GetNode(int);											//	��� ����
};

