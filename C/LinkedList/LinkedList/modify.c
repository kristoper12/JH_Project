#include "LinkedList.h"

Node *Modify(LinkedList *_ptList, int _cnt, int _iObject) {
	int i;

	if (_ptList->m_uCount < _cnt) {
		printf("입력하신 번호에 노드가 존재하지 않습니다.\n번호와 데이터를 다시 입력하주세요.\n");
		return;
	}
	_ptList->m_pCurrent = _ptList->m_pHead;
	for (i = 1; i <= _cnt; i++) {
		_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
	}
	_ptList->m_pCurrent->m_iObject = _iObject;
}