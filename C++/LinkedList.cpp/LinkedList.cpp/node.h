#pragma once
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
class node
{
private:
	node *m_pPrevious;											//	노드의 이전 노드
	node *m_pNext;												//	노드의 이전 노드
	int m_iObject;												//	노드의 값
public:
	node(int);
	~node();

	node* GetNext() { return m_pNext; }							//
	void SetNext(node* pNode) { m_pNext = pNode; }				//
	node* GetPrevious() { return m_pPrevious; }					//
	void SetPrevious(node* pNode) { m_pPrevious = pNode; }		//
	int GetiObject() { return m_iObject; }						//
	void SetiObject(int _iObject) { m_iObject = _iObject; }		//
	node *GetNode(int);											//	노드 생성
};

