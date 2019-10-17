#include "LinkedList.h"

void main(){
	int select;
	int select_option;
	LinkedList *_ptList;
	LinkedList *_ptList_Temp;

	Create(&_ptList);
	Create(&_ptList_Temp);
	while(1){
		printf("1) AppendFromHead\n2) AppendFromTail\n3) InsertBefore\n4) InsertAfter\n5) DeleteFromHead\n\
6) DeleteFromTail\n7) Delete\n8) Modify\n9) Display\n10) DeleteAll\n11) Read\n12) SortByBubble\n\
13) SortByInsertion\n14) SortBySelection\n15) LinearSearchByUnique\n16) LinearSearchByDuplicate\n\
17) BinarySearchByUnique\n18) BinarySearchByDuplicate\n0) CloseProgram\n");
		scanf("%d", &select);
		system("cls");
		switch (select){
		case 1: AppendFromHead(_ptList, _printf_iObject()); break;
		case 2: AppendFromTail(_ptList, _printf_iObject()); break;
		case 3: InsertBefore(_ptList, _printf_Number(), _printf_iObject()); break;
		case 4: InsertAfter(_ptList, _printf_Number(), _printf_iObject()); break;
		case 5: DeleteFromHead(_ptList); break;
		case 6: DeleteFromTail(_ptList); break;
		case 7: Delete(_ptList, _printf_Number()); break;
		case 8: Modify(_ptList, _printf_Number(), _printf_iObject()); break;
		case 9: Display(_ptList); break;
		case 10: DeleteAll(_ptList); break;
		case 11: Read(_ptList, _printf_Number()); break;
		case 12: SortByBubble(_ptList, _printf_Option()); break;
		case 13: SortByInsertion(_ptList, _printf_Option()); break;
		case 14: SortBySelection(_ptList, _printf_Option()); break;
		case 15: LinearSearchByUnique(_ptList, _printf_iObject()); break;
		case 16: LinearSearchByDuplicate(_ptList, _ptList_Temp, _printf_iObject()); break;
		case 17: BinarySearchByUnique(_ptList, _printf_iObject()); break;
		case 18: BinarySearchByDuplicate(_ptList, _ptList_Temp, _printf_iObject()); break;
		}
		if(select == 0) break;
	}
}