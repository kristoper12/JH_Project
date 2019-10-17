#include "LinkedList.h"

void Display(LinkedList *_ptList) {
	int i;
	_ptList->m_pCurrent = _ptList->m_pHead;
	for (i = 0; i<(_ptList->m_uCount); i++) {
		printf("%d\n", _ptList->m_pCurrent->m_iObject);
		_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
	}
	if (_ptList->m_pCurrent == 0) {
		printf("데이터가 존재하지 않습니다.\n");
	}
}
int _printf_Number() {
	int num;
	printf("몇번째 노드에 적용하시겠습니까? : ");
	scanf("%d", &num);

	system("cls");
	return num;
}
int _printf_iObject() {
	int data;

	printf("데이터를 입력하시오 : ");
	scanf("%d", &data);

	system("cls");
	return data;
}
int _printf_Option() {
	int option;

	printf("1. 오름차순 2. 내림차순\n");
	scanf("%d", &option);

	system("cls");
	return option;
}