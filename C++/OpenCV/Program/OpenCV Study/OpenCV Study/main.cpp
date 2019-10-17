#include <opencv2/core.hpp> 
// �⺻���� �ڷᱸ���� �Լ����� ����
#include <opencv2/imgcodecs.hpp> 
// �̹��� ������ �о���� �Լ��� �̹��� ������ �����ϴ� �Լ��� ����
#include <opencv2/highgui.hpp> 
// �������̽��� ������ ���� ���, ������� �Է��� �ޱ� ���� ����ϴ� �Լ��� ȭ�鿡 �̹����� �����ֱ� ���� �Լ��� ���ԵǾ� �ִ�.
#include <opencv2/imgproc.hpp>
// Canny �Լ��� ����ϱ� ���� ���

//	#include <opencv2/opencv.hpp> �� 3���� �ϳ��� ���ļ� ����
#include <iostream>	// ������� ���� C++ ��� ����


using namespace cv;
using namespace std;


int main()
{
	Mat image;
	image = imread("OhMyGirl.jpeg", IMREAD_GRAYSCALE);
	// MAT cv::imread(const String & filename, int flags = IMREAD_COLOR)
	// IMREAD_UNCHANGED		���� ä���� ���Խ�Ų �÷� �̹��� ��ȯ
	// IMREAD_COLOR			���� ä���� ���� �÷� �̹����� ��ȯ
	// IMREAD_GRAYSCALE		�׷��� ������ �̹����� ��ȯ�Ͽ� ��ȯ
	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	imshow("Original", image);
	Canny(image, image, 50, 150);
	// ������ �����ϴ� �Լ�
	// ������ �����ϴ� �Լ��� ȣ���� �� image �� IMREAD_GRAYSCALE �ɼ����� �о�;� �Ѵ�.

	//namedWindow("Original", WINDOW_NORMAL);
	//namedWindow("Canny", WINDOW_NORMAL);
	// �̹����� ������ ������ ����
	// 1��° ���ڴ� �������� �ĺ��� �̸鼭 ������ Ÿ��Ʋ�� ������ �޼���
	// 2��° ���ڴ� WINDOW_AUTOSIZE�� �̹��� ũ�⿡ ���� ������ ũ�Ⱑ ������ ����ڰ� ������ ũ�⸦ ������ �� ����
	// WINDOW_NORMAL �� �̹����� ū ��� �ػ� ũ�⿡ ���� ������ ũ�Ⱑ ���� ��. ����ڰ� ������ ũ�⸦ ������ �� �ִ�. 
	// WND_PROP_FULLSCREEN �� ����� ��
	// setWindowProperty("Original", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	// �� ����ϸ� ȭ���� ����Ϳ� �� ����.
	imshow("Canny", image);
	// Original �޵��쿡 image �� ������ִ� �̹����� �����ش�.

	waitKey(0);
	// Ű���� �Է��� ���� �� ���� ���

	return 0;
}