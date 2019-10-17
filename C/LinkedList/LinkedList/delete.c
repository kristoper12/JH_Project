#include "LinkedList.h"

Node *DeleteFromHead(LinkedList *_ptList) {
	if (_ptList->m_pHead) {
		if (_ptList->m_uCount == 1) {
			(_ptList->m_uCount)--;
			free(_ptList->m_pHead);
		}
		else {
			_ptList->m_pHead = _ptList->m_pHead->m_pNext;
			(_ptList->m_uCount)--;
			free(_ptList->m_pHead->m_pPrevious);
		}
	}
	else
		printf("데이터가 존재하지 않습니다.\n");
}
Node *DeleteFromTail(LinkedList *_ptList) {
	if (_ptList->m_pHead) {
		if (_ptList->m_uCount == 1) {
			(_ptList->m_uCount)--;
			free(_ptList->m_pHead);
		}
		else {
			_ptList->m_pTail = _ptList->m_pTail->m_pPrevious;
			/*_ptList->m_pTail->m_pPrevious->m_pNext = */
			(_ptList->m_uCount)--;
			free(_ptList->m_pTail->m_pNext);
		}
	}
	else
		printf("데이터가 존재하지 않습니다.\n");
}
Node *Delete(LinkedList *_ptList, int _cnt) {
	int i;

	if (_ptList->m_uCount < _cnt) {
		printf("입력하신 번호에 노드가 존재하지 않습니다.\n번호와 데이터를 다시 입력하주세요.\n");
		return;
	}
	_ptList->m_pCurrent = _ptList->m_pHead;
	if (_ptList->m_pHead) {
		for (i = 0; i<_cnt; i++) {
			_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
		}
		if (_ptList->m_uCount == 1) {
			free(_ptList->m_pCurrent);
			return;
		}
		if (_ptList->m_uCount == _cnt) {
			_ptList->m_pTail = _ptList->m_pTail->m_pPrevious;
			free(_ptList->m_pTail->m_pNext);
		}
		else if (_cnt == 1) {
			_ptList->m_pHead = _ptList->m_pHead->m_pNext;
			free(_ptList->m_pHead->m_pPrevious);
		}
		else {
			_ptList->m_pCurrent->m_pNext->m_pPrevious = _ptList->m_pCurrent->m_pPrevious;
			_ptList->m_pCurrent->m_pPrevious->m_pNext = _ptList->m_pCurrent->m_pNext;
		}
		(_ptList->m_uCount)--;
	}
	else
		printf("데이터가 존재하지 않습니다.\n");
}
void *DeleteAll(LinkedList *_ptList) {
	int i;
	_ptList->m_pCurrent = _ptList->m_pHead;
	for (i = 1; i<(_ptList->m_uCount); i++) {
		_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
		free(_ptList->m_pHead);
		_ptList->m_pHead = _ptList->m_pCurrent;
	}
	free(_ptList->m_pHead);
	_ptList->m_uCount = 0;
}