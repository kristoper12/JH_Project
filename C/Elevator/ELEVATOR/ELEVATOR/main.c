#include <stdio.h>
#include <Windows.h>
#include <conio.h>

void main_Display();
int sub_Display(int *, int *, int, int, int);
int WhereYouGo(int *, int);
int HowManyPeople(int *, int, int);
void gotoxy(int, int);
void Box(int, int);
void People_insert(int, int);
void People_output(int, int);

int main() {
	int input_floor = 0;
	int input_people_plus = 0;
	int input_people_minus = 0;
	int floor = 1;
	int people = 0;
	int yPos = 20;
	int *pCurrent_floor = &floor;
	int *pCurrent_people = &people;
	int check_error = 0;
	int i;

	while (1) {
		main_Display();
		Box(14, yPos);
		for (i = 0; i < *pCurrent_people; i++) {
			People_insert(i + 9, yPos);
		}
		if (*pCurrent_people == 0) {
			gotoxy(35, 20);
			printf("몇 층에 사람이 있나요? : ");
			scanf("%d", &input_floor);
			gotoxy(35, 21);
			printf("몇 명이 타나요? : ");
			scanf("%d", &input_people_plus);
			input_people_minus = 0;
		}
		else {
			gotoxy(35, 19);
			printf("몇 층 가나요? : ");
			scanf("%d", &input_floor);
			gotoxy(35, 20);
			printf("몇 명이 내리나요? : ");
			scanf("%d", &input_people_minus);
			gotoxy(35, 21);
			printf("몇 명이 타나요? : ");
			scanf("%d", &input_people_plus);
		}
		gotoxy(35, 22);
		check_error = HowManyPeople(pCurrent_people, input_people_plus, input_people_minus);
		if (check_error == 0) {
			system("cls");
			continue;
		}
		check_error = WhereYouGo(pCurrent_floor, input_floor);
		if (check_error == 0) {
			system("cls");
			continue;
		}
		yPos = sub_Display(pCurrent_floor, pCurrent_people, input_floor, input_people_plus, input_people_minus);
		system("cls");
	}
	return 0;
}

int WhereYouGo(int *pCurrent_floor, int input_floor) {
	if (input_floor == *pCurrent_floor) {
		printf("현재 %d층 입니다.\n", input_floor);
		Sleep(3000);
		return 0;
	}
	else if (input_floor < 1 || input_floor > 7) {
		printf("저희는 1층부터 7층까지만 운행합니다.\n");
		Sleep(3000);
		return 0;
	}
	else if (input_floor > *pCurrent_floor) {
		printf("올라갑니다\n");
		return 1;
	}
	else if (input_floor < *pCurrent_floor) {
		printf("내려갑니다.\n");
		return 1;
	}
	return 0;
}

int HowManyPeople(int *pCurrent_people, int input_people_plus, int input_people_minus) {
	if (*pCurrent_people < input_people_minus) {
		printf("현재 %d명이 타고 있어 %d명이 내릴 수 없습니다.\n", *pCurrent_people, input_people_minus);
		Sleep(3000);
		return 0;
	}
	if (*pCurrent_people + input_people_plus - input_people_minus > 5) {
		printf("최대 정원 5명 입니다.\n");
		Sleep(3000);
		return 0;
	}
	return 1;
}

void main_Display() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("┌──────────────┐  \n");
	printf("│     ┌──────┐ │		  \n");
	printf("│  ⑦ │      │ │			  \n");
	printf("│     └──────┘ │		  \n");
	printf("│     ┌──────┐ │		  \n");
	printf("│  ⑥ │      │ │			  \n");
	printf("│     └──────┘ │		  \n");
	printf("│     ┌──────┐ │		  \n");
	printf("│  ⑤ │      │ │			  \n");
	printf("│     └──────┘ │		  \n");
	printf("│     ┌──────┐ │		  \n");
	printf("│  ④ │      │ │			  \n");
	printf("│     └──────┘ │		  \n");
	printf("│     ┌──────┐ │		  \n");
	printf("│  ③ │      │ │			  \n");
	printf("│     └──────┘ │		  \n");
	printf("│     ┌──────┐ │		  \n");
	printf("│  ② │      │ │			  \n");
	printf("│     └──────┘ │		  \n");
	printf("│     ┌──────┐ │		  \n");
	printf("│  ① │      │ │			  \n");
	printf("│     └──────┘ │		  \n");
	printf("└──────────────┘  \n");
}

int sub_Display(int *pCurrent_floor, int *pCurrent_people, int input_floor, int input_people_plus, int input_people_minus) {
	int floor;
	int floor_gap = input_floor - *pCurrent_floor;
	int people_gap = *pCurrent_people - input_people_minus;
	int yPos;
	int i;

	floor = *pCurrent_floor;
	*pCurrent_floor = input_floor;
	while (1) {
		switch (floor)
		{
		case 1:	yPos = 20;	break;
		case 2:	yPos = 17;	break;
		case 3:	yPos = 14;	break;
		case 4:	yPos = 11;	break;
		case 5:	yPos = 8;	break;
		case 6:	yPos = 5;	break;
		case 7:	yPos = 2;	break;
		}

		Sleep(1500);
		if (floor_gap > 0) {
			if (floor != 1)
				Box(15, yPos + 3);
			Box(14, yPos);
			for (i = 0; i < *pCurrent_people; i++) {
				People_insert(i + 9, yPos);
			}
			if (floor == input_floor)
				break;
			floor++;
		}
		else {
			if (floor != 7)
				Box(15, yPos - 3);
			Box(14, yPos);
			for (i = 0; i < *pCurrent_people; i++) {
				People_insert(i + 9, yPos);
			}
			if (floor == input_floor)
				break;
			floor--;
		}
	}
	Sleep(1000);

	for (i = *pCurrent_people; i > people_gap; i--) {
		People_output(i + 8, yPos);
		Sleep(500);
	}
	*pCurrent_people = *pCurrent_people - input_people_minus;
	for (i = *pCurrent_people; i < *pCurrent_people + input_people_plus; i++) {
		People_insert(i + 9, yPos);
		Sleep(500);
	}
	*pCurrent_people = *pCurrent_people + input_people_plus;
	return yPos;
}

void Box(int color, int yPos) {
	gotoxy(7, yPos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("┌──────┐ \n");
	gotoxy(7, yPos + 1);
	printf("│      │ \n");
	gotoxy(7, yPos + 2);
	printf("└──────┘ \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void People_insert(int xPos, int yPos) {
	gotoxy(xPos, yPos + 1);
	printf("p\n");
}
void People_output(int xPos, int yPos) {
	gotoxy(xPos, yPos + 1);
	printf(" \n");
	gotoxy(xPos + 10, yPos + 1);
	printf("p\n");
}

void gotoxy(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}