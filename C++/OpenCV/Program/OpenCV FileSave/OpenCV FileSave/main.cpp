#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;


int main()
{
	Mat img_color;


	img_color = imread("orange.jpg", IMREAD_COLOR);
	// 이미지 파일 orange.jpg로부터 이미지를 읽어와서 BGR 포맷으로 변환
	if (img_color.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}


	Mat img_gray;

	Mat img_gray_3channel, img_gray_1channel;
	img_gray_3channel.create(img_color.rows, img_color.cols, CV_8UC3); //3채널로 생성
	img_gray_1channel.create(img_color.rows, img_color.cols, CV_8UC1); //1채널로 생성
	// GrayScale 이미지를 저장하기 위해 3개의 채널을 가진 Mat 객체와 1개의 채널을 가진 Mat 객체를 생성

	for (int y = 0; y < img_color.rows; y++)
		for (int x = 0; x < img_color.cols; x++)
		{
			float b = img_color.at<Vec3b>(y, x)[0];
			float g = img_color.at<Vec3b>(y, x)[1];
			float r = img_color.at<Vec3b>(y, x)[2];
			// 컬러 이미지의 각 픽셀에서 B, G, R 채널 값을 가져온다.

			float gray = (r * 0.21) + (g * 0.72) + (b * 0.07);
			// GrayScale 픽셀 값을 구한다.

			img_gray_1channel.at<uchar>(y, x) = gray;
			// 1채널 이미지에 저장

			img_gray_3channel.at<Vec3b>(y, x)[0] = gray;
			img_gray_3channel.at<Vec3b>(y, x)[1] = gray;
			img_gray_3channel.at<Vec3b>(y, x)[2] = gray;
			// 3채널 이미지에 저장
		}
	namedWindow("GrayScale 3 channel", WINDOW_AUTOSIZE);
	namedWindow("GrayScale 1 channel", WINDOW_AUTOSIZE);

	Canny(img_gray_1channel, img_gray_1channel, 50, 150);
	imshow("GrayScale 3 channel", img_gray_3channel);
	imshow("GrayScale 1 channel", img_gray_1channel);

	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);
	// img_color 에 저장되어 있는 BGR 포맷의 컬러 이미지를 GrayScale 이미지로 변환하여 img_gray 에 저장한다.
	// BGR2GRAY => BGR To GRAY
	// 대부분의 OpenCV 함수들은 출력을 리턴할 때 변수에 메모리를 할당하여 리턴하기 때문에 출력으로 지정한 변수에 메모리를 할당할 필요가 없다.
	// 따라서 cvtColor 함수를 호출을 하여 리턴할 때 img_gray 변수에 메모리가 할당됨
	imwrite("gray image.jpg", img_gray);
	// 이미지를 저장한다. 지정한 파일 이름의 확장자대로 이미지 파일의 포맷이 정해진다.


	namedWindow("BGR", WINDOW_AUTOSIZE);
	namedWindow("Grayscale", WINDOW_AUTOSIZE);

	imshow("BGR", img_color);
	imshow("Grayscale", img_gray);


	while (waitKey(0) != 27);
	// ESC 누를때 까지 대기

	return 0;
}