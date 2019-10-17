#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define PI 3.1415926535897

#define NUM_LAYER						2
#define NUM_TARGET						1
#define NUM_INPUT						1
#define NUM_NODE						10

#define NUM_LEARN_PATTERN				63
#define LEARNING_PATTERN_FLOAT			0.1
#define NUM_PREDICT_PATTERN				63
#define NUM_PREDICT_PATTERN_FLOAT		63.0

#define NUM_EPOCH						2000000
#define LEARNING_RATE					0.01

typedef struct nueron_ {
	int layer;
	int numnode;
	int numweight;
	double *x;
	double *w;
	double *error;
};

double RandDouble();								// 난수 뽑는 함수 -0.5 ~ 0.5
double Sigmoid(double result);						// 활성화 함수
double GetRadian(double num);						// Radian 받는 함수
int ArgMax(double output[]);						// Argument 중 가장 큰 값의 Index 값 구하기


void main() {
	nueron_ nueron[NUM_LAYER];
	char str[20];									// 파일 이름
	char temp[10];									// 파일 이름
	char *pch;										// strtok
	char f_input[NUM_INPUT * 2];					// 파일 데이터

	int epoch;										// 학습 횟수
	double input[NUM_LEARN_PATTERN][NUM_INPUT];		// 입력값
	double Quiz[NUM_PREDICT_PATTERN][NUM_INPUT];	// 평가 데이터
	int count = 0;									
	int result;										// 평가 답안지
	int index;
	int index_;
	double Y[NUM_LEARN_PATTERN][NUM_TARGET];		// Target
	double max;
	double min;
	double target;									// 목표값
	double n;										// 학습률
	double score;									// 평가 점수
	double sum;
	double Delta[NUM_TARGET];
	double d_sum[NUM_NODE + 1];						// HiddenLayer DeltaSum
	double e[NUM_NODE + 1];							// HiddenLayer Error
	double error[NUM_TARGET];						// 에러
	double output[NUM_PREDICT_PATTERN][NUM_TARGET];	// 단순 합 결과
	double cost;
	FILE *rfp;
	FILE *wfp;

	// 초기화
	srand(time(NULL));
	epoch				= NUM_EPOCH;
	n					= LEARNING_RATE;
	nueron[0].numnode	= NUM_INPUT + 1;
	nueron[1].numnode	= NUM_NODE + 1;

	for (int i = 0; i < NUM_LAYER - 1; i++) {
		nueron[i].numweight = nueron[i].numnode * (nueron[i + 1].numnode - 1);
	}
	nueron[NUM_LAYER - 1].numweight = nueron[NUM_LAYER - 1].numnode * NUM_TARGET;

	for (int i = 0; i < NUM_LAYER; i++) {
		nueron[i].layer = i + 1;
		nueron[i].x = (double *)malloc(nueron[i].numnode * sizeof(double));
		nueron[i].w = (double *)malloc(nueron[i].numweight * sizeof(double));
		nueron[i].error = (double *)malloc(nueron[i].numweight / nueron[i].numnode * sizeof(double));
		for (int k = 0; k < nueron[i].numweight; k++) {
			nueron[i].w[k] = RandDouble();
		}
		nueron[i].x[0] = 1.0;
	}

	for (int i = 0; i < NUM_NODE + 1; i++) {
		d_sum[i] = 0.0;
	}
	int k = 0;
	for (double i = 0.0; i < 6.3; i = i + LEARNING_PATTERN_FLOAT) {
		input[k++][0] = i;
		//Quiz[k++][0] = i;
	}
	k = 0;
	for (double i = 0.0; i < 6.3; i = i + 0.1) {
		Quiz[k++][0] = i;
	}
	for (int i = 0; i < NUM_LEARN_PATTERN; i++) {
		Y[i][0] = sin(input[i][0]) + (input[i][0] * input[i][0]) - (7 * input[i][0]) + (10);
	}

	max = Y[0][0];
	min = Y[0][0];
	for (int i = 0; i < NUM_LEARN_PATTERN; i++) {
		if (max < Y[i][0]) {
			max = Y[i][0];
		}
		
		if (min > Y[i][0]) {
			min = Y[i][0];
		}
	}

	for (int i = 0; i < NUM_LEARN_PATTERN; i++) {
		Y[i][0] = (Y[i][0] - min) / (max - min);
	}

	/*for (int i = 0; i < NUM_LEARN_PATTERN; i++) {
		printf("%f\t", Y[i][0]);
	}
	printf("\n");*/

	/*
	// 파일 입출력
	for (int i = 0; i < NUM_LEARN_PATTERN; i++) {
		count = 0;
		if (i / 10 == 0) {
			strcpy(str, "NumberJH\\");
		}
		else if (i / 10 == 1) {
			strcpy(str, "NumberCW\\");
		}
		else if (i / 10 == 2) {
			strcpy(str, "NumberGH\\");
		}
		itoa(i % 10, temp, 10);
		strcat(str, temp);
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

	for (int i = 0; i < NUM_PREDICT_PATTERN; i++) {
		count = 0;
		if (i / 10 == 0) {
			strcpy(str, "NumberGH\\");
		}
		else if (i / 10 == 1) {
			strcpy(str, "NumberJH\\");
		}
		else if (i / 10 == 2) {
			strcpy(str, "NumberCW\\");
		}
		itoa(i % 10, temp, 10);
		strcat(str, temp);
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
	*/

	// 학습

	printf("\n학습 횟수 = %d\n", epoch);
	printf("학습률 = %f\n", n);
	printf("학습 시작\n");

	printf("숫자 인식 학습\n");

	wfp = fopen("result.txt", "w");
	for (int a = 0; a < 10; a++) {
		for (int i = 0; i < NUM_LAYER; i++) {
			for (int k = 0; k < nueron[i].numweight; k++) {
				nueron[i].w[k] = RandDouble();
			}
		}
		for (int i = 0; i < NUM_NODE + 1; i++) {
			d_sum[i] = 0.0;
		}

		
		printf("%d 번째\n\n", a + 1);
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


				// 최상위층 Error, Delta, HiddenLayer d_sum
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

				// d_sum 을 통해 HiddenLayer 의 Error 계산
				// 새로 구한 Error 를 통해 weight 갱신
				// InputLayer Weight 갱신
				index = 0;
				for (int k = 1; k < nueron[1].numnode; k++) {
					e[k] = d_sum[k] * nueron[1].x[k] * (1 - nueron[1].x[k]);
					for (int u = index; u < NUM_INPUT + index + 1; u++) {
						nueron[0].w[u] = nueron[0].w[u] + n * nueron[0].x[u - index] * e[k];
					}
					index = index + NUM_INPUT + 1;
				}

				// HiddenLayer Weight 갱신
				index = 0;
				for (int k = 0; k < NUM_TARGET; k++) {
					for (int u = index; u < nueron[1].numnode + index; u++) {
						// 기훈이는 Delta 를 안곱하고 Error 를 곱했음 왜지?
						// nueron[1].w[u] = nueron[1].w[u] + n * nueron[1].x[u - index] * Delta[k];
						nueron[1].w[u] = nueron[1].w[u] + n * nueron[1].x[u - index] * error[k];
					}
					index = index + nueron[1].numnode;
				}
				cost = cost + (error[0] * error[0]);
			}
			if (cost < 0.1) {
				printf("cost가 0.1 미만이므로 학습을 종료합니다.\n");
				break;
			}
			if (i % 500000 == 0) {
				//printf("%d 번째 학습중\n", i + 1);
				for (int x = 0; x < NUM_TARGET; x++) {
					printf("cost : %.2f\t", cost);
				}
				printf("\n");
			}
		}

		// 평가
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
				output[j][k] = (output[j][k] * (max - min)) + min;
				fprintf(wfp, "%f\n", output[j][k]);
			}
		}
		fprintf(wfp, "\n");
	}

	printf("평가 결과 생성 완료 : result.txt\n");
	fclose(wfp);

	for (int i = 0; i < NUM_LAYER; i++) {
		free(nueron[i].x);
		free(nueron[i].w);
		free(nueron[i].error);
	}
}

int ArgMax(double output[]) {
	double max = output[0];
	int maxindex = 0;

	for (int i = 1; i < NUM_TARGET; i++) {
		if (max < output[i]) {
			max = output[i];
			maxindex = i;
		}
	}

	return maxindex;
}

double RandDouble() {
	return (double)rand() / RAND_MAX - 0.5;
}

double Sigmoid(double result) {
	return 1.0 / (1.0 + exp(-result));
}

double GetRadian(double num) {
	return num * (PI / 180.0);
}