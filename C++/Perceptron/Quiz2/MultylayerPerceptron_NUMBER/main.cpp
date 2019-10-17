#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define NUM_COUNT						3

#define NUM_LAYER						2
#define NUM_TARGET						3
#define NUM_INPUT						224
#define NUM_NODE						300

#define NUM_LEARN_PATTERN				3
#define NUM_PREDICT_PATTERN				3
#define NUM_PREDICT_PATTERN_FLOAT		3.0

#define NUM_EPOCH						100000
#define LEARNING_RATE					0.0001

typedef struct nueron_ {
	int layer;
	int numnode;
	int numweight;
	float *x;
	float *w;
	float *error;
};

float RandFloat();									// ���� �̴� �Լ� -0.5 ~ 0.5
float Sigmoid(float result);						// Ȱ��ȭ �Լ�
int ArgMax(float output[]);							// Argument �� ���� ū ���� Index �� ���ϱ�
void CreateRandNum(int arr[]);


void main() {
	nueron_ nueron[NUM_LAYER];
	char str[20];									// ���� �̸�
	char temp1[10];									// ���� �̸�
	char temp2[10];
	char *pch;										// strtok
	char f_input[NUM_INPUT * 2];					// ���� ������
	int rand_array[6];

	int epoch;										// �н� Ƚ��
	float input[NUM_LEARN_PATTERN][NUM_INPUT];		// �Է°�
	float Quiz[NUM_PREDICT_PATTERN][NUM_INPUT];		// �� ������
	int count = 0;
	int result;										// �� �����
	int index;
	int index_;
	float Y[NUM_LEARN_PATTERN][NUM_TARGET];			// Target
	float target;									// ��ǥ��
	float n;										// �н���
	float score;									// �� ����
	float sum;
	float Delta[NUM_TARGET];
	float d_sum[NUM_NODE + 1];						// HiddenLayer DeltaSum
	float e[NUM_NODE + 1];							// HiddenLayer Error
	float error[NUM_TARGET];						// ����
	float output[NUM_PREDICT_PATTERN][NUM_TARGET];	// �ܼ� �� ���
	float cost;
	FILE *rfp;
	FILE *wfp;

	// �ʱ�ȭ
	//srand(time(NULL));
	epoch = NUM_EPOCH;
	n = LEARNING_RATE;
	nueron[0].numnode = NUM_INPUT + 1;
	nueron[1].numnode = NUM_NODE + 1;

	for (int i = 0; i < NUM_LEARN_PATTERN; i++) {
		for (int j = 0; j < NUM_COUNT; j++) {
			if ((i % NUM_COUNT) == j)
				Y[i][j] = 1;
			else
				Y[i][j] = 0;
		}
	}

	for (int i = 0; i < NUM_LAYER - 1; i++) {
		nueron[i].numweight = nueron[i].numnode * (nueron[i + 1].numnode - 1);
	}
	nueron[NUM_LAYER - 1].numweight = nueron[NUM_LAYER - 1].numnode * NUM_TARGET;

	for (int i = 0; i < NUM_LAYER; i++) {
		nueron[i].layer = i + 1;
		nueron[i].x = (float *)malloc(nueron[i].numnode * sizeof(float));
		nueron[i].w = (float *)malloc(nueron[i].numweight * sizeof(float));
		nueron[i].error = (float *)malloc(nueron[i].numweight / nueron[i].numnode * sizeof(float));
		for (int k = 0; k < nueron[i].numweight; k++) {
			nueron[i].w[k] = RandFloat();
		}
		nueron[i].x[0] = 1.0;
	}

	for (int i = 0; i < NUM_NODE + 1; i++) {
		d_sum[i] = 0.0;
	}

	// ���� �����
	CreateRandNum(rand_array);
	for (int k = 0; k < NUM_COUNT; k++) {
		for (int i = 0; i < NUM_LEARN_PATTERN; i++) {
			count = 0;

			strcpy(str, "Number");
			itoa(rand_array[k] + 1, temp1, 10);
			strcat(str, temp1);
			strcat(str, "\\");

			itoa(i % NUM_COUNT + 1, temp2, 10);
			strcat(str, temp2);
			strcat(str, ".txt");
			rfp = fopen(str, "r");

			fgets(f_input, NUM_INPUT * 2, rfp);
			pch = strtok(f_input, ",");
			while (pch != NULL) {
				input[i][count] = atoi(pch);
				pch = strtok(NULL, ",");
				count++;
			}
			fclose(rfp);
		}
	}

	for (int k = 0; k < NUM_COUNT; k++) {
		for (int i = 0; i < NUM_PREDICT_PATTERN; i++) {
			count = 0;

			strcpy(str, "Number");
			itoa(rand_array[k] + 1, temp1, 10);
			strcat(str, temp1);
			strcat(str, "\\");

			itoa(i % NUM_COUNT + 1, temp2, 10);
			strcat(str, temp2);
			strcat(str, ".txt");
			rfp = fopen(str, "r");

			fgets(f_input, NUM_INPUT * 2, rfp);
			pch = strtok(f_input, ",");
			while (pch != NULL) {
				Quiz[i][count] = atoi(pch);
				pch = strtok(NULL, ",");
				count++;
			}
			fclose(rfp);
		}
	}


	// �н�
	printf("\n�н� Ƚ�� = %d\n", epoch);
	printf("�н��� = %f\n", n);
	printf("�н� ����\n");

	printf("���� �ν� �н�\n");
	for (int i = 0; i < epoch; i++) {
		cost = 0.0;
		for (int j = 0; j < NUM_LEARN_PATTERN; j++) {

			// InputLayer Data Input
			for (int k = 0; k < NUM_INPUT; k++) {
				nueron[0].x[k + 1] = input[j][k];
			}

			// HiddenLayer Data Input
			index = 0;
			for (int k = 1; k < NUM_NODE + 1; k++) {
				sum = 0.0;
				for (int u = index; u < NUM_INPUT + index + 1; u++) {
					sum = sum + (nueron[0].x[u - index] * nueron[0].w[u]);
				}
				index = index + NUM_INPUT + 1;
				//nueron[1].x[k] = sum;
				nueron[1].x[k] = Sigmoid(sum);
				//printf("%f\t", nueron[1].x[k]);
			}
			//printf("\n");


			// �ֻ����� Error, Delta, HiddenLayer d_sum
			index = 0;
			index_ = 0;
			for (int k = 0; k < NUM_TARGET; k++) {
				sum = 0.0;
				for (int u = index; u < NUM_NODE + index + 1; u++) {
					sum = sum + (nueron[1].x[u - index] * nueron[1].w[u]);
				}
				index = index + NUM_NODE + 1;
				//output[j][k] = sum;
				output[j][k] = Sigmoid(sum);
				error[k] = Y[j][k] - output[j][k];
				//printf("Error : %f\tTarget : %f\tPredict : %f\n", error[k], Y[j][k], output[j][k]);
				Delta[k] = error[k] * output[j][k] * (1 - output[j][k]);
				for (int x = 1 + index_; x < nueron[1].numnode + index_; x++) {
					d_sum[x - index_] = d_sum[x - index_] + Delta[k] * nueron[1].w[x];
				}
				index_ = index_ + nueron[1].numnode;
			}

			// d_sum �� ���� HiddenLayer �� Error ���
			// ���� ���� Error �� ���� weight ����
			// InputLayer Weight ����
			index = 0;
			for (int k = 1; k < nueron[1].numnode; k++) {
				e[k] = d_sum[k] * nueron[1].x[k] * (1 - nueron[1].x[k]);
				for (int u = index; u < NUM_INPUT + index + 1; u++) {
					nueron[0].w[u] = nueron[0].w[u] + n * nueron[0].x[u - index] * e[k];
				}
				index = index + NUM_INPUT + 1;
			}

			// HiddenLayer Weight ����
			index = 0;
			for (int k = 0; k < NUM_TARGET; k++) {
				for (int u = index; u < nueron[1].numnode + index; u++) {
					nueron[1].w[u] = nueron[1].w[u] + n * nueron[1].x[u - index] * Delta[k];
				}
				index = index + nueron[1].numnode;
			}
			cost = cost + (error[0] * error[0]);
		}
		if (cost < 0.1) {
			printf("cost�� 0.1 �̸��̹Ƿ� �н��� �����մϴ�.\n");
			break;
		}
		if (i % 10000 == 0) {
			printf("%d ��° �н���\n", i + 1);
			for (int x = 0; x < NUM_TARGET; x++) {
				printf("%d\t", ArgMax(output[x]));
			}
			printf("\n");
		}
	}

	// ��
	count = 0;
	for (int j = 0; j < NUM_PREDICT_PATTERN; j++) {


		for (int k = 0; k < NUM_INPUT; k++) {
			nueron[0].x[k + 1] = Quiz[j][k];
		}

		index = 0;
		for (int k = 1; k < NUM_NODE + 1; k++) {
			sum = 0.0;
			for (int u = index; u < NUM_INPUT + index + 1; u++) {
				sum = sum + (nueron[0].x[u - index] * nueron[0].w[u]);
			}
			index = index + NUM_INPUT + 1;
			//nueron[1].x[k] = sum;
			nueron[1].x[k] = Sigmoid(sum);
		}

		index = 0;
		for (int k = 0; k < NUM_TARGET; k++) {
			sum = 0.0;
			for (int u = index; u < NUM_NODE + index + 1; u++) {
				sum = sum + (nueron[1].x[u - index] * nueron[1].w[u]);
			}

			index = index + NUM_NODE + 1;
			//output[j][k] = sum;
			output[j][k] = Sigmoid(sum);
		}
		result = ArgMax(output[j]);
		if (result == (j % NUM_COUNT) + 1)
			count++;

	}

	score = count / NUM_PREDICT_PATTERN_FLOAT * 100;
	printf("�� ��� : %.2f\n", score);

	for (int i = 0; i < NUM_LAYER; i++) {
		free(nueron[i].x);
		free(nueron[i].w);
		free(nueron[i].error);
	}
}

int ArgMax(float output[]) {
	float max = output[0];
	int maxindex = 0;

	for (int i = 1; i < NUM_TARGET; i++) {
		if (max < output[i]) {
			max = output[i];
			maxindex = i;
		}
	}

	return maxindex + 1;
}

float RandFloat() {
	return (float)rand() / RAND_MAX - 0.5;
}

float Sigmoid(float result) {
	return 1.0 / (1.0 + exp(-result));
}

void CreateRandNum(int arr[]) {
	int cnt = 0;
	int num;
	int flag = 0;

	while (cnt != 6) {
		num = rand() % 6;
		for (int i = 0; i < 6; i++) {
			if (num != arr[i]) {
				flag = 0;
			}
			else {
				flag = 1;
				break;
			}
		}
		
		if (flag == 0) {
			arr[cnt] = num;
			cnt++;
		}
	}
}