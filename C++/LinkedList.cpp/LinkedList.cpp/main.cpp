#include "LinkedList.h"

void _fail() {
	cout << "숫자만 입력해 주세요\n";
	cin.clear();
	cin.ignore(256, '\n');
}
int _printf_Number() {
	int num;
	cout << "몇번째 노드에 적용하시겠습니까? : ";
	cin >> num;
	if (cin.fail()) {
		_fail();
		_printf_Number();
	}
	system("cls");
	return num;
}
int _printf_iObject() {
	int data;

	cout << "데이터를 입력하시오 : ";
	cin >> data;
	
	if (cin.fail()) {
		_fail();
		_printf_iObject();
	}
	system("cls");
	return data;
}
int _printf_Option() {
	int option;

	cout << "1. 오름차순 2. 내림차순\n";
	cin >> option;
	if (cin.fail()) {
		_fail();
		return 0;
	}

	system("cls");
	return option;
}
void main() {
	int select;
	int select_option;

	LinkedList *_ptList;
	LinkedList *_ptList_Temp;
	_ptList = new LinkedList();
	_ptList_Temp = new LinkedList();

	while (1) {
		cout << "1) AppendFromHead\n2) AppendFromTail\n3) InsertBefore\n4) InsertAfter\n5) DeleteFromHead\n\
6) DeleteFromTail\n7) Delete\n8) Modify\n9) Display\n10) DeleteAll\n11) Read\n12) SortByBubble\n\
13) SortByInsertion\n14) SortBySelection\n15) LinearSearchByUnique\n16) LinearSearchByDuplicate\n\
17) BinarySearchByUnique\n18) BinarySearchByDuplicate\n0) CloseProgram\n";
		cin >> select;
		system("cls");
		switch (select) {
		case 1: _ptList->AppendFromHead(_printf_iObject()); break;
		case 2: _ptList->AppendFromTail(_printf_iObject()); break;
		case 3: _ptList->InsertBefore(_printf_Number(), _printf_iObject()); break;
		case 4: _ptList->InsertAfter(_printf_Number(), _printf_iObject()); break;
		case 5: _ptList->DeleteFromHead(); break;
		case 6: _ptList->DeleteFromTail(); break;
		case 7: _ptList->Delete(_printf_Number()); break;
		case 8: _ptList->Modify(_printf_Number(), _printf_iObject()); break;
		case 9: _ptList->Display(); break;
		case 10: _ptList->DeleteAll(); break;
		case 11: _ptList->Read(_printf_Number()); break;
		case 12: _ptList->SortByBubble(_printf_Option()); break;
		case 13: _ptList->SortByInsertion(_printf_Option()); break;
		case 14: _ptList->SortBySelection(_printf_Option()); break;
		case 15: _ptList->LinearSearchByUnique(_printf_iObject()); break;
		case 16: _ptList->LinearSearchByDuplicate(_ptList_Temp, _printf_iObject()); _ptList_Temp->DeleteAll(); break;
		case 17: _ptList->BinarySearchByUnique(_printf_iObject()); break;
		case 18: _ptList->BinarySearchByDuplicate(_ptList_Temp, _printf_iObject()); _ptList_Temp->DeleteAll(); break;
		}
		if (select == 0) break;
	}
}