#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float NET(int bias, int x1, int x2);
int Thresholding(float result);
int AND(int x1, int x2);
int OR(int x1, int x2);
int XOR(int x1, int x2);
void refreshWeight(int bias, int x1, int x2, int result, float n);

int flag;				// 1 이면 AND 2 이면 OR 3 이면 XOR
int error;				// 에러
float w1, w2, w3;		// 가중치

void main() {
	int bias;			// y 절편
	int epoch;			// 학습 횟수
	int input[4][2] = {
		{0, 0},
		{0, 1},
		{1, 0},
		{1, 1}
	};					// 입력값
	int cnt;
	int x1, x2;			// 평가 데이터
	float n;			// 학습률
	float threshold;	// 임계치
	float result;		// 단순 합 결과
	float score;		// 평가 점수

	// 초기화
	srand(time(NULL));
	bias = 1;
	epoch = 1000;
	w1 = 0.1; w2 = 0.3; w3 = -0.2;
	n = 0.1;
	threshold = 0.5;

	printf("1. AND\n");
	printf("2. OR\n");
	printf("3. XOR\n");
	printf("> ");
	scanf("%d", &flag);
	// 학습
	printf("\n학습 횟수 = %d\n", epoch);
	printf("가중치 = w1 : %.1f, w2 : %.1f, w3 : %.1f\n", w1, w2, w3);
	printf("학습률 = %.1f\n", n);
	printf("임계치 = %.1f\n\n", threshold);
	printf("학습 시작\n");
	if (flag == 1)
		printf("AND 학습\n");
	else if (flag == 2)
		printf("OR 학습\n");
	else if (flag == 3)
		printf("XOR 학습\n");
	for (int i = 0; i < epoch; i++) {
		cnt = 0;
		printf("%d 번째 학습중\n", i + 1);
		for (int j = 0; j < 4; j++) {
			result = NET(bias, input[j][0], input[j][1]);
			if (flag == 1) {		// AND
				if (AND(input[j][0], input[j][1]) != Thresholding(result)) {
					refreshWeight(bias, input[j][0], input[j][1], Thresholding(result), n);
				}
				else
					cnt++;
			}
			else if (flag == 2) {	// OR
				if (OR(input[j][0], input[j][1]) != Thresholding(result)) {
					refreshWeight(bias, input[j][0], input[j][1], Thresholding(result), n);
				}
				else
					cnt++;
			}
			else if (flag == 3) {	// XOR
				if (XOR(input[j][0], input[j][1]) != Thresholding(result)) {
					refreshWeight(bias, input[j][0], input[j][1], Thresholding(result), n);
				}
				else
					cnt++;
			}
		}
		if (cnt == 4) {
			printf("\nerror = 0\t학습완료\n\n");
			break;
		}
	}
	if (cnt != 4)
		printf("학습 완료\n\n");

	// 평가
	cnt = 0;
	printf("평가 시작\n");
	for (int i = 0; i < 20; i++) {
		x1 = rand() % 2;
		x2 = rand() % 2;
		result = NET(bias, x1, x2);

		if (flag == 1) {
			if (AND(x1, x2) == Thresholding(result))
				cnt++;
		}
		else if (flag == 2) {
			if (OR(x1, x2) == Thresholding(result))
				cnt++;
		}
		else if (flag == 3) {
			if (XOR(x1, x2) == Thresholding(result))
				cnt++;
		}
	}
	printf("평가 완료\n");
	printf("평가 점수 : %.2f\n", cnt / 20.0 * 100);
}

int AND(int x1, int x2) {
	if (x1 == 0 || x2 == 0)
		return 0;
	else if (x1 == 1 && x2 == 1)
		return 1;
}

int OR(int x1, int x2) {
	if (x1 == 0 && x2 == 0)
		return 0;
	else if (x1 == 1 || x2 == 1)
		return 1;
}

int XOR(int x1, int x2) {
	if (x1 == x2)
		return 0;
	else if (x1 != x2)
		return 1;
}

float NET(int bias, int x1, int x2) {
	return ((bias * w1) + (x1 * w2) + (x2 * w3));
}

int Thresholding(float result) {
	if (result >= 0.5)
		return 1;
	else
		return 0;
}

void refreshWeight(int bias, int x1, int x2, int result, float n) {
	int target;

	if (flag == 1)					// AND
		target = AND(x1, x2);
	else if (flag == 2)				// OR
		target = OR(x1, x2);
	else if (flag == 3)				// XOR
		target = XOR(x1, x2);
	
	error = target - result;

	w1 = w1 + (n * bias * (error));
	w2 = w2 + (n * x1 * (error));
	w3 = w3 + (n * x2 * (error));
}