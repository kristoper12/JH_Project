#include "LinkedList.h"

Node *LinearSearchByUnique(LinkedList *_ptList, int SearchObject) {
	unsigned int i;

	_ptList->m_pCurrent = _ptList->m_pHead;
	for (i = 0; i < _ptList->m_uCount; i++) {
		if (_ptList->m_pCurrent->m_iObject == SearchObject) {
			return _ptList->m_pCurrent;
		}
		_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
	}
	printf("�Է��Ͻ� ���� �����ϴ�.\n");
	return _ptList->m_pCurrent;
}	//	���� ���� Ž��
void LinearSearchByDuplicate(LinkedList *_ptList, LinkedList *_ptList_Temp, int SearchObject) {
	unsigned int i;

	_ptList->m_pCurrent = _ptList->m_pHead;
	for (i = 0; i < _ptList->m_uCount; i++) {
		if (_ptList->m_pCurrent->m_iObject == SearchObject) {
			_ptList_Temp->m_pCurrent = GetNode(SearchObject);
			if (_ptList_Temp->m_uCount == 0) {
				_ptList_Temp->m_pHead = _ptList_Temp->m_pCurrent;
				_ptList_Temp->m_pTail = _ptList_Temp->m_pCurrent;
				(_ptList_Temp->m_uCount)++;
			}
			else {
				AppendFromTail(_ptList_Temp, SearchObject);
			}
		}
		_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
	}
	if (_ptList_Temp->m_uCount == 0) {
		printf("�Է��Ͻ� ���� �����ϴ�.\n");
		return;
	}
}	//	���� ���� Ž��
Node *BinarySearchByUnique(LinkedList *_ptList, int SearchObject) {
	int i;
	int low, high, mid;

	SortBySelection(_ptList, 1);
	low = 1;
	high = _ptList->m_uCount;
	mid = (low + high) / 2;
	
	while (low <= high) {
		_ptList->m_pCurrent = _ptList->m_pHead;
		for (i = 1; i < mid; i++) {
			_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
		}
		if (_ptList->m_pCurrent->m_iObject > SearchObject) {
			high = mid - 1;
			mid = (low + high) / 2;
		}
		else if (_ptList->m_pCurrent->m_iObject < SearchObject) {
			low = mid + 1;
			mid = (low + high) / 2;
		}
		else {
			return _ptList->m_pCurrent;
		}
	}
	printf("�Է��Ͻ� ���� �����ϴ�.");
	return _ptList->m_pCurrent;
}	//	���� ���� Ž��
void BinarySearchByDuplicate(LinkedList *_ptList, LinkedList *_ptList_Temp, int SearchObject) {
	int i;
	int low, high, mid, check = 0;

	SortBySelection(_ptList, 1);
	low = 0;
	high = _ptList->m_uCount;
	mid = (low + high) / 2;

	while (check == 0) {
		_ptList->m_pCurrent = _ptList->m_pHead;
		for (i = 0; i < mid; i++) {
			_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
		}
		if (_ptList->m_pCurrent->m_iObject > SearchObject) {
			high = mid;
			mid = (low + high) / 2;
		}
		else if (_ptList->m_pCurrent->m_iObject < SearchObject) {
			low = mid;
			mid = (low + high) / 2;
		}
		else {
			check = 1;
			_ptList_Temp->m_pCurrent = GetNode(SearchObject);
			_ptList_Temp->m_pHead = _ptList_Temp->m_pCurrent;
			_ptList_Temp->m_pTail = _ptList_Temp->m_pCurrent;
			(_ptList_Temp->m_uCount)++;
			while (_ptList->m_pCurrent->m_pPrevious->m_iObject == SearchObject) {
				_ptList->m_pCurrent = _ptList->m_pCurrent->m_pPrevious;
				if (_ptList->m_pCurrent->m_pPrevious == _ptList->m_pHead)
					break;
			}
			while (_ptList->m_pCurrent->m_iObject == SearchObject) {
				if (_ptList_Temp->m_uCount == 0) {
					_ptList_Temp->m_pHead = _ptList_Temp->m_pCurrent;
					_ptList_Temp->m_pTail = _ptList_Temp->m_pCurrent;
					(_ptList_Temp->m_uCount)++;
					_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
				}
				else {
					AppendFromTail(_ptList_Temp, SearchObject);
					_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
				}
				if (_ptList->m_pCurrent == _ptList->m_pTail)
					break;
			}
		}
	}
	if (check == 0)
		printf("�Է��Ͻ� ���� �����ϴ�.");
}	//	���� ���� Ž��
