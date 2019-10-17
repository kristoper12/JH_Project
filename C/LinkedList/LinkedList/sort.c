#include "LinkedList.h"

void SortByBubble(LinkedList *_ptList, int _option) {
	unsigned int i, j;

	if (_option == 1) {
		for (i = 0; i < _ptList->m_uCount; i++) {
			_ptList->m_pCurrent = _ptList->m_pHead;
			for (j = 0; j < _ptList->m_uCount - i; j++) {
				_ptList->m_pTemp = _ptList->m_pCurrent->m_pNext;
				if (_ptList->m_pCurrent->m_iObject > _ptList->m_pTemp->m_iObject) {
					if (_ptList->m_pCurrent == _ptList->m_pHead) {
						_ptList->m_pHead = _ptList->m_pTemp;
						_ptList->m_pCurrent->m_pNext = _ptList->m_pTemp->m_pNext;
						_ptList->m_pTemp->m_pNext = _ptList->m_pCurrent;
						_ptList->m_pCurrent->m_pNext->m_pPrevious = _ptList->m_pCurrent;
						_ptList->m_pCurrent->m_pPrevious = _ptList->m_pTemp;
					}
					else if (_ptList->m_pTemp == _ptList->m_pTail) {
						_ptList->m_pTail = _ptList->m_pCurrent;
						_ptList->m_pCurrent->m_pPrevious->m_pNext = _ptList->m_pTemp;
						_ptList->m_pTemp->m_pPrevious = _ptList->m_pCurrent->m_pPrevious;
						_ptList->m_pTemp->m_pNext = _ptList->m_pCurrent;
						_ptList->m_pCurrent->m_pPrevious = _ptList->m_pTemp;
					}
					else {
						_ptList->m_pCurrent->m_pPrevious->m_pNext = _ptList->m_pTemp;
						_ptList->m_pTemp->m_pPrevious = _ptList->m_pCurrent->m_pPrevious;
						_ptList->m_pCurrent->m_pNext = _ptList->m_pTemp->m_pNext;
						_ptList->m_pTemp->m_pNext = _ptList->m_pCurrent;
						_ptList->m_pCurrent->m_pNext->m_pPrevious = _ptList->m_pCurrent;
						_ptList->m_pCurrent->m_pPrevious = _ptList->m_pTemp;
					}
				}
				else {
					_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
				}
			}
		}
	}
	else if (_option == 2) {
		for (i = 0; i < _ptList->m_uCount; i++) {
			_ptList->m_pCurrent = _ptList->m_pHead;
			for (j = 0; j < _ptList->m_uCount - i; j++) {
				_ptList->m_pTemp = _ptList->m_pCurrent->m_pNext;
				if (_ptList->m_pCurrent->m_iObject < _ptList->m_pTemp->m_iObject) {
					if (_ptList->m_pCurrent == _ptList->m_pHead) {
						_ptList->m_pHead = _ptList->m_pTemp;
						_ptList->m_pCurrent->m_pNext = _ptList->m_pTemp->m_pNext;
						_ptList->m_pTemp->m_pNext = _ptList->m_pCurrent;
						_ptList->m_pCurrent->m_pNext->m_pPrevious = _ptList->m_pCurrent;
						_ptList->m_pCurrent->m_pPrevious = _ptList->m_pTemp;
					}
					else if (_ptList->m_pTemp == _ptList->m_pTail) {
						_ptList->m_pTail = _ptList->m_pCurrent;
						_ptList->m_pCurrent->m_pPrevious->m_pNext = _ptList->m_pTemp;
						_ptList->m_pTemp->m_pPrevious = _ptList->m_pCurrent->m_pPrevious;
						_ptList->m_pTemp->m_pNext = _ptList->m_pCurrent;
						_ptList->m_pCurrent->m_pPrevious = _ptList->m_pTemp;
					}
					else {
						_ptList->m_pCurrent->m_pPrevious->m_pNext = _ptList->m_pTemp;
						_ptList->m_pTemp->m_pPrevious = _ptList->m_pCurrent->m_pPrevious;
						_ptList->m_pCurrent->m_pNext = _ptList->m_pTemp->m_pNext;
						_ptList->m_pTemp->m_pNext = _ptList->m_pCurrent;
						_ptList->m_pCurrent->m_pNext->m_pPrevious = _ptList->m_pCurrent;
						_ptList->m_pCurrent->m_pPrevious = _ptList->m_pTemp;
					}
				}
				else {
					_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
				}
			}
		}
	}
}	//	버블 정렬

