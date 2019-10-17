#include "LinkedList.h"

void Display(LinkedList *_ptList) {
	int i;
	_ptList->m_pCurrent = _ptList->m_pHead;
	for (i = 0; i<(_ptList->m_uCount); i++) {
		printf("%d\n", _ptList->m_pCurrent->m_iObject);
		_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
	}
	if (_ptList->m_pCurrent == 0) {
		printf("�����Ͱ� �������� �ʽ��ϴ�.\n");
	}
}
int _printf_Number() {
	int num;
	printf("���° ��忡 �����Ͻðڽ��ϱ�? : ");
	scanf("%d", &num);

	system("cls");
	return num;
}
int _printf_iObject() {
	int data;

	printf("�����͸� �Է��Ͻÿ� : ");
	scanf("%d", &data);

	system("cls");
	return data;
}
int _printf_Option() {
	int option;

	printf("1. �������� 2. ��������\n");
	scanf("%d", &option);

	system("cls");
	return option;
}