#pragma once
#include "node.h"

class LinkedList
{
private:
	node *m_pHead;							//	��� �Ӹ�
	node *m_pTail;							//	��� ����
	node *m_pCurrent;						//	���� ���
	node *m_pTemp;							//	Swap�� ���
	unsigned int m_uCount;					//	����� �� ����
public:
	LinkedList() {
		m_pHead = NULL;
		m_pTail = NULL;
		m_pCurrent = NULL;
		m_pTemp = NULL;
		m_uCount = 0;
	}
	~LinkedList();

	node *Read(int);						//	���� ��ġ �� �б�
	node *AppendFromHead(int);				//	�� ��� �߰�
	node *AppendFromTail(int);				//	�� ��� �߰�
	node *InsertBefore(int, int);			//	���� ��� �� ��� �߰�
	node *InsertAfter(int, int);			//	���� ��� �� ��� �߰�
	node *DeleteFromHead();					//	�� ��� ����
	node *DeleteFromTail();					//	�� ��� ����
	node *Delete(int);						//	���� ��� ����
	void DeleteAll();						//	��� ��� ����
	node *Modify(int, int);					//	��� �� ����
	void Display();							//	��� ��ȸ �� ���
	void SortByBubble(int);					//	���� ����
	void SortByInsertion(int);				//	���� ����
	void SortBySelection(int);				//	���� ����
	node *LinearSearchByUnique(int);		//	���� ���� Ž��
	void LinearSearchByDuplicate(LinkedList*, int);		//	���� ���� Ž��
	node *BinarySearchByUnique(int);		//	���� ���� Ž��
	void BinarySearchByDuplicate(LinkedList*, int);		//	���� ���� Ž��
};

