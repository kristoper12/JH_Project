#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define NUMLAYER				2
#define NUMLEARNPATTERN			30
#define NUMPREDICTPATTERN		30
#define NUMPREDICTPATTERNFLOAT	30.0
#define NUMTARGET				10
#define NUMINPUT				224
#define NUMNODE					100
#define NUMEPOCH				50000
#define LEARNINGRATE			0.01

typedef struct nueron_ {
	int layer;
	int numnode;
	int numweight;
	float *x;
	float *w;
	float *error;
};

float RandFloat();								// 난수 뽑는 함수 -0.5 ~ 0.5
float Sigmoid(float result);					// 활성화 함수
int ArgMax(float output[]);						// Argument 중 가장 큰 값의 Index 값 구하기


void main() {
	nueron_ nueron[NUMLAYER];
	char str[20];								// 파일 이름
	char temp[10];								// 파일 이름
	char *pch;									// strtok
	char f_input[NUMINPUT * 2];					// 파일 데이터

	int epoch;									// 학습 횟수
	int input[NUMLEARNPATTERN][NUMINPUT];		// 입력값
	int Quiz[NUMPREDICTPATTERN][NUMINPUT];		// 평가 데이터
	int count = 0;								
	int result;									// 평가 답안지
	int index;
	int index_;
	float Y[NUMLEARNPATTERN][NUMTARGET];		// Target
	float target;								// 목표값
	float n;									// 학습률
	float score;								// 평가 점수
	float sum;
	float Delta[NUMTARGET];
	float d_sum[NUMNODE];						// HiddenLayer DeltaSum
	float e[NUMNODE];							// HiddenLayer Error
	float error[NUMTARGET];						// 에러
	float output[NUMTARGET][NUMTARGET];			// 단순 합 결과
	FILE *rfp;

	// 초기화
	srand(time(NULL));
	epoch				= NUMEPOCH;
	n					= LEARNINGRATE;
	nueron[0].numnode	= NUMINPUT + 1;
	nueron[1].numnode	= NUMNODE + 1;

	for (int i = 0; i < NUMLEARNPATTERN; i++) {
		for (int j = 0; j < 10; j++) {
			if ((i % 10) == j)
				Y[i][j] = 1;
			else
				Y[i][j] = 0;
		}
	}

	for (int i = 0; i < NUMLAYER - 1; i++) {
		nueron[i].numweight = nueron[i].numnode * (nueron[i + 1].numnode - 1);
	}
	nueron[NUMLAYER - 1].numweight = nueron[NUMLAYER - 1].numnode * NUMTARGET;

	for (int i = 0; i < NUMLAYER; i++) {
		nueron[i].layer = i + 1;
		nueron[i].x = (float *)malloc(nueron[i].numnode * sizeof(float));
		nueron[i].w = (float *)malloc(nueron[i].numweight * sizeof(float));
		nueron[i].error = (float *)malloc(nueron[i].numweight / nueron[i].numnode * sizeof(float));
		for (int k = 0; k < nueron[i].numweight; k++) {
			nueron[i].w[k] = RandFloat();
		}
		nueron[i].x[0] = 1.0;
	}

	for (int i = 0; i < NUMNODE; i++) {
		d_sum[i] = 0.0;
	}
	// 파일 입출력
	for (int i = 0; i < NUMLEARNPATTERN; i++) {
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

		fgets(f_input, NUMINPUT * 2, rfp);
		pch = strtok(f_input, ",");
		while (pch != NULL) {
			input[i][count] = atoi(pch);
			pch = strtok(NULL, ",");
			count++;
		}
		fclose(rfp);
	}

	for (int i = 0; i < NUMPREDICTPATTERN; i++) {
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

		fgets(f_input, NUMINPUT * 2, rfp);
		pch = strtok(f_input, ",");
		while (pch != NULL) {
			Quiz[i][count] = atoi(pch);
			pch = strtok(NULL, ",");
			count++;
		}
		fclose(rfp);
	}

	// 학습
	printf("\n학습 횟수 = %d\n", epoch);
	printf("학습률 = %f\n", n);
	printf("학습 시작\n");

	printf("숫자 인식 학습\n");
	for (int i = 0; i < epoch; i++) {
		for (int j = 0; j < NUMLEARNPATTERN; j++) {

			// InputLayer Data Input
			index = NUMINPUT + 1;
			for (int k = 1; k < NUMINPUT + 1; k++) {
				nueron[0].x[k] = input[j][k];
			}

			// HiddenLayer Data Input
			for (int k = 1; k < NUMNODE + 1; k++) {
				sum = 0.0;
				for (int u = index; u < NUMINPUT + index + 1; u++) {
					sum = sum + (nueron[0].x[u - index] * nueron[0].w[u]);
				}
				index = index + NUMINPUT + 1;
				nueron[1].x[k] = Sigmoid(sum);
			}


			// 최상위층 Error, Delta, HiddenLayer d_sum
			index = 0;
			index_ = 0;
			for (int k = 0; k < NUMTARGET; k++) {
				sum = 0.0;
				for (int u = index; u < NUMNODE + index + 1; u++) {
					sum = sum + (nueron[1].x[u - index] * nueron[1].w[u]);
				}
				index = index + NUMNODE + 1;
				output[j][k] = Sigmoid(sum);
				error[k] = Y[j][k] - output[j][k];
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
				for (int u = index; u < NUMINPUT + index + 1; u++) {
					nueron[0].w[u] = nueron[0].w[u] + n * nueron[0].x[u - index] * e[k];
				}
				index = index + NUMINPUT + 1;
			}

			// HiddenLayer Weight 갱신
			index = 0;
			for (int k = 0; k < NUMTARGET; k++) {
				for (int u = index; u < nueron[1].numnode + index; u++) {
					nueron[1].w[u] = nueron[1].w[u] + n * nueron[1].x[u - index] * Delta[k];
				}
				index = index + nueron[1].numnode;
			}
		}
		if (i % 10000 == 0) {
			printf("%d 번째 학습중\n", i + 1);
			for (int x = 0; x < NUMTARGET; x++) {
				printf("%d\t", ArgMax(output[x]));
			}
			printf("\n");
		}
	}

	// 평가
	count = 0;
	for (int j = 0; j < NUMPREDICTPATTERN; j++) {
		index = NUMINPUT + 1;
		for (int k = 1; k < NUMINPUT + 1; k++) {
			nueron[0].x[k] = Quiz[j][k];
		}
		for (int k = 1; k < NUMNODE + 1; k++) {
			sum = 0.0;
			for (int u = index; u < NUMINPUT + index + 1; u++) {
				sum = sum + (nueron[0].x[u - index] * nueron[0].w[u]);
			}
			index = index + NUMINPUT + 1;
			nueron[1].x[k] = Sigmoid(sum);
		}
		index = 0;
		for (int k = 0; k < NUMTARGET; k++) {
			sum = 0.0;
			for (int u = index; u < NUMNODE + index + 1; u++) {
				sum = sum + (nueron[1].x[u - index] * nueron[1].w[u]);
			}
			index = index + NUMNODE + 1;
			output[j][k] = Sigmoid(sum);
		}
		result = ArgMax(output[j]);
		if (result == j % 10)
			count++;
	}

	score = count / NUMPREDICTPATTERNFLOAT * 100;
	printf("평가 결과 : %.2f\n", score);

	for (int i = 0; i < NUMLAYER; i++) {
		free(nueron[i].x);
		free(nueron[i].w);
		free(nueron[i].error);
	}
}

int ArgMax(float output[]) {
	float max = output[0];
	int maxindex = 0;

	for (int i = 1; i < NUMTARGET; i++) {
		if (max < output[i]) {
			max = output[i];
			maxindex = i;
		}
	}

	return maxindex;
}

float RandFloat() {
	return (float)rand() / RAND_MAX - 0.5;
}

float Sigmoid(float result) {
	return 1.0 / (1.0 + exp(-result));
}