void SortByInsertion(LinkedList *_ptList, int _option) {
	int i, j, cnt;
	Node *q;

	_ptList->m_pCurrent = _ptList->m_pHead;
	if (_option == 1) {
		for (i = 1; i < _ptList->m_uCount; i++) {
			_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
			_ptList->m_pTemp = _ptList->m_pCurrent;
			cnt = 1;
			for (j = i - 1; j >= 0; j--) {
				q = _ptList->m_pTemp->m_pPrevious;
				if (q->m_iObject > _ptList->m_pTemp->m_iObject) {
					if (q == _ptList->m_pHead) {
						_ptList->m_pHead = _ptList->m_pTemp;
						q->m_pNext = _ptList->m_pTemp->m_pNext;
						_ptList->m_pTemp->m_pNext = q;
						q->m_pNext->m_pPrevious = q;
						q->m_pPrevious = _ptList->m_pTemp;
						if (cnt == 1) {
							cnt = 0;
							_ptList->m_pCurrent = q;
						}
					}
					else if (_ptList->m_pTemp == _ptList->m_pTail) {
						_ptList->m_pTail = q;
						q->m_pPrevious->m_pNext = _ptList->m_pTemp;
						_ptList->m_pTemp->m_pPrevious = q->m_pPrevious;
						_ptList->m_pTemp->m_pNext = q;
						q->m_pPrevious = _ptList->m_pTemp;
					}
					else {
						if (cnt == 1) {
							cnt = 0;
							_ptList->m_pCurrent = q;
						}
						q->m_pPrevious->m_pNext = _ptList->m_pTemp;
						_ptList->m_pTemp->m_pPrevious = q->m_pPrevious;
						q->m_pNext = _ptList->m_pTemp->m_pNext;
						_ptList->m_pTemp->m_pNext = q;
						q->m_pNext->m_pPrevious = q;
						q->m_pPrevious = _ptList->m_pTemp;
					}
				}
			}
		}
	}
	else if (_option == 2) {
		for (i = 1; i < _ptList->m_uCount; i++) {
			_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
			_ptList->m_pTemp = _ptList->m_pCurrent;
			cnt = 1;
			for (j = i - 1; j >= 0; j--) {
				q = _ptList->m_pTemp->m_pPrevious;
				if (q->m_iObject < _ptList->m_pTemp->m_iObject) {
					if (q == _ptList->m_pHead) {
						_ptList->m_pHead = _ptList->m_pTemp;
						q->m_pNext = _ptList->m_pTemp->m_pNext;
						_ptList->m_pTemp->m_pNext = q;
						q->m_pNext->m_pPrevious = q;
						q->m_pPrevious = _ptList->m_pTemp;
						if (cnt == 1) {
							cnt = 0;
							_ptList->m_pCurrent = q;
						}
					}
					else if (_ptList->m_pTemp == _ptList->m_pTail) {
						_ptList->m_pTail = q;
						q->m_pPrevious->m_pNext = _ptList->m_pTemp;
						_ptList->m_pTemp->m_pPrevious = q->m_pPrevious;
						_ptList->m_pTemp->m_pNext = q;
						q->m_pPrevious = _ptList->m_pTemp;
					}
					else {
						if (cnt == 1) {
							cnt = 0;
							_ptList->m_pCurrent = q;
						}
						q->m_pPrevious->m_pNext = _ptList->m_pTemp;
						_ptList->m_pTemp->m_pPrevious = q->m_pPrevious;
						q->m_pNext = _ptList->m_pTemp->m_pNext;
						_ptList->m_pTemp->m_pNext = q;
						q->m_pNext->m_pPrevious = q;
						q->m_pPrevious = _ptList->m_pTemp;
					}
				}
			}
		}
	}
}	//	삽입 정렬

void SortBySelection(LinkedList *_ptList, int _option) {
	unsigned int i, j, temp;
	int Min;
	int Min_Address;
	Node *q;

	_ptList->m_pCurrent = _ptList->m_pHead;
	if (_option == 1) {
		for (i = 0; i < _ptList->m_uCount - 1; i++) {
			q = _ptList->m_pCurrent;
			Min = q->m_iObject;
			Min_Address = 0;
			for (j = 0; j < _ptList->m_uCount - i; j++) {
				if (q->m_iObject < Min) {
					Min = q->m_iObject;
					Min_Address = j + i;
				}
				q = q->m_pNext;
			}
			if (Min_Address != 0) {
				q = _ptList->m_pHead;
				for (int k = 0; k < Min_Address; k++)
					q = q->m_pNext;
				temp = _ptList->m_pCurrent->m_iObject;
				_ptList->m_pCurrent->m_iObject = q->m_iObject;
				q->m_iObject = temp;
			}
			_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
		}
	}
	else if (_option == 2) {
		for (i = 0; i < _ptList->m_uCount - 1; i++) {
			q = _ptList->m_pCurrent;
			Min = q->m_iObject;
			Min_Address = 0;
			for (j = 0; j < _ptList->m_uCount - i; j++) {
				if (q->m_iObject > Min) {
					Min = q->m_iObject;
					Min_Address = j + i;
				}
				q = q->m_pNext;
			}
			if (Min_Address != 0) {
				q = _ptList->m_pHead;
				for (int k = 0; k < Min_Address; k++)
					q = q->m_pNext;
				temp = _ptList->m_pCurrent->m_iObject;
				_ptList->m_pCurrent->m_iObject = q->m_iObject;
				q->m_iObject = temp;
			}
			_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
		}
	}
}	//	선택 정렬