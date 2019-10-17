#pragma once
#include "node.h"

class LinkedList
{
private:
	node *m_pHead;							//	노드 머리
	node *m_pTail;							//	노드 꼬리
	node *m_pCurrent;						//	현재 노드
	node *m_pTemp;							//	Swap용 노드
	unsigned int m_uCount;					//	노드의 총 개수
public:
	LinkedList() {
		m_pHead = NULL;
		m_pTail = NULL;
		m_pCurrent = NULL;
		m_pTemp = NULL;
		m_uCount = 0;
	}
	~LinkedList();

	node *Read(int);						//	임의 위치 값 읽기
	node *AppendFromHead(int);				//	앞 노드 추가
	node *AppendFromTail(int);				//	뒤 노드 추가
	node *InsertBefore(int, int);			//	선택 노드 뒤 노드 추가
	node *InsertAfter(int, int);			//	선택 노드 앞 노드 추가
	node *DeleteFromHead();					//	앞 노드 제거
	node *DeleteFromTail();					//	뒤 노드 제거
	node *Delete(int);						//	선택 노드 제거
	void DeleteAll();						//	모든 노드 제거
	node *Modify(int, int);					//	노드 값 수정
	void Display();							//	노드 순회 후 출력
	void SortByBubble(int);					//	버블 정렬
	void SortByInsertion(int);				//	삽입 정렬
	void SortBySelection(int);				//	선택 정렬
	node *LinearSearchByUnique(int);		//	단일 선형 탐색
	void LinearSearchByDuplicate(LinkedList*, int);		//	다중 선형 탐색
	node *BinarySearchByUnique(int);		//	단일 이진 탐색
	void BinarySearchByDuplicate(LinkedList*, int);		//	다중 이진 탐색
};

