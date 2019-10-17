#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float NET(int bias, int x1, int x2);
int Thresholding(float result);
int AND(int x1, int x2);
int OR(int x1, int x2);
int XOR(int x1, int x2);
void refreshWeight(int bias, int x1, int x2, int result, float n);

int flag;				// 1 �̸� AND 2 �̸� OR 3 �̸� XOR
int error;				// ����
float w1, w2, w3;		// ����ġ

void main() {
	int bias;			// y ����
	int epoch;			// �н� Ƚ��
	int input[4][2] = {
		{0, 0},
		{0, 1},
		{1, 0},
		{1, 1}
	};					// �Է°�
	int cnt;
	int x1, x2;			// �� ������
	float n;			// �н���
	float threshold;	// �Ӱ�ġ
	float result;		// �ܼ� �� ���
	float score;		// �� ����

	// �ʱ�ȭ
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
	// �н�
	printf("\n�н� Ƚ�� = %d\n", epoch);
	printf("����ġ = w1 : %.1f, w2 : %.1f, w3 : %.1f\n", w1, w2, w3);
	printf("�н��� = %.1f\n", n);
	printf("�Ӱ�ġ = %.1f\n\n", threshold);
	printf("�н� ����\n");
	if (flag == 1)
		printf("AND �н�\n");
	else if (flag == 2)
		printf("OR �н�\n");
	else if (flag == 3)
		printf("XOR �н�\n");
	for (int i = 0; i < epoch; i++) {
		cnt = 0;
		printf("%d ��° �н���\n", i + 1);
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
			printf("\nerror = 0\t�н��Ϸ�\n\n");
			break;
		}
	}
	if (cnt != 4)
		printf("�н� �Ϸ�\n\n");

	// ��
	cnt = 0;
	printf("�� ����\n");
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
	printf("�� �Ϸ�\n");
	printf("�� ���� : %.2f\n", cnt / 20.0 * 100);
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