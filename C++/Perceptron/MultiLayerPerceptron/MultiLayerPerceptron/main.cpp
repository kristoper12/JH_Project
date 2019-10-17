#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUMLAYER 2

typedef struct nueron_ {
	int layer;
	int numnode;
	int numweight;
	float *x;
	float *w;
	float *error;
};

float RandFloat();
float NET(int n1, int layer, int bias, float x[], float w[], int numnode);
int Thresholding(float result);
int AND(int x1, int x2);
int OR(int x1, int x2);
int XOR(int x1, int x2);
void refreshWeight(int layer, int bias, float error[], float n, float x[], float w[]);
float Sigmoid(float result);

int flag;				// 1 이면 AND 2 이면 OR 3 이면 XOR
float error;				// 에러



void main() {
	nueron_ nueron[NUMLAYER];
	float bias;			// y 절편
	int epoch;			// 학습 횟수
	float input[4][2] = {
		{ 0, 0 },
		{ 0, 1 },
		{ 1, 0 },
		{ 1, 1 }
	};					// 입력값
	float Y[4] = {
		0, 1, 1, 0
	};
	float cnt;
	float target;			// 목표값
	float predict;		// 예측값
	float x1, x2;
	float x[2];
	float n;			// 학습률
	float threshold;	// 임계치
	float result;		// 단순 합 결과
	float score;		// 평가 점수
	float Delta;
	float d_sum;
	float m1, m2;
	float w11, w12, w13, w14, w15, w16, w21, w22, w23;
	FILE *wfp;

	// 초기화
	//srand(time(NULL));
	/*w11 = 0.1; w12 = 0.1; w13 = 0.1; w14 = 0.1; w15 = 0.1; w16 = 0.1;
	w21 = 0.1; w22 = 0.1; w23 = 0.1;*/
	bias = 1.0;
	epoch = 10000000;
	n = 0.0001;
	threshold = 0.5;
	nueron[0].numweight = 6;
	nueron[1].numweight = 3;

	w11 = RandFloat();
	w12 = RandFloat();
	w13 = RandFloat();
	w14 = RandFloat();
	w15 = RandFloat();
	w16 = RandFloat();
	w21 = RandFloat();
	w22 = RandFloat();
	w23 = RandFloat();

	for (int i = 0; i < NUMLAYER; i++) {
		nueron[i].layer = i + 1;
		nueron[i].numnode = 2;
		nueron[i].x = (float *)malloc(nueron[i].numnode * sizeof(float));
		nueron[i].w = (float *)malloc(nueron[i].numweight * sizeof(float));
		nueron[i].error = (float *)malloc(nueron[i].numweight / (nueron[i].numnode + 1) * sizeof(float));
		for (int k = 0; k < nueron[i].numweight; k++) {
			nueron[i].w[k] = RandFloat();
		}
	}	

	// 학습
	printf("\n학습 횟수 = %d\n", epoch);
	printf("학습률 = %.1f\n", n);
	printf("임계치 = %.1f\n\n", threshold);
	printf("학습 시작\n");
	
	printf("XOR 학습\n");
	for (int i = 0; i < epoch; i++) {
		cnt = 0;
		//printf("%d 번째 학습중\n", i + 1);
		for (int j = 0; j < 4; j++) {
			m1 = Sigmoid(bias * w11 + input[j][0] * w12 + input[j][1] * w13);
			m2 = Sigmoid(bias * w14 + input[j][0] * w15 + input[j][1] * w16);
			result = Sigmoid(bias * w21 + m1 * w22 + m2 * w23);

			error = Y[j] - result;

			/*w11 = w11 + n * bias		* (error * w22);
			w12 = w12 + n * input[j][0] * (error * w22);
			w13 = w13 + n * input[j][1] * (error * w22);
			w14 = w14 + n * bias		* (error * w23);
			w15 = w15 + n * input[j][0] * (error * w23);
			w16 = w16 + n * input[j][1] * (error * w23);

			w21 = w21 + n * bias	* error;
			w22 = w22 + n * m1		* error;
			w23 = w23 + n * m2		* error;*/

			Delta = error * result * (1 - result);
			d_sum = Delta * w22;

			w11 = w11 + n * bias		* (d_sum * m1 * (1 - m1));
			w12 = w12 + n * input[j][0] * (d_sum * m1 * (1 - m1));
			w13 = w13 + n * input[j][1] * (d_sum * m1 * (1 - m1));

			d_sum = Delta * w23;
			w14 = w14 + n * bias		* (d_sum * m2 * (1 - m2));
			w15 = w15 + n * input[j][0] * (d_sum * m2 * (1 - m2));
			w16 = w16 + n * input[j][1] * (d_sum * m2 * (1 - m2));

			w21 = w21 + n * bias		* Delta;
			w22 = w22 + n * m1			* Delta;
			w23 = w23 + n * m2			* Delta;
			//nueron[0].x[0] = input[j][0];
			//nueron[0].x[1] = input[j][1];

			//nueron[1].x[0] = Sigmoid(NET(1, 1, bias, nueron[0].x, nueron[0].w, nueron[0].numnode));
			//nueron[1].x[1] = Sigmoid(NET(2, 1, bias, nueron[0].x, nueron[0].w, nueron[0].numnode));

			//result = Sigmoid(NET(1, 2, bias, nueron[1].x, nueron[1].w, nueron[1].numnode));
			//target = Y[j];
			////target = XOR(input[j][0], input[j][1]);
			//predict = result;
			////predict = Thresholding(result);
			//if (target != predict) {
			//	nueron[1].error[0] = target - predict;
			//	//printf("target : %f, predict : %f\n", target, predict);
			//	//nueron[1].error[0] = nueron[1].error[0] * nueron[1].error[0];
			//	/*Delta = nueron[1].error[0] * predict * (1 - predict);

			//	nueron[0].error[0] = Delta * nueron[1].w[1];
			//	nueron[0].error[1] = Delta * nueron[1].w[2];*/

			//	nueron[0].error[0] = nueron[1].error[0] * nueron[1].w[1];//
			//	nueron[0].error[1] = nueron[1].error[0] * nueron[1].w[2];//
			//	/*for (int z = 0; z < 2; z++) {
			//		printf("w = ");
			//		for (int k = 0; k < nueron[z].numweight; k++) {
			//			printf("%f, ", nueron[z].w[k]);
			//		}
			//		printf("\n");
			//	}
			//	printf("error = %f\t%f\t%f\n", nueron[0].error[0], nueron[0].error[1], nueron[1].error[0]);*/
			//	refreshWeight(2, 1, nueron[1].error, n, nueron[1].x, nueron[1].w);
			//	refreshWeight(1, 1, nueron[0].error, n, nueron[0].x, nueron[0].w);
			//	/*for (int z = 0; z < 2; z++) {
			//		printf("w = ");
			//		for (int k = 0; k < nueron[z].numweight; k++) {
			//			printf("%f, ", nueron[z].w[k]);
			//		}
			//		printf("\n");
			//	}*/
				//cnt = cnt + nueron[1].error[0];
			/*}
			else {
				cnt++;
			}*/
		}
		if (i % 1000 == 0) {
			printf("%d 번째 학습중\n", i + 1);
			printf("error = %.2f\n", error * error);
			//printf("w = %f, %f, %f, %f, %f, %f\n", w11, w12, w13, w14, w15, w16);
			//printf("w = %f, %f, %f\n", w21, w22, w23);
			printf("Delta = %f\n", Delta);
			//printf("error = %.2f\n", nueron[1].error[0]);
			/*for (int z = 0; z < 2; z++) {
				printf("w = ");
				for (int k = 0; k < nueron[z].numweight; k++) {
					printf("%f, ", nueron[z].w[k]);
				}
				printf("\n");
			}*/
		}
		/*if (cnt < 0.1)
			break;*/
		/*if (cnt == 4) {
			printf("\nerror < 0.1\t학습완료\n\n");
			break;
		}*/
	}
	if (cnt != 4)
		printf("학습 완료\n\n");

	// 평가
	cnt = 0;
	wfp = fopen("a.txt", "w");
	for (float i = 0.0; i <= 1.0; i = i + 0.1) {
		for (float j = 0.0; j <= 1.0; j = j + 0.1) {
			m1 = Sigmoid(bias * w11 + i * w12 + j * w13);
			m2 = Sigmoid(bias * w14 + i * w15 + j * w16);
			result = Sigmoid(bias * w21 + m1 * w22 + m2 * w23);

			printf("%.2f\t", result);
			fprintf(wfp, "%.2f\t", result);
		}
		fprintf(wfp, "\n");
		printf("\n");
	}
	fclose(wfp);
	/*printf("평가 시작\n");
	for (int i = 0; i < 20; i++) {
		x1 = rand() % 2;
		x2 = rand() % 2;
		x[0] = (float)x1;
		x[1] = (float)x2;

		x[0] = NET(1, 1, bias, x, nueron[0].w, nueron[0].numnode);
		x[1] = NET(2, 1, bias, x, nueron[0].w, nueron[0].numnode);
		
		result = NET(1, 2, bias, x, nueron[1].w, nueron[1].numnode);
		target = XOR(x1, x2);
		predict = Sigmoid(result);
		predict = Thresholding(predict);
		if (target == predict) {
			cnt++;
		}
	}
	printf("평가 완료\n");
	printf("평가 점수 : %.2f\n", cnt / 20.0 * 100);*/
	//	cnt = 0;
	//	printf("%d 번째 학습중\n", i + 1);
	//	for (int j = 0; j < 4; j++) {
	//		result = NET(bias, input[j][0], input[j][1]);
	//		if (flag == 1) {		// AND
	//			if (AND(input[j][0], input[j][1]) != Thresholding(result)) {
	//				refreshWeight(bias, input[j][0], input[j][1], Thresholding(result), n);
	//			}
	//			else
	//				cnt++;
	//		}
	//		else if (flag == 2) {	// OR
	//			if (OR(input[j][0], input[j][1]) != Thresholding(result)) {
	//				refreshWeight(bias, input[j][0], input[j][1], Thresholding(result), n);
	//			}
	//			else
	//				cnt++;
	//		}
	//		else if (flag == 3) {	// XOR
	//			if (XOR(input[j][0], input[j][1]) != Thresholding(result)) {
	//				refreshWeight(bias, input[j][0], input[j][1], Thresholding(result), n);
	//			}
	//			else
	//				cnt++;
	//		}
	//	}
	//	if (cnt == 4) {
	//		printf("\nerror = 0\t학습완료\n\n");
	//		break;
	//	}
	//}
	//if (cnt != 4)
	//	printf("학습 완료\n\n");
	//// 평가
	//cnt = 0;
	//printf("평가 시작\n");
	//for (int i = 0; i < 20; i++) {
	//	x1 = rand() % 2;
	//	x2 = rand() % 2;
	//	result = NET(bias, x1, x2);
	//	if (flag == 1) {
	//		if (AND(x1, x2) == Thresholding(result))
	//			cnt++;
	//	}
	//	else if (flag == 2) {
	//		if (OR(x1, x2) == Thresholding(result))
	//			cnt++;
	//	}
	//	else if (flag == 3) {
	//		if (XOR(x1, x2) == Thresholding(result))
	//			cnt++;
	//	}
	//}
	//printf("평가 완료\n");
	//printf("평가 점수 : %.2f\n", cnt / 20.0 * 100);
}

