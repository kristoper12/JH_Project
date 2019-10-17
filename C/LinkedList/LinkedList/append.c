#include "LinkedList.h"

Node *AppendFromHead(LinkedList *_ptList, int _iObject) {
	_ptList->m_pCurrent = GetNode(_iObject);

	if (_ptList->m_pHead) {
		_ptList->m_pCurrent->m_pNext = _ptList->m_pHead;
		_ptList->m_pHead->m_pPrevious = _ptList->m_pCurrent;
	}
	else
		_ptList->m_pTail = _ptList->m_pCurrent;
	_ptList->m_pHead = _ptList->m_pCurrent;
	(_ptList->m_uCount)++;

	return _ptList->m_pCurrent;
}	// �� ��� �߰�
Node *AppendFromTail(LinkedList *_ptList, int _iObject) {
	_ptList->m_pCurrent = GetNode(_iObject);

	if (_ptList->m_pHead) {
		_ptList->m_pCurrent->m_pPrevious = _ptList->m_pTail;
		_ptList->m_pTail->m_pNext = _ptList->m_pCurrent;
	}
	else
		_ptList->m_pHead = _ptList->m_pCurrent;
	_ptList->m_pTail = _ptList->m_pCurrent;
	(_ptList->m_uCount)++;

	return _ptList->m_pCurrent;
}	// �� ��� �߰