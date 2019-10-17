#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;


int main()
{
	Mat img_color;


	img_color = imread("orange.jpg", IMREAD_COLOR);
	// �̹��� ���� orange.jpg�κ��� �̹����� �о�ͼ� BGR �������� ��ȯ
	if (img_color.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}


	Mat img_gray;

	Mat img_gray_3channel, img_gray_1channel;
	img_gray_3channel.create(img_color.rows, img_color.cols, CV_8UC3); //3ä�η� ����
	img_gray_1channel.create(img_color.rows, img_color.cols, CV_8UC1); //1ä�η� ����
	// GrayScale �̹����� �����ϱ� ���� 3���� ä���� ���� Mat ��ü�� 1���� ä���� ���� Mat ��ü�� ����

	for (int y = 0; y < img_color.rows; y++)
		for (int x = 0; x < img_color.cols; x++)
		{
			float b = img_color.at<Vec3b>(y, x)[0];
			float g = img_color.at<Vec3b>(y, x)[1];
			float r = img_color.at<Vec3b>(y, x)[2];
			// �÷� �̹����� �� �ȼ����� B, G, R ä�� ���� �����´�.

			float gray = (r * 0.21) + (g * 0.72) + (b * 0.07);
			// GrayScale �ȼ� ���� ���Ѵ�.

			img_gray_1channel.at<uchar>(y, x) = gray;
			// 1ä�� �̹����� ����

			img_gray_3channel.at<Vec3b>(y, x)[0] = gray;
			img_gray_3channel.at<Vec3b>(y, x)[1] = gray;
			img_gray_3channel.at<Vec3b>(y, x)[2] = gray;
			// 3ä�� �̹����� ����
		}
	namedWindow("GrayScale 3 channel", WINDOW_AUTOSIZE);
	namedWindow("GrayScale 1 channel", WINDOW_AUTOSIZE);

	Canny(img_gray_1channel, img_gray_1channel, 50, 150);
	imshow("GrayScale 3 channel", img_gray_3channel);
	imshow("GrayScale 1 channel", img_gray_1channel);

	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);
	// img_color �� ����Ǿ� �ִ� BGR ������ �÷� �̹����� GrayScale �̹����� ��ȯ�Ͽ� img_gray �� �����Ѵ�.
	// BGR2GRAY => BGR To GRAY
	// ��κ��� OpenCV �Լ����� ����� ������ �� ������ �޸𸮸� �Ҵ��Ͽ� �����ϱ� ������ ������� ������ ������ �޸𸮸� �Ҵ��� �ʿ䰡 ����.
	// ���� cvtColor �Լ��� ȣ���� �Ͽ� ������ �� img_gray ������ �޸𸮰� �Ҵ��
	imwrite("gray image.jpg", img_gray);
	// �̹����� �����Ѵ�. ������ ���� �̸��� Ȯ���ڴ�� �̹��� ������ ������ ��������.


	namedWindow("BGR", WINDOW_AUTOSIZE);
	namedWindow("Grayscale", WINDOW_AUTOSIZE);

	imshow("BGR", img_color);
	imshow("Grayscale", img_gray);


	while (waitKey(0) != 27);
	// ESC ������ ���� ���

	return 0;
}