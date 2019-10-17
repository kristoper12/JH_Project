#include <stdio.h>

//집값과 집의 크기(평수)의 관계가 아래 데이터와 같을 때 17평형 집의 값을
//선형회귀분석으로 구하라.
//
//
//(크기, 가격) : (14, 127), (21, 140), (26, 151), (32, 175), (36, 180)
#define NUMDATA			5
#define NUMDATAFLOAT	5.0
// x 는 독립변수 y 는 종속변수
void main() {
	float alpha;					// 기울기
	float beta;						// y 절편
	float R;						// 결정계수
	float SSR;						// 회귀 제곱의 합
	float SST;						// 총 제곱의 합

	float x_d[NUMDATA];				// x 편차
	float y_d[NUMDATA];				// y 편차
	float yHat_d[NUMDATA];			// y^ 편차

	float x_avg;					// x 평균
	float y_avg;					// y 평균

	float d_sum = 0.0;				// x 편차와 y 편차의 곱들의 합

	float x_d_pow_sum = 0.0;		// x 편차 제곱 합
	float y_d_pow_sum = 0.0;		// y 편차 제곱 합
	float yHat_d_pow_sum = 0.0;		// y^ 편차 제곱 합

	int x_sum = 0;					// x 합
	int y_sum = 0;					// y 합

	int input[NUMDATA][2] = {
		{14, 127},
		{21, 140},
		{26, 151},
		{32, 175},
		{36, 180}
	};								// 입력 데이터
	float yHat_input[NUMDATA];		// 회귀식으로 인해 바뀐 새로운 y 값

	// x 와 y 의 합
	for (int i = 0; i < NUMDATA; i++) {
		x_sum = x_sum + input[i][0];
		y_sum = y_sum + input[i][1];
	}

	// x 와 y 의 평균
	x_avg = x_sum / NUMDATAFLOAT;
	y_avg = y_sum / NUMDATAFLOAT;

	for (int i = 0; i < NUMDATA; i++) {
		// x 와 y 의 편차
		x_d[i] = input[i][0] - x_avg;
		y_d[i] = input[i][1] - y_avg;

		// x 편차와 y 편차의 곱들의 합
		d_sum = d_sum + (x_d[i] * y_d[i]);
		
		// x 와 y 의 편차의 제곱의 합
		x_d_pow_sum = x_d_pow_sum + (x_d[i] * x_d[i]);
		y_d_pow_sum = y_d_pow_sum + (y_d[i] * y_d[i]);
	}

	// 총 제곱의 합
	SST = y_d_pow_sum;
	// 기울기 = x 편차와 y 편차의 곱들의 합 / x 편차 제곱 합
	alpha = d_sum / x_d_pow_sum;
	// y 절편 = y 평균 - (기울기 * x 평균)
	beta = y_avg - (alpha * x_avg);

	for (int i = 0; i < NUMDATA; i++) {
		// 회귀식으로 인해 바뀐 새로운 y 값
		yHat_input[i] = alpha * input[i][0] + beta;
		// y^ 의 편차
		yHat_d[i] = yHat_input[i] - y_avg;
		// y^ 의 편차의 제곱의 합
		yHat_d_pow_sum = yHat_d_pow_sum + (yHat_d[i] * yHat_d[i]);
	}

	// 회귀 제곱의 합
	SSR = yHat_d_pow_sum;
	// 결정계수
	R = SSR / SST;

	printf("집 평수에 따른 집의 가격\n\n");
	printf("집 평수\t\t집 가격\n");
	for (int i = 0; i < NUMDATA; i++) {
		printf("  %d\t\t  %d\n", input[i][0], input[i][1]);
	}
	printf("\n회귀 식 : y = %fx + %f\n\n", alpha, beta);
	printf("SST : %f, SSR : %f\n\n", SST, SSR);
	printf("결정계수(R) : %.2f\n\n", R);

	printf("집이 17평 일 때의 집 값은 : %f\n\n", alpha * 17.0 + beta);
}