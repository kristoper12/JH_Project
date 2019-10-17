#include "LinkedList.h"

Node *Modify(LinkedList *_ptList, int _cnt, int _iObject) {
	int i;

	if (_ptList->m_uCount < _cnt) {
		printf("�Է��Ͻ� ��ȣ�� ��尡 �������� �ʽ��ϴ�.\n��ȣ�� �����͸� �ٽ� �Է����ּ���.\n");
		return;
	}
	_ptList->m_pCurrent = _ptList->m_pHead;
	for (i = 1; i <= _cnt; i++) {
		_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
	}
	_ptList->m_pCurrent->m_iObject = _iObject;
}