float RandFloat() {
	int flag;
	flag = rand() % 2;
	if (flag == 1)
		return ((float)rand() / RAND_MAX);
	else if (flag == 0)
		return ((float)rand() / RAND_MAX) * -1;
}

//int AND(int x1, int x2) {
//	if (x1 == 0 || x2 == 0)
//		return 0;
//	else if (x1 == 1 && x2 == 1)
//		return 1;
//}
//
//int OR(int x1, int x2) {
//	if (x1 == 0 && x2 == 0)
//		return 0;
//	else if (x1 == 1 || x2 == 1)
//		return 1;
//}

//int XOR(int x1, int x2) {
//	if (x1 == x2)
//		return 0.1;
//	else if (x1 != x2)
//		return 0.9;
//}

float NET(int n1, int layer, int bias, float x[], float w[], int numnode) {
	float sum = 0.0;

	if (layer == 1) {
		if (n1 == 1) {
			return ((bias * w[0]) + (x[0] * w[1]) + (x[1] * w[2]));
		}
		else if (n1 == 2) {
			return ((bias * w[3]) + (x[0] * w[4]) + (x[1] * w[5]));
		}
	}
	else {
		sum = sum + bias * w[0];
		for (int i = 0; i < numnode; i++) {
			sum = sum + x[i] * w[i + 1];
		}
		return sum;
	}
}

int Thresholding(float result) {
	if (result >= 0.5)
		return 1;
	else
		return 0;
}

float Sigmoid(float result) {
	return 1.0 / (1.0 + exp(-result));
}

void refreshWeight(int layer, int bias, float error[], float n, float x[], float w[]) {

	if (layer == 1) {
		w[0] = w[0] + (n * bias * (error[0]));
		w[1] = w[1] + (n * x[0] * (error[0]));
		w[2] = w[2] + (n * x[1] * (error[0]));
		w[3] = w[3] + (n * bias * (error[1]));
		w[4] = w[4] + (n * x[0] * (error[1]));
		w[5] = w[5] + (n * x[1] * (error[1]));
	}
	else {
		w[0] = w[0] + (n * bias * (error[0]));
		w[1] = w[1] + (n * x[0] * (error[0]));
		w[2] = w[2] + (n * x[1] * (error[0]));
	}
}