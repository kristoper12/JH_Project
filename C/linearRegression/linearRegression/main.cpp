#include <stdio.h>

//������ ���� ũ��(���)�� ���谡 �Ʒ� �����Ϳ� ���� �� 17���� ���� ����
//����ȸ�ͺм����� ���϶�.
//
//
//(ũ��, ����) : (14, 127), (21, 140), (26, 151), (32, 175), (36, 180)
#define NUMDATA			5
#define NUMDATAFLOAT	5.0
// x �� �������� y �� ���Ӻ���
void main() {
	float alpha;					// ����
	float beta;						// y ����
	float R;						// �������
	float SSR;						// ȸ�� ������ ��
	float SST;						// �� ������ ��

	float x_d[NUMDATA];				// x ����
	float y_d[NUMDATA];				// y ����
	float yHat_d[NUMDATA];			// y^ ����

	float x_avg;					// x ���
	float y_avg;					// y ���

	float d_sum = 0.0;				// x ������ y ������ ������ ��

	float x_d_pow_sum = 0.0;		// x ���� ���� ��
	float y_d_pow_sum = 0.0;		// y ���� ���� ��
	float yHat_d_pow_sum = 0.0;		// y^ ���� ���� ��

	int x_sum = 0;					// x ��
	int y_sum = 0;					// y ��

	int input[NUMDATA][2] = {
		{14, 127},
		{21, 140},
		{26, 151},
		{32, 175},
		{36, 180}
	};								// �Է� ������
	float yHat_input[NUMDATA];		// ȸ�ͽ����� ���� �ٲ� ���ο� y ��

	// x �� y �� ��
	for (int i = 0; i < NUMDATA; i++) {
		x_sum = x_sum + input[i][0];
		y_sum = y_sum + input[i][1];
	}

	// x �� y �� ���
	x_avg = x_sum / NUMDATAFLOAT;
	y_avg = y_sum / NUMDATAFLOAT;

	for (int i = 0; i < NUMDATA; i++) {
		// x �� y �� ����
		x_d[i] = input[i][0] - x_avg;
		y_d[i] = input[i][1] - y_avg;

		// x ������ y ������ ������ ��
		d_sum = d_sum + (x_d[i] * y_d[i]);
		
		// x �� y �� ������ ������ ��
		x_d_pow_sum = x_d_pow_sum + (x_d[i] * x_d[i]);
		y_d_pow_sum = y_d_pow_sum + (y_d[i] * y_d[i]);
	}

	// �� ������ ��
	SST = y_d_pow_sum;
	// ���� = x ������ y ������ ������ �� / x ���� ���� ��
	alpha = d_sum / x_d_pow_sum;
	// y ���� = y ��� - (���� * x ���)
	beta = y_avg - (alpha * x_avg);

	for (int i = 0; i < NUMDATA; i++) {
		// ȸ�ͽ����� ���� �ٲ� ���ο� y ��
		yHat_input[i] = alpha * input[i][0] + beta;
		// y^ �� ����
		yHat_d[i] = yHat_input[i] - y_avg;
		// y^ �� ������ ������ ��
		yHat_d_pow_sum = yHat_d_pow_sum + (yHat_d[i] * yHat_d[i]);
	}

	// ȸ�� ������ ��
	SSR = yHat_d_pow_sum;
	// �������
	R = SSR / SST;

	printf("�� ����� ���� ���� ����\n\n");
	printf("�� ���\t\t�� ����\n");
	for (int i = 0; i < NUMDATA; i++) {
		printf("  %d\t\t  %d\n", input[i][0], input[i][1]);
	}
	printf("\nȸ�� �� : y = %fx + %f\n\n", alpha, beta);
	printf("SST : %f, SSR : %f\n\n", SST, SSR);
	printf("�������(R) : %.2f\n\n", R);

	printf("���� 17�� �� ���� �� ���� : %f\n\n", alpha * 17.0 + beta);
}