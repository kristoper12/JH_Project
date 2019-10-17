#include "LinkedList.h"

void Create(LinkedList **_ptList) {
	*_ptList = (LinkedList *)calloc(1, sizeof(LinkedList));
}	 // 관리구조 생성
Node *GetNode(int _iObject) {
	Node *pNode = (Node*)malloc(sizeof(Node));
	pNode->m_pNext = pNode;
	pNode->m_pPrevious = pNode;
	pNode->m_iObject = _iObject;
	return pNode;
}   // 노드 생성
Node *Read(LinkedList *_ptList, int _cnt) {
	int i;

	_ptList->m_pCurrent = _ptList->m_pHead;
	for (i = 1; i<_cnt; i++) {
		_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
	}
	printf("%d\n", _ptList->m_pCurrent->m_iObject);
}	 // 임의 위치 값 읽기