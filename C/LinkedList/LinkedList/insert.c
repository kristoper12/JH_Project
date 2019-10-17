#include "LinkedList.h"

Node *InsertBefore(LinkedList *_ptList, int _cnt, int _iObject) {
	int i;

	if (_ptList->m_uCount < _cnt) {
		printf("입력하신 번호에 노드가 존재하지 않습니다.\n번호와 데이터를 다시 입력하주세요.\n");
		return;
	}
	_ptList->m_pTemp = GetNode(_iObject);
	_ptList->m_pCurrent = _ptList->m_pHead;
	for (i = 0; i<_cnt; i++) {
		_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
	}
	_ptList->m_pTemp->m_pNext = _ptList->m_pCurrent;
	_ptList->m_pTemp->m_pPrevious = _ptList->m_pCurrent->m_pPrevious;
	_ptList->m_pCurrent->m_pPrevious->m_pNext = _ptList->m_pTemp;
	_ptList->m_pCurrent->m_pPrevious = _ptList->m_pTemp;
	(_ptList->m_uCount)++;
}
Node *InsertAfter(LinkedList *_ptList, int _cnt, int _iObject) {
	int i;

	if (_ptList->m_uCount < _cnt) {
		printf("입력하신 번호에 노드가 존재하지 않습니다.\n번호와 데이터를 다시 입력하주세요.\n");
		return;
	}
	_ptList->m_pTemp = GetNode(_iObject);
	_ptList->m_pCurrent = _ptList->m_pHead;
	for (i = 0; i<_cnt; i++) {
		_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
	}
	if (_ptList->m_uCount == _cnt) {
		_ptList->m_pTemp->m_pPrevious = _ptList->m_pTail;
		_ptList->m_pTail->m_pNext = _ptList->m_pTemp;
	}
	else {
		_ptList->m_pTemp->m_pNext = _ptList->m_pCurrent->m_pNext;
		_ptList->m_pTemp->m_pPrevious = _ptList->m_pCurrent;
		_ptList->m_pCurrent->m_pNext->m_pPrevious = _ptList->m_pTemp;
		_ptList->m_pCurrent->m_pNext = _ptList->m_pTemp;
	}
	(_ptList->m_uCount)++;
}